#include "boot_master_config.h"
#include "Model/boot_master/boot_master_process.h"
boot_master_config_t boot_master_config = {.start_download = 0};
uint16_t        start_download;
DEVICE_NODEID   nodeid_device;

bool set_download_firmware_par( uint16_t start_download,
                                uint16_t nodeid_device,
                                char src_firmware[],
                                uint32_t flash_download_start,
                                void        (*method)(void)){
    BOOT_STATE bootSt = boot_get_state(&boot_master.base);
    if(bootSt == BOOT_ST_LOADING_LOCAL ||
       bootSt == BOOT_ST_DOWNLOAD_COMPLETED ||
       bootSt == BOOT_ST_LOADING_SERVER){
                return false;
    }
    boot_master_config.start_download       = start_download;
    boot_master_config.nodeid_device        = (DEVICE_NODEID)nodeid_device;
    memset(boot_master_config.src_data_firmware,0,1024);
    memcpy(boot_master_config.src_data_firmware,
           src_firmware,
           strlen(src_firmware));
    boot_master_config.flash_image_start    = flash_download_start;
    boot_master_config.reboot               = method;

    download_results.download_results       = DOWNLOADING;
    return true;

}
bool active_download_button = false;
void active_download_firmware(void){
    active_download_button = true;
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
