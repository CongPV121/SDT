#include "boot_master_config.h"
#include "Model/boot_master/boot_master_process.h"
boot_master_config_t boot_master_config = {.start_download = 0};
uint16_t        start_download;
DEVICE_NODEID   nodeid_device;

void set_download_firmware_par( uint16_t start_download,
                                uint16_t nodeid_device,
                                char src_firmware[],
                                uint32_t flash_download_start){
    boot_master_config.start_download       = start_download;
    boot_master_config.nodeid_device        = (DEVICE_NODEID)nodeid_device;
    memcpy(boot_master_config.src_data_firmware,
           src_firmware,
           strlen(src_firmware));
    download_results.download_results       = DOWNLOADING;
    boot_master_config.flash_image_start    = flash_download_start;
}
bool active_download_button = false;
void active_download_firmware(void){
    active_download_button = true;
}
