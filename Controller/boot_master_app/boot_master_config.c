#include "boot_master_config.h"
#include "Model/boot_master/boot_master_process.h"

static void boot_can_request(uint16_t noideID,uint8_t stateRequest,
                             BOOT_STATE nextState, uint32_t mux);

boot_master_config_t boot_master_config = {.start_download = 0};
uint16_t        start_download;
DEVICE_NODEID   nodeid_device;

bool set_download_firmware_par( uint16_t start_download,
                                uint16_t nodeid_device,
                                char src_firmware[],
                                uint32_t flash_download_start,
                                void        (*reboot)(void),
                                void        (*ex_request)(void),
                                void        (*show_proccess)(const int value, uint8_t state_process)){
    BOOT_STATE bootSt = boot_get_state(&boot_master.base);
    if(     bootSt == BOOT_ST_LOADING_LOCAL ||
            bootSt == BOOT_ST_DOWNLOAD_COMPLETED ||
            bootSt == BOOT_ST_LOADING_SERVER){
        return false;
    }
    boot_master_config.start_download       = start_download;
    boot_master_config.nodeid_device        = (DEVICE_NODEID)nodeid_device;
    boot_master_config.flash_image_start    = flash_download_start;
    boot_master_config.reboot               = reboot;
    boot_master_config.ex_request           = ex_request;
    boot_master_config.show_proccess        = show_proccess;
    download_results.download_results       = DOWNLOADING;
    memset(boot_master_config.src_data_firmware,0,1024);
    memcpy(boot_master_config.src_data_firmware,
           src_firmware,
           strlen(src_firmware));

    return true;

}
bool active_download_button = false;
int debounce_fw_download = 0;
void active_download_firmware(void){
    if(debounce_fw_download == 0){
        active_download_button = true;
        debounce_fw_download = 1000; // delay 2000ms
    }
}
static uint8_t reboot_bp_boot1[1] ;
void    boot1_bp_reboot_method (void)
{
    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;
    reboot_bp_boot1[0] = 1;

    if ( CO_SDO_get_status(p_sdo) == CO_SDO_RT_idle ){

        CO_Sub_Object boot_state = { .p_data    = (uint8_t*)reboot_bp_boot1,
                                     .attr      = ODA_SDO_RW,
                                     .len       = 1,
                                     .p_ext     = NULL};
        CO_SDOclient_start_download(p_sdo, 4	, SDO_BOOTLOADER_INDEX,
                                    9,
                                    &boot_state,
                                    100);
    }
    if (CO_SDO_get_status(p_sdo) == CO_SDO_RT_abort ){
        CO_SDO_reset_status(p_sdo);
        //boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
    }
    else if(CO_SDO_get_status(p_sdo) == CO_SDO_RT_success){
        CO_SDO_reset_status(p_sdo);
        boot_set_state(&boot_master.base, BOOT_ST_INIT);
        return;
    }
}

