/*
 * app_boot_config.h
 *
 *  Created on: May 19, 2022
 *      Author: khanh
 */

#ifndef APP_CONFIG_APP_BOOT_CONFIG_H_
#define APP_CONFIG_APP_BOOT_CONFIG_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "Model/canopen/CO.h"


#define MAX_IMAGE_NUM                       2

#define FLASH_IMAGE_BOOT_ADDR               FLASH_HP_CF_BLOCK_0
#define FLASH_IMAGE_1_ADDR                  0
#define FLASH_IMAGE_2_ADDR                  FLASH_HP_CF_BLOCK_11
/* Starting address of firmware mainapp*/
#define BMS_MAIN_APP_FIRM_ADDR              0x0010000

#define BOOT_COMMON_SETTING_ADDR            FLASH_HP_DF_BLOCK_0

#define FLASH_IMAGE_BLOCK_NUM               3
#define FLASH_IMAGE_BLOCK_SIZE              FLASH_HP_CF_BLOCK_SIZE_32KB

#define SEGMENT_MEMORY_SIZE                 1024               // Bytes
#define NUMBER_OF_SEGMENT	                96
// Bytes

typedef enum{
    PMU_MAINAPP_NODE_ID = 1,
    MC_MAINAPP_NODE_ID = 2,
    BP_MAINAPP_NODE_ID = 4,
    HMI_MAINAPP_NODE_ID = 8

} DEVICE_NODEID;



typedef struct{
    uint16_t        start_download;
    DEVICE_NODEID   nodeid_device;
    char            src_data_firmware[1024];
    uint32_t        flash_image_start;

}boot_master_config_t ;



extern bool active_download_button;

extern boot_master_config_t boot_master_config;

void set_download_firmware_par( uint16_t start_download,
                                uint16_t nodeid_device,
                                char src_firmware[],
                                uint32_t flash_download_start);
void active_download_firmware(void);

#ifdef __cplusplus
}
#endif
#endif /* APP_CONFIG_APP_BOOT_CONFIG_H_ */
