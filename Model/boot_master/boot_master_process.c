/*
 * boot_master_app.c
 *
 *  Created on: May 11, 2022
 *      Author: khanh
 */

#include "boot_master_process.h"
#include "Controller/boot_master_app/boot_master_config.h"

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
static void main_app_request_new_firmware       (Segment_fw*);
void co_segment_build_handle(Segment_fw* p_seg, uint32_t addr, uint8_t* data,
                             uint16_t crc_code,uint16_t size );
static void co_set_download_completed(Boot_master* p_boot);
static void co_read_version_fw_handle            (Signature*);
uint8_t reboot_state[2];

static inline void segment_fw_write_process      (Segment_fw* p_seg, void (*method)(Segment_fw*), WRITE_SEGMENT_FW_STATE next_state);
Boot_master boot_master;
uint8_t segment[1024];
uint8_t fw_data[SEGMENT_MEMORY_SIZE * NUMBER_OF_SEGMENT];
void boot_master_init(void){
    boot_master.boot_id_src						 =	1;
    Bootloader* p_boot                           = &boot_master.base;
    boot_set_state(&boot_master.base, BOOT_ST_INIT);
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
void boot_master_process(Boot_master *p_boot_m,uint64_t timestamp){
    //CO_process(&selex_bms.co_app, 1);
    //boot_read_info((Bootloader*)p_boot_m);

    switch( boot_get_state((Bootloader*)p_boot_m) ){

    case BOOT_ST_PRE_INIT:
        fw_extract();

        break;
    case BOOT_ST_INIT:
        boot_reboot((Bootloader*)p_boot_m) ;
        break;

    case BOOT_ST_PREPARING:
        break;

    case BOOT_ST_LOADING_SERVER:
        boot_set_state(&p_boot_m->base, BOOT_ST_LOADING_LOCAL);
        segment_download_build();
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
void fw_extract(void){

}

void segment_download_build(void){
    Segment_fw* p_seg = &boot_master.base.segment_downloaded;
    Bootloader* p_boot =&boot_master.base;
    uint32_t addr =0 ;
    //memcpy(segment,(uint8_t *)addr,SEGMENT_MEMORY_SIZE);
    co_segment_build_handle(p_seg,addr,segment,
                            CRC_CalculateCRC16(segment, SEGMENT_MEMORY_SIZE),
                            SEGMENT_MEMORY_SIZE);
    p_boot->segment_downloaded.write_state = SEGMENT_WRITE_NONE;
    p_seg->id++;
    if(p_seg->id > NUMBER_OF_SEGMENT)  {
        p_seg->id = 0;
        co_set_download_completed(&boot_master);
    }
}
void co_segment_build_handle(Segment_fw* p_seg, uint32_t addr, uint8_t *data,
                             uint16_t crc_code, uint16_t size ){
    p_seg->addr = addr;
    memcpy(p_seg->data,data,1024);
    p_seg->crc_code = crc_code;
    p_seg->size = size;
}
static void co_set_download_completed(Boot_master* p_boot){
    boot_set_state(&p_boot->base, BOOT_ST_DOWNLOAD_COMPLETED);
    reset_id_segment_download(&p_boot->base.segment_downloaded);
    p_boot->fw_signature.addr = (uint32_t) BMS_MAIN_APP_FIRM_ADDR;
    p_boot->fw_signature.size = SEGMENT_MEMORY_SIZE * NUMBER_OF_SEGMENT;
    //memcpy(fw_data,(uint8_t *)p_boot->fw_signature.addr,p_boot->fw_signature.size);
    p_boot->fw_signature.crc  = (uint16_t) CRC_CalculateCRC16((uint8_t*)p_boot->fw_signature.addr
                                                              ,p_boot->fw_signature.size);
}

static void boot_load_from_server_handle(Bootloader* p_boot){
    if( !p_boot->segment_downloaded.is_last ) return;
    boot_set_state(p_boot, BOOT_ST_DOWNLOAD_COMPLETED);
}


static void boot_reboot_handle(Bootloader* p_boot){
    (void)p_boot;
    // Reset all
    NVIC_SystemReset();
}


static void boot_finish_handle(Bootloader* p_boot){
    (void)p_boot;
    boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);

    //    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    //    Boot_master* p_boot_m = &boot_master;
    //
    //    switch( CO_SDO_get_status(p_sdo) ){
    //        case CO_SDO_RT_idle:
    //        {
    //            CO_Sub_Object boot_state = {.p_data = (uint8_t*)p_boot_m->base.state,
    //                                        .attr   = ODA_SDO_RW,
    //                                        .len    = 1,
    //                                        .p_ext  = NULL
    //            };
    //            CO_SDOclient_start_download(p_sdo, p_boot_m->boot_id_src, SDO_BOOTLOADER_INDEX,
    //                                        SDO_BOOTLOADER_BOOT_STATE_SUB_INDEX,
    //                                        &boot_state,
    //                                        500);
    //        }
    //            break;
    //
    //        case CO_SDO_RT_busy:
    //            break;
    //
    //        case CO_SDO_RT_success:
    //            CO_SDO_reset_status(p_sdo);
    //            if ( mqtt_client_publish_message(&selex_hmi_app.mqtt_client, &boot_master.fota_svr->state.topic) != 0 ){
    //                mqtt_client_set_state(&selex_hmi_app.mqtt_client, MQTT_CLIENT_ST_FAIL);
    //            }
    //            boot_set_state((Bootloader*)&boot_master, BOOT_ST_INIT);
    //            break;
    //
    //        case CO_SDO_RT_abort:
    //            CO_SDO_reset_status(p_sdo);
    //            boot_set_state((Bootloader*)&boot_master, BOOT_ST_INIT);
    //            break;
    //    }
}


static void boot_start_handle(Bootloader* p_boot){

    //    Fota_server* p_svr = boot_master.fota_svr;
    //    if( fota_svr_response_state(p_svr, "ready") ){
    //        boot_set_state(p_boot, BOOT_ST_LOADING_SERVER);
    //        return;
    //    }
    //    boot_set_state(p_boot, BOOT_ST_FAIL);
}


static void boot_save_setting_handle    (Bootloader* p_boot){

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
                                &fw_size, 500);
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
                                &fw_crc, 500);
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
                                &fw_version, 500);
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
        //            if(sdo_svr->retry_cnt < SDO_SEGMENT_WRITE_RETRY_NUM){
        //                sdo_svr->retry_cnt++;
        //                break;
        //            }
        //            p_seg->write_state = SEGMENT_WRITE_FAIL;
        //            sdo_svr->retry_cnt = 0;
        break;
    }
}










