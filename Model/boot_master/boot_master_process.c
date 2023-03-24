/*
 * boot_master_app.c
 *
 *  Created on: May 11, 2022
 *      Author: khanh
 */

#include "boot_master_process.h"
#include "Controller/boot_master_app/boot_master_config.h"
#include "Model/boot_master/intel_hex.h"
#include "stdint.h"

static void boot_load_data_to_local_handle       (Bootloader*);
static void boot_load_from_server_handle         (Bootloader*);
static void boot_reboot_handle                   (Bootloader*);
static void boot_finish_handle                   (Bootloader*);
static void boot_start_handle                    (Bootloader*);
static void boot_completed_download_handle       (Bootloader*);
static void boot_save_setting_handle             (Bootloader*);

static void can_reboot_sync_state_to_local 		 (Segment_fw*);
static void co_segment_fw_write_addr_handle      (Segment_fw*);
static void co_segment_fw_write_data_handle      (Segment_fw*);
static void co_segment_fw_write_crc_handle       (Segment_fw*);
static void main_app_request_new_firmware        (Segment_fw*);
void        co_segment_build_handle(Segment_fw* p_seg, uint32_t addr, uint8_t* data,
                                    uint16_t crc_code,uint16_t size );
static void co_set_download_completed(Boot_master* p_boot);
static void co_read_version_fw_handle            (Signature*);
static void flashImageFromHex(seg_firmware *p_data,intel_hex *p_record);


uint8_t reboot_state[2];

static inline void segment_fw_write_process      (Segment_fw* p_seg, void (*method)(Segment_fw*), WRITE_SEGMENT_FW_STATE next_state);
Boot_master         boot_master;
proress_results     download_results = {.percent_complete = 0};
uint8_t     data_firmware[1024*1024];

void boot_master_init(void){
    boot_master.boot_id_src						 =	1;
    boot_master.total_segment                    =  96;
    boot_master.data_firmware                    =  data_firmware;
    Bootloader* p_boot                           = &boot_master.base;
    boot_set_state(&boot_master.base, BOOT_ST_NOT_ACTIVE);
    reset_id_segment_download(&boot_master.base.segment_downloaded);

    p_boot->load_data_to_local                   = boot_load_data_to_local_handle;
    p_boot->get_data_from_server                 = boot_load_from_server_handle;
    p_boot->reboot                               = can_reboot_sync_state_to_local;
    p_boot->finish                               = boot_finish_handle;
    p_boot->start                                = boot_start_handle;
    p_boot->download_completed                   = boot_completed_download_handle;
    p_boot->save_setting                         = boot_save_setting_handle;
    p_boot->request_new_firmware				 = main_app_request_new_firmware;


    p_boot->segment_downloaded.write_addr        = co_segment_fw_write_addr_handle;
    p_boot->segment_downloaded.write_data        = co_segment_fw_write_data_handle;
    p_boot->segment_downloaded.write_crc         = co_segment_fw_write_crc_handle;
}
FILE *file = NULL;


