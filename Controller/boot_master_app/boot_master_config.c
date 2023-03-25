#include "boot_master_config.h"
#include "Model/boot_master/boot_master_process.h"
boot_master_config_t boot_master_config = {.start_download = 0};
uint16_t        start_download;
DEVICE_NODEID   nodeid_device;

void set_download_firmware_par( uint16_t start_download,
                                uint16_t nodeid_device,
                                const char * src_firmware){
    boot_master_config.start_download       = start_download;
    boot_master_config.nodeid_device        = (DEVICE_NODEID)nodeid_device;
    boot_master_config.src_data_firmware    = src_firmware;
    download_results.download_results       = DOWNLOADING;
}
