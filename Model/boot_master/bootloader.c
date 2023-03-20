/*
 * boot_slave.c
 *
 *  Created on: May 7, 2022
 *      Author: khanh
 */

#include "bootloader.h"
//#include "app_boot_config.h"

/* Flash layout for Bootloader info (bytes index):
 * [0]          new version flag
 * [1 - 14]     main app signature
 * [15 - 28]    sub app signature
 */
void  boot_read_info (Bootloader* p_boot) {

//    uint8_t buff_size = 29;             // new_ver_flag(1) + main_app_sign(14) + sub_app_sign(14)
//    uint8_t buff[buff_size];
//    memcpy( buff, (uint8_t*)BOOT_COMMON_SETTING_ADDR, buff_size );

//    p_boot->is_new_version = buff[0];
//    firmware_update_signature(&p_boot->main_app, buff+1);
//    firmware_update_signature(&p_boot->sub_app,  buff+15);
}

void boot_update_info (Bootloader* p_boot, uint8_t* buff){

//    buff[0] = p_boot->is_new_version;
//    firmware_set_signature(&p_boot->main_app, buff+1);
//    firmware_set_signature(&p_boot->sub_app,  buff+15);
}