void boot_master_process(Boot_master *p_boot_m,uint64_t timestamp,
                         uint16_t *active_download,
                         uint16_t nodeid_device,
                         char *path,
                         proress_results *download_results){
    printf("boot sate: %d\n",boot_get_state((Bootloader*)p_boot_m));
    //boot_read_info((Bootloader*)p_boot_m);
    /*timeout update*/
    if(p_boot_m->base.is_state_change){
        boot_master_update_timeout(p_boot_m,timestamp);
        p_boot_m->base.is_state_change = false;
    }
    if(boot_master_is_timeout(p_boot_m,timestamp)){
        boot_set_state((Bootloader*)p_boot_m, BOOT_ST_FAIL);
    }

    switch( boot_get_state((Bootloader*)p_boot_m) ){

    case BOOT_ST_NOT_ACTIVE:
        /* Start preparing and download firmware*/

        if(*active_download == 1 &&
                path != NULL    ){
            boot_set_state((Bootloader*)p_boot_m, BOOT_ST_INIT);
            p_boot_m->boot_id_src = nodeid_device;
            *active_download = 0;
        }
        break;
    case BOOT_ST_INIT:

        file = fopen(path,"r");
        fclose(file);
        file = NULL;
        file = fopen(path,"r");
        if(extract_getsegment(file) == 0 ){
            fclose(file);
            file = NULL;
            boot_set_state(&p_boot_m->base, BOOT_ST_PREPARING);
        }
        p_boot_m->fw_signature.addr = (uint32_t) BMS_MAIN_APP_FIRM_ADDR;
        p_boot_m->base.segment_downloaded.transmitted_seg = 0;
        boot_set_state(&p_boot_m->base, BOOT_ST_PREPARING);
        break;

    case BOOT_ST_PREPARING:
        //boot_reboot((Bootloader*)p_boot_m);

        break;

    case BOOT_ST_LOADING_SERVER:

        boot_set_state(&p_boot_m->base, BOOT_ST_LOADING_LOCAL);
        /* get firmware segment */
        segment_download_build(p_boot_m);

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
        if( file != NULL ){
            fclose(file);
        }
        file = NULL;
        CO_SDO_reset_status(&CO_DEVICE.sdo_client);
        boot_set_state((Bootloader*)p_boot_m, BOOT_ST_NOT_ACTIVE);
        reset_id_segment_download(&boot_master.base.segment_downloaded);
        break;

    case BOOT_ST_READ_INFO:
        break;

    case BOOT_ST_WRITE_VERSION:
        break;

    default:
        break;
    }

    if(p_boot_m->total_segment < 1){
        download_results->percent_complete = 0;
    }
    else{
        download_results->percent_complete = 100*p_boot_m->base.segment_downloaded.transmitted_seg
                /p_boot_m->total_segment;
    }

}
/*-------------------------------------------------------------------*/
bool extract_getsegment(FILE *p_file){
    if(p_file == NULL){
        return 0;
    }
    bool end_of_file = false;

    Segment_fw* p_seg = &boot_master.base.segment_downloaded;
    Bootloader* p_boot =&boot_master.base;

    memset(boot_master.data_firmware,0xff,1024*1024);
    boot_master.total_segment = 0;
    boot_master.fw_signature.size = 0;

    seg_firmware *data_iscomming;

    /* unzip the firmware segment */
    while(!end_of_file){
        data_iscomming = unzip_fw(p_file);
        if(data_iscomming->err == 1){
        }
        /*end of hex file*/
        if(data_iscomming->end_record == true){
            end_of_file = false;
            fclose(p_file);
            //co_set_download_completed(p_boot_m);
            break;
        }
        /*remove the part of data that is outside the address*/
        if(data_iscomming->addr > (0x10000 + 0x20000)
                || data_iscomming->addr < 0x10000){
            continue;
        }

        /* get firmware segment */
        memcpy(boot_master.data_firmware + boot_master.fw_signature.size,
               data_iscomming->p_data,data_iscomming->length);
        boot_master.fw_signature.size += data_iscomming->length;
        data_iscomming->addr += data_iscomming->length;
        boot_master.total_segment ++;
    }
    return 1;
}

/*-------------------------------------------------------------------*/
/* This is the function to decode intel hex file to flash data Image
 *
*/
static uint8_t segment_data[SEGMENT_MEMORY_SIZE];
seg_firmware bp_data = {.addr = 0,.start_addr = 0,.p_data = segment_data,.length = 0,.err = 0,.is_comming = false,.end_record = false};

seg_firmware* unzip_fw(FILE *file){
    if(file == NULL){
        return NULL;
    }
    seg_firmware *p_bp_data = &bp_data;

    char line[64] = {0};
    uint8_t buff_hex [50];

    p_bp_data->p_data = segment_data;
    p_bp_data->length = 0;
    while(p_bp_data->length < SEGMENT_MEMORY_SIZE){
        char *p_line = fgets(line, 64, file);
        if (p_line == NULL) {

        }

        int hex_length = string_to_hex(line, strlen(line)-2, buff_hex);
        intel_hex *p_record = intel_hex_process(buff_hex, hex_length);

        if (p_record == NULL) {
        }
        flashImageFromHex(p_bp_data,p_record);
        if(p_bp_data->is_comming == true) break;
    }
    return p_bp_data;
}

