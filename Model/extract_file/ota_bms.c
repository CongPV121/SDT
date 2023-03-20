/*
 * ota_bms.c
 *
 *  Created on: Mar 13, 2023
 *      Author: Admin
 */



#include "ota_bms.h"
#include "app_config.h"
#include "cabinet.h"
#include "esp_log.h"
#include "storage.h"
#include "boot_master_app.h"
#include "app_co_init.h"
static const char* TAG = "BMS_OTA";


void boot_master_process(FILE *file);

typedef struct Bp_Ota_Data_t Bp_Ota_Data;

typedef struct Bp_Ota_t Bp_Ota;

struct Bp_Ota_t{
	MBS *p_mbs;
	int bp_index;
};

struct Bp_Ota_Data_t{
	uint16_t length;
	bool is_comming;
	uint32_t addr;
	uint8_t *p_data;
	bool end_record;
	uint32_t start_addr;
	uint32_t begin_addr;
	uint8_t begin_ota;
	int err;
};

static Bp_Ota_Data* bms_ota_get_data(FILE *file);

TaskHandle_t bms_ota_handle;
SemaphoreHandle_t bms_ota_mutex;
QueueHandle_t bms_ota_is_comming_data_handle;
static void bms_ota_process(void *arg);
static void bms_ota_record_process(Bp_Ota_Data *p_data,intel_hex *p_record);
static void boot_m_co_set_download_completed(Boot_master* p_boot);

void bms_ota_init(){
	bms_ota_mutex = xSemaphoreCreateMutex();
	bms_ota_is_comming_data_handle = xQueueCreate(1,sizeof(Bp_Ota_Data));
}
int bms_ota_add(MBS *p_mbs,int bp_index){
	for(uint16_t i = 0;i< MAX_BATTERY_CABINET_NUM;i++){
		if(cab_get_state(&p_mbs->cabinets[i]) == CAB_ST_UPDATE_FIRMWARE){
			return -1;
		}
	}
	cab_set_state(&p_mbs->cabinets[bp_index],CAB_ST_UPDATE_FIRMWARE);
	Bp_Ota bp_ota = {.p_mbs = p_mbs, .bp_index = bp_index};
	xTaskCreate(bms_ota_process,"bms_ota",1024*4, &bp_ota,configMAX_PRIORITIES-10,&bms_ota_handle);
	return 0;
}

static uint8_t segment_data[SEGMENT_MEMORY_SIZE];

static void bms_ota_process(void *arg){
	boot_master_app_init();
	Bp_Ota *p_bp_ota = (Bp_Ota*) arg;

	MBS *p_mbs = p_bp_ota->p_mbs;
	int bp_index = p_bp_ota->bp_index;
	p_mbs->cabinets[bp_index].battery->base.base.node_id = 4;
	xSemaphoreTake(bms_ota_mutex, portMAX_DELAY);

	FILE *file = fopen("/spiffs/bms.hex","r");
	if(file == NULL){
		goto END_OTA;
	}
	while(1){
		boot_master_process(file);
	}
END_OTA:
{
	xSemaphoreGive(bms_ota_mutex);

	cab_set_state(&p_mbs->cabinets[bp_index],CAB_ST_EMPTY);
	printf("End update BMS OTA\n");
	vTaskDelete(bms_ota_handle);
}
}
static void bms_ota_record_process(Bp_Ota_Data *p_data,intel_hex *p_record){

	switch (p_record->record_type) {
		case INTEL_HEX_Data:
			// TODO: Add data to buffer
			for(uint16_t i = 0;i<p_record->byte_count;i++){
				p_data->p_data[p_data->length+i] = p_record->data[i];
			}
			p_data->length+= p_record->byte_count;
			break;
		case INTEL_HEX_EndFile:
			// TODO: End of file, end flash firmware,
			p_data->end_record = true;
			break;
		case INTEL_HEX_Extended_Linear_Address:
			// TODO: New address , bit 16-31
			uint32_t addr_16_31 = ((uint32_t)p_record->data[0]<<8) | (uint32_t)p_record->data[1];
			uint32_t addr_0_15 = ((uint32_t)p_record->addr[0] << 8) | (uint32_t)p_record->addr[1];
			p_data->addr = (addr_16_31<<16)  + addr_0_15;
			if(p_data->length > 0){
				p_data->is_comming = true;
			}
			break;
		case INTEL_HEX_Extended_Segment_Address:
			// TODO: New address, bit 4-19
			uint32_t addr_4_19 = ((uint32_t)p_record->data[0]<<8) | (uint32_t)p_record->data[1];
			uint32_t addr_0 = ((uint32_t)p_record->addr[0] << 8) | (uint32_t)p_record->addr[1];
			p_data->addr = (addr_4_19<<4) + addr_0;
			if(p_data->length > 0){
				p_data->is_comming = true;
			}
			break;
		case INTEL_HEX_Start_Linear_Address:
			// TODO: Nothing
			break;
		case INTEL_HEX_Start_Segment_Address:
			// TODO: Nothing
			break;
		default:
			break;
	}
}
Boot_master  *p_boot_m =  &boot_master;
uint16_t ex_boot_cnt = 0;
uint16_t num_request_cnt = 0;