//static void fota_svr_others_write_fw_info_handle    (Fota_server* p_svr){
//    (void)p_svr;
//
//    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
//    Boot_master* p_boot_m = &boot_master;
//
////    // TEST
//    p_sdo->status = CO_SDO_RT_success;
////    // TEST
//
//    switch( CO_SDO_get_status(p_sdo) ){
//        case CO_SDO_RT_idle:
//        {
//            CO_Sub_Object fw_version = {.p_data = p_boot_m->fw_signature.version,
//                                        .attr   = ODA_SDO_RW,
//                                        .len    = 3,
//                                        .p_ext  = NULL
//            };
//            CO_SDOclient_start_download(p_sdo,
//                                        p_boot_m->boot_id_src,
//                                        SDO_BOOTLOADER_INDEX,
//                                        SDO_BOOTLOADER_FW_VERSION_SUB_INDEX,
//                                        &fw_version, 50000);
//        }
//            break;
//
//        case CO_SDO_RT_busy:
//            break;
//
//        case CO_SDO_RT_success:
//            CO_SDO_reset_status(p_sdo);
//            if( fota_svr_response_state(p_boot_m->fota_svr, "ok") ){
//                boot_set_state((Bootloader*)p_boot_m, BOOT_ST_PREPARING);
//                break;
//            }
//            boot_set_state((Bootloader*)p_boot_m, BOOT_ST_FAIL);
//            break;
//
//        case CO_SDO_RT_abort:
//            CO_SDO_reset_status(p_sdo);
//            boot_set_state((Bootloader*)p_boot_m, BOOT_ST_FAIL);
//            break;
//    }
//}


//static void fota_svr_validate_new_fw_handle(Fota_server* p_svr){
//    if( !boot_master.fw_signature.is_valid ) return;
//    fota_svr_response_state(p_svr, "valid");
//    boot_set_state((Bootloader*)&boot_master, BOOT_ST_FINISH);
//}


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
                                5000);
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
                                5000);
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
                                5000);
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
                                    300);
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
                                    300);
    }
    if (CO_SDO_get_status(p_sdo) == CO_SDO_RT_abort ){
        CO_SDO_reset_status(p_sdo);
        //boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
    }
    else if(CO_SDO_get_status(p_sdo) == CO_SDO_RT_success){
        CO_SDO_reset_status(p_sdo);
        boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
        return;
    }
}