static void flashImageFromHex(seg_firmware *p_data,intel_hex *p_record){
    uint32_t addr_16_31 ;
    uint32_t addr_4_19 ;
    p_data->addr_t = p_record->addrs;
    if(p_record == NULL) return;
    if(p_data == NULL) return;

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
        addr_16_31 = (uint32_t)(((uint32_t)p_record->data[0]<<8) | (uint32_t)p_record->data[1]);
        uint32_t addr_0_15 = ((uint32_t)p_record->addr[0] << 8) | (uint32_t)p_record->addr[1];
        p_data->addr = (addr_16_31<<16)  + addr_0_15;
        if(p_data->length > 0){
            p_data->is_comming = true;
        }
        break;
    case INTEL_HEX_Extended_Segment_Address:
        // TODO: New address, bit 4-19
        addr_4_19 = ((uint32_t)p_record->data[0]<<8) | (uint32_t)p_record->data[1];
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
static uint8_t segment[SEGMENT_MEMORY_SIZE];
void segment_download_build(Boot_master *p_boot_m){
    Segment_fw* p_seg = &p_boot_m->base.segment_downloaded;

    Bootloader* p_boot =&p_boot_m->base;
    /* */
    uint32_t addr = p_boot_m->fw_signature.addr +
            p_seg->transmitted_seg*SEGMENT_MEMORY_SIZE;
    memset(segment,0xff,SEGMENT_MEMORY_SIZE);
    memcpy(segment,p_boot_m->data_firmware + p_seg->transmitted_seg*SEGMENT_MEMORY_SIZE,
           SEGMENT_MEMORY_SIZE );
    co_segment_build_handle(p_seg,addr,segment,
                            CRC_CalculateCRC16(segment, SEGMENT_MEMORY_SIZE),
                            SEGMENT_MEMORY_SIZE);
    p_boot->segment_downloaded.write_state = SEGMENT_WRITE_NONE;
    p_seg->transmitted_seg++;
    if(p_seg->transmitted_seg > boot_master.total_segment){
        p_seg->transmitted_seg = 0;
        co_set_download_completed(p_boot_m);
        boot_set_state(&p_boot_m->base, BOOT_ST_DOWNLOAD_COMPLETED);
    }
}
/*-------------------------------------------------------------------*/
static void boot_load_data_to_local_handle(Bootloader* p_boot){

    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Segment_fw* p_seg = &p_boot->segment_downloaded;

    switch(p_seg->write_state){
    case SEGMENT_WRITE_NONE:
        if( CO_SDO_get_status(p_sdo) == CO_SDO_RT_idle )
            p_seg->write_state = SEGMENT_WRITE_ADDR;
        break;

    case SEGMENT_WRITE_ADDR:
        segment_fw_write_process(p_seg, p_seg->write_addr, SEGMENT_WRITE_DATA);
        break;

    case SEGMENT_WRITE_DATA:
        segment_fw_write_process(p_seg, p_seg->write_data, SEGMENT_WRITE_CRC);
        break;

    case SEGMENT_WRITE_CRC:
        segment_fw_write_process(p_seg, p_seg->write_crc, SEGMENT_WRITE_SUCCESS);
        break;

    case SEGMENT_WRITE_SUCCESS:
        //p_boot->segment_downloaded.write_state = SEGMENT_WRITE_NONE;
        break;

    case SEGMENT_WRITE_FAIL:
        p_boot->segment_downloaded.write_state = SEGMENT_WRITE_NONE;
        boot_set_state(p_boot, BOOT_ST_FAIL);
        break;
    default:
        break;
    }
}

void co_segment_build_handle(Segment_fw* p_seg, uint32_t addr, uint8_t *data,
                             uint16_t crc_code, uint16_t size ){
    p_seg->addr = addr;
    memcpy(p_seg->data,data,size);
    p_seg->crc_code = crc_code;
    p_seg->size = size;
}
static void co_set_download_completed(Boot_master* p_boot){
    reset_id_segment_download(&p_boot->base.segment_downloaded);
    p_boot->fw_signature.crc  = (uint16_t) CRC_CalculateCRC16(p_boot->data_firmware
                                                              ,p_boot->fw_signature.size);
}

static void boot_load_from_server_handle(Bootloader* p_boot){
    if( !p_boot->segment_downloaded.is_last ) return;
    boot_set_state(p_boot, BOOT_ST_DOWNLOAD_COMPLETED);
}


static void boot_reboot_handle(Bootloader* p_boot){
    (void)p_boot;
    // Reset all
    //NVIC_SystemReset();
}


static void boot_finish_handle(Bootloader* p_boot){
    (void)p_boot;
    boot_set_state(&boot_master.base, BOOT_ST_NOT_ACTIVE);
    CO_SDO_reset_status(&CO_DEVICE.sdo_client);
}


static void boot_start_handle(Bootloader* p_boot){
    (void)p_boot;
    //    Fota_server* p_svr = boot_master.fota_svr;
    //    if( fota_svr_response_state(p_svr, "ready") ){
    //        boot_set_state(p_boot, BOOT_ST_LOADING_SERVER);
    //        return;
    //    }
    //    boot_set_state(p_boot, BOOT_ST_FAIL);
}


static void boot_save_setting_handle    (Bootloader* p_boot){
    (void)p_boot;
    //    uint8_t buff_size = 32;
    //    uint8_t buff[buff_size];
    //    memset(buff, 0, buff_size);
    //    memcpy(buff, (uint8_t*)BOOT_COMMON_SETTING_ADDR, buff_size);

    //    boot_update_info(p_boot, buff);

    //    if( flash_hp_data_flash_write_memory(BOOT_COMMON_SETTING_ADDR, buff, buff_size) != 0 ){
    //        boot_set_state(p_boot, BOOT_ST_FAIL);
    //    }
}




/* ------------------------- SDO For Firmware Information ------------------------- */

static void write_fw_size       (Segment_fw* p_seg);
static void write_fw_crc        (Segment_fw* p_seg);
static void write_fw_version    (Segment_fw* p_seg);

static Segment_fw fw_info = {.write_addr = write_fw_size,
                             .write_crc  = write_fw_crc,
                             .write_data = write_fw_version,
                             .write_state = SEGMENT_WRITE_NONE
                            };

static void boot_completed_download_handle(Bootloader* p_boot){

    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;

    Segment_fw* p_seg = &fw_info;

    switch(p_seg->write_state){
    case SEGMENT_WRITE_NONE:
        if( CO_SDO_get_status(p_sdo) == CO_SDO_RT_idle )
            p_seg->write_state = SEGMENT_WRITE_ADDR;
        break;

    case SEGMENT_WRITE_ADDR:            // Firmware Size
        segment_fw_write_process(p_seg, p_seg->write_addr, SEGMENT_WRITE_CRC);
        break;

    case SEGMENT_WRITE_CRC:             // Firmware CRC
        segment_fw_write_process(p_seg, p_seg->write_crc, SEGMENT_WRITE_DATA);
        break;

    case SEGMENT_WRITE_DATA:            // Firmware Version
        segment_fw_write_process(p_seg, p_seg->write_data, SEGMENT_WRITE_SUCCESS);
        break;

    case SEGMENT_WRITE_SUCCESS:
        p_seg->write_state = SEGMENT_WRITE_NONE;
        boot_set_state(p_boot, BOOT_ST_VALIDATING);
        break;

    case SEGMENT_WRITE_FAIL:
        p_seg->write_state = SEGMENT_WRITE_NONE;
        boot_set_state(p_boot, BOOT_ST_FAIL);
        break;
    }
}

static void write_fw_size(Segment_fw* p_seg){
    (void)p_seg;
    CO_Sub_Object fw_size = {.p_data = (uint8_t*)&boot_master.fw_signature.size,
                             .attr   = ODA_SDO_RW,
                             .len    = 4,
                             .p_ext  = NULL
                            };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                boot_master.boot_id_src,
                                SDO_BOOTLOADER_INDEX,
                                SDO_BOOTLOADER_FW_SIZE_SUB_INDEX,
                                &fw_size, 1000);
}