uint32_t boot_timeout = 0;
#define  TIMEOUT 20000
void boot_master_process(FILE *file){
	boot_read_info((Bootloader*)p_boot_m);
	switch( boot_get_state((Bootloader*)p_boot_m) ){

	case BOOT_ST_PRE_INIT:
		ex_boot_cnt = 0;
		num_request_cnt = 0;
		boot_timeout = 0;
		boot_set_state(&p_boot_m->base, BOOT_ST_INIT);
		break;
	case BOOT_ST_INIT:
		if(boot_timeout ++ > TIMEOUT) {
			boot_set_state(&p_boot_m->base, BOOT_ST_PRE_INIT);
		}
		ex_boot_cnt ++;
		if((ex_boot_cnt > num_request_cnt) &&
				(ex_boot_cnt < 2000)	){
			co_send_ex_boot_request(&can1);
			num_request_cnt += 100;
			break;
		}
		/*  timeout */
		if(ex_boot_cnt == 3000){
			boot_set_state(&p_boot_m->base, BOOT_ST_PRE_INIT);

		}
		/* ex request*/
		if(ex_boot_cnt > 2000){
			boot_reboot((Bootloader*)p_boot_m);
		}
		//boot_reboot((Bootloader*)p_boot_m);
		break;

	case BOOT_ST_PREPARING:
		break;

	case BOOT_ST_LOADING_SERVER:
		Bp_Ota_Data *data_iscomming;
		boot_set_state(&p_boot_m->base, BOOT_ST_LOADING_LOCAL);

		data_iscomming = bms_ota_get_data(file);
		if(data_iscomming->err == 1){
			boot_set_state((Bootloader*)p_boot_m, BOOT_ST_FAIL);
		}
		//printf("Writing %u, size %d\n",data_iscomming->addr,(unsigned int)data_iscomming->length);
		segment_download_build(data_iscomming->addr,data_iscomming->p_data,data_iscomming->length);

		data_iscomming->addr += data_iscomming->length;

		if(data_iscomming->end_record == true){
			Segment_fw* p_seg = &boot_master.base.segment_downloaded;
			p_seg->id = 0;
			boot_m_co_set_download_completed(p_boot_m);
		}
		break;

	case BOOT_ST_LOADING_LOCAL:
		boot_set_data_to_local((Bootloader*)p_boot_m);
		break;

	case BOOT_ST_DOWNLOAD_COMPLETED:
		boot_download_completed_handle((Bootloader*)p_boot_m);
		break;

	case BOOT_ST_VALIDATING:
		boot_set_state((Bootloader*)p_boot_m, BOOT_ST_FINISH);
		break;

	case BOOT_ST_FINISH:
		boot_finish((Bootloader*)p_boot_m);
		break;

	case BOOT_ST_FAIL:
		boot_set_state((Bootloader*)p_boot_m, BOOT_ST_PRE_INIT);
		reset_id_segment_download(&boot_master.base.segment_downloaded);
		break;

	case BOOT_ST_READ_INFO:
		break;

	case BOOT_ST_WRITE_VERSION:
		break;

	default:
		break;
	}

}
static void boot_m_co_set_download_completed(Boot_master* p_boot){
	boot_set_state(&p_boot->base, BOOT_ST_DOWNLOAD_COMPLETED);
	reset_id_segment_download(&p_boot->base.segment_downloaded);
	p_boot->fw_signature.addr = (uint32_t) FLASH_IMAGE_1_ADDR;
	p_boot->fw_signature.size = SEGMENT_MEMORY_SIZE * NUMBER_OF_SEGMENT;
	p_boot->fw_signature.crc  = (uint16_t) CRC_CalculateCRC16((uint8_t*)p_boot->fw_signature.addr
			,p_boot->fw_signature.size);
}

Bp_Ota_Data bp_data = {.addr = 0,.start_addr = 0,.p_data = segment_data,.length = 0,.err = 0,.is_comming = false,.end_record = false};

static Bp_Ota_Data* bms_ota_get_data(FILE *file){

	Bp_Ota_Data *p_bp_data = &bp_data;
	if(file == NULL){
		goto BP_DATA_ERROR;
	}

	char line[64] = {0};
	uint8_t buff_hex [50];

	p_bp_data->p_data = segment_data;
	p_bp_data->length = 0;
	while(p_bp_data->length < SEGMENT_MEMORY_SIZE){
		char *p_line = fgets(line, 64, file);

		if (p_line == NULL) {
			goto BP_DATA_ERROR;
		}

		int hex_length = string_to_hex(p_line, strlen(p_line), buff_hex);
		intel_hex *p_record = intel_hex_process(buff_hex, hex_length);

		if (p_record == NULL) {
			goto BP_DATA_ERROR;
		}
		bms_ota_record_process(p_bp_data,p_record);

		if(p_bp_data->is_comming == true) break;

	}
	return p_bp_data;
BP_DATA_ERROR:
{
 	p_bp_data->addr = 0;
	p_bp_data->err = 1;
	p_bp_data->end_record = false;
	p_bp_data->length = 0;
	p_bp_data->p_data = NULL;
	p_bp_data->is_comming = false;
	return p_bp_data;
}
}
