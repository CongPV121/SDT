/*
 * boot_master_app.h
 *
 *  Created on: May 11, 2022
 *      Author: khanh
 */

#ifndef APP_BOOT_MASTER_APP_BOOT_MASTER_APP_H_
#define APP_BOOT_MASTER_APP_BOOT_MASTER_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Model/boot_master/boot_master.h"
#include "Controller/app_co/od/od_config.h"
#include "Controller/app_co/od/od.h"

extern Boot_master boot_master;
void boot_master_init(void);
void segment_download_build(void);
void boot_master_process(Boot_master *p_boot_m, uint64_t timestamp);

#ifdef __cplusplus
}
#endif

#endif /* APP_BOOT_MASTER_APP_BOOT_MASTER_APP_H_ */