static void write_fw_crc(Segment_fw* p_seg){
    (void)p_seg;
    CO_Sub_Object fw_crc = {.p_data = (uint8_t*)&boot_master.fw_signature.crc,
                            .attr   = ODA_SDO_RW,
                            .len    = 2,
                            .p_ext  = NULL
                           };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                boot_master.boot_id_src,
                                SDO_BOOTLOADER_INDEX,
                                SDO_BOOTLOADER_FW_CRC_SUB_INDEX,
                                &fw_crc, 1000);
}

static void write_fw_version(Segment_fw* p_seg){
    (void)p_seg;
    CO_Sub_Object fw_version = {.p_data = boot_master.fw_signature.version,
                                .attr   = ODA_SDO_RW,
                                .len    = 3,
                                .p_ext  = NULL
                               };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                boot_master.boot_id_src,
                                SDO_BOOTLOADER_INDEX,
                                SDO_BOOTLOADER_FW_VERSION_SUB_INDEX,
                                &fw_version, 1000);
}

/* ------------------------- Segment Firmware Interface ------------------------- */

static inline void segment_fw_write_process(Segment_fw* p_seg, void (*method)(Segment_fw*), WRITE_SEGMENT_FW_STATE next_state){
    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;

    switch( CO_SDO_get_status(p_sdo) ){
    case CO_SDO_RT_idle:
        method(p_seg);
        break;

    case CO_SDO_RT_busy:
        break;

    case CO_SDO_RT_success:
        CO_SDO_reset_status(p_sdo);
        p_seg->write_state = next_state;
        break;

    case CO_SDO_RT_abort:
        CO_SDO_reset_status(p_sdo);
        //        if(sdo_svr->retry_cnt < SDO_SEGMENT_WRITE_RETRY_NUM){
        //            sdo_svr->retry_cnt++;
        //            break;
        //        }
        p_seg->write_state = SEGMENT_WRITE_FAIL;
        // sdo_svr->retry_cnt = 0;
        break;
    }
}
/* ----------------------------------------------------------------------------------- */

