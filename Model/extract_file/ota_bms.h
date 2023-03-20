/*
 * ota_bms.h
 *
 *  Created on: Mar 13, 2023
 *      Author: Admin
 */

#ifndef MAIN_APP_OTA_BMS_OTA_BMS_H_
#define MAIN_APP_OTA_BMS_OTA_BMS_H_


#include "stdio.h"
#include "mbs.h"
#include "intel_hex.h"

void bms_ota_init();
int bms_ota_add(MBS *p_mbs,int bp_index);
#endif /* MAIN_APP_OTA_BMS_OTA_BMS_H_ */