static uint8_t reboot_bp[1] ;
void    bp_reboot_method (void)
{
    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;
    reboot_bp[0] = 1;

    if ( CO_SDO_get_status(p_sdo) == CO_SDO_RT_idle ){

        CO_Sub_Object boot_state = { .p_data    = (uint8_t*)reboot_bp,
                                     .attr      = ODA_SDO_RW,
                                     .len       = 1,
                                     .p_ext     = NULL};
        CO_SDOclient_start_download(p_sdo, 0	, SDO_BOOTLOADER_INDEX,
                                    7,
                                    &boot_state,
                                    100);
    }
    if (CO_SDO_get_status(p_sdo) == CO_SDO_RT_abort ){
        CO_SDO_reset_status(p_sdo);
        //boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
    }
    else if(CO_SDO_get_status(p_sdo) == CO_SDO_RT_success){
        CO_SDO_reset_status(p_sdo);
        boot_set_state(&boot_master.base, BOOT_ST_INIT);
        return;
    }
}
static uint8_t reboot_hmi[1] ;
/*-----------------------------------------------------------------*/
void hmi_reboot_method (void)
{
    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;
    reboot_hmi[0] = 1;

    if ( CO_SDO_get_status(p_sdo) == CO_SDO_RT_idle ){

        CO_Sub_Object boot_state = { .p_data    = (uint8_t*)reboot_hmi,
                                     .attr      = ODA_SDO_RW,
                                     .len       = 1,
                                     .p_ext     = NULL};
        CO_SDOclient_start_download(p_sdo, boot_master.boot_id_src	, SDO_BOOTLOADER_INDEX,
                                    1,
                                    &boot_state,
                                    100);
    }
    if (CO_SDO_get_status(p_sdo) == CO_SDO_RT_abort ){
        CO_SDO_reset_status(p_sdo);
        //boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
    }
    else if(CO_SDO_get_status(p_sdo) == CO_SDO_RT_success){
        CO_SDO_reset_status(p_sdo);
        boot_set_state(&boot_master.base, BOOT_ST_EXT_REQUEST);
        return;
    }
}
/*-----------------------------------------------------------------*/
static uint8_t exRequestData[1] ;
static void boot_can_request(uint16_t noideID,uint8_t stateRequest,
                             BOOT_STATE nextState, uint32_t mux){
    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;
    Boot_master* p_boot_m = &boot_master;
    exRequestData[0] = stateRequest;

    if ( CO_SDO_get_status(p_sdo) == CO_SDO_RT_idle ){

        CO_Sub_Object subOject = { .p_data    = (uint8_t*)exRequestData,
                                   .attr      = ODA_SDO_RW,
                                   .len       = 1,
                                   .p_ext     = NULL};
        CO_SDOclient_start_download(p_sdo, noideID	, (mux >> 8),
                                    (uint8_t) mux,
                                    &subOject,
                                    100);
    }
    if (CO_SDO_get_status(p_sdo) == CO_SDO_RT_abort ){
        CO_SDO_reset_status(p_sdo);
        //boot_set_state(&boot_master.base, BOOT_ST_PRE_INIT);
    }
    else if(CO_SDO_get_status(p_sdo) == CO_SDO_RT_success){
        CO_SDO_reset_status(p_sdo);
        boot_set_state(&boot_master.base, nextState);
        return;
    }
}
/*-----------------------------BP------------------------------------*/
void boot1_bp_reboot (void){
    boot_can_request(0,1,BOOT_ST_EXT_REQUEST,0x200107);
}
void boot1_bp_exRequest (void){
    boot_can_request(BP_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200109);

}
void boot2_bp_reboot (void){
    boot_can_request(0,1,BOOT_ST_INIT,0x200107);

}
void boot2_bp_exRequest (void){
    boot_can_request(BP_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200107);

}
/*---------------------------PMU----------------------------------*/

void boot1_pmu_reboot (void){
    //boot_can_request(PMU_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200101);

}
void boot2_pmu_reboot (void){
    //boot_can_request(PMU_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200101);

}
void boot1_pmu_exRequest (void){
    boot_can_request(PMU_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200109);
}
void boot2_pmu_exRequest (void){
    boot_can_request(PMU_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200107);
}
/*---------------------------MC----------------------------------*/


void boot1_mc_reboot (void){

}
void boot1_mc_exRequest (void){
    boot_can_request(MC_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200109);

}
void boot2_mc_reboot (void){

}
void boot2_mc_exRequest (void){
    boot_can_request(MC_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200107);

}
/*---------------------------HMI----------------------------------*/

void boot1_hmi_reboot (void){

}

void boot2_hmi_reboot (void){

}
void boot1_hmi_exRequest (void){
    boot_can_request(HMI_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200109);

}

void boot2_hmi_exRequest (void){
    boot_can_request(HMI_MAINAPP_NODE_ID,1,BOOT_ST_INIT,0x200107);

}
/*-------------------------------------------------------------*/

void boot1_bp_reconfig (void){

}
void boot1_pmu_reconfig (void){

}
void boot1_mc_reconfig (void){

}
void boot1_hmi_reconfig (void){

}

void boot2_bp_reconfig (void){

}
void boot2_pmu_reconfig (void){

}
void boot2_mc_reconfig (void){

}
void boot2_hmi_reconfig (void){

}