static void co_read_version_fw_handle(Signature* p_sig){

    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;

    CO_Sub_Object fw_version = {.p_data = p_sig->version,
                                .attr   = ODA_SDO_RW,
                                .len    = 3,
                                .p_ext  = NULL
                               };
    CO_SDOclient_start_upload  (p_sdo,
                                p_boot_m->boot_id_src,
                                SDO_BOOTLOADER_INDEX,
                                SDO_BOOTLOADER_FW_VERSION_SUB_INDEX,
                                &fw_version, 500);
}

static void co_segment_fw_write_addr_handle(Segment_fw* p_seg){

    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;

    CO_Sub_Object segment_addr = {.p_data = (uint8_t*)&p_seg->addr,
                                  .attr   = ODA_SDO_RW,
                                  .len    = 4,
                                  .p_ext  = NULL
                                 };
    CO_SDOclient_start_download(p_sdo, p_boot_m->boot_id_src, SDO_BOOTLOADER_INDEX,
                                SDO_BOOTLOADER_SEG_ADDR_SUB_INDEX,
                                &segment_addr,
                                1000);
}


static void co_segment_fw_write_data_handle(Segment_fw* p_seg){

    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;

    CO_Sub_Object segment_data = {.p_data = (uint8_t*)p_seg->data,
                                  .attr   = ODA_SDO_RW,
                                  .len    = p_seg->size,
                                  .p_ext  = NULL
                                 };
    CO_SDOclient_start_download(p_sdo, p_boot_m->boot_id_src, SDO_BOOTLOADER_INDEX,
                                SDO_BOOTLOADER_SEG_DATA_SUB_INDEX,
                                &segment_data,
                                1000);
}


static void co_segment_fw_write_crc_handle(Segment_fw* p_seg){

    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;

    CO_Sub_Object segment_crc = {.p_data = (uint8_t*)&p_seg->crc_code,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 2,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(p_sdo, p_boot_m->boot_id_src, SDO_BOOTLOADER_INDEX,
                                SDO_BOOTLOADER_SEG_CRC_SUB_INDEX,
                                &segment_crc,
                                1000);
}
static void can_reboot_sync_state_to_local (Segment_fw* p_seg)
{
    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;
    reboot_state[0] = 1;

    if ( CO_SDO_get_status(p_sdo) == CO_SDO_RT_idle ){

        CO_Sub_Object boot_state = { .p_data    = (uint8_t*)reboot_state,
                                     .attr      = ODA_SDO_RW,
                                     .len       = 1,
                                     .p_ext     = NULL};
        CO_SDOclient_start_download(p_sdo, boot_master.boot_id_src	, SDO_BOOTLOADER_INDEX,
                                    1,
                                    &boot_state,
                                    1000);
    }
    if (CO_SDO_get_status(p_sdo) == CO_SDO_RT_abort ){
        CO_SDO_reset_status(p_sdo);
        //boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
    }
    else if(CO_SDO_get_status(p_sdo) == CO_SDO_RT_success){
        CO_SDO_reset_status(p_sdo);
        // boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
        return;
    }
}
static void main_app_request_new_firmware (Segment_fw* p_seg)
{
    (void)p_seg;
    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;
    reboot_state[0] = 1;

    if ( CO_SDO_get_status(p_sdo) == CO_SDO_RT_idle ){

        CO_Sub_Object boot_state = { .p_data    = (uint8_t*)reboot_state,
                                     .attr      = ODA_SDO_RW,
                                     .len       = 1,
                                     .p_ext     = NULL};
        CO_SDOclient_start_download(p_sdo, boot_master.boot_id_src	, 0x2300,
                                    1,
                                    &boot_state,
                                    1000);
    }
    if (CO_SDO_get_status(p_sdo) == CO_SDO_RT_abort ){
        CO_SDO_reset_status(p_sdo);
        //boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
    }
    else if(CO_SDO_get_status(p_sdo) == CO_SDO_RT_success){
        CO_SDO_reset_status(p_sdo);
        boot_set_state(&boot_master.base, BOOT_ST_NOT_ACTIVE);
        return;
    }
}

