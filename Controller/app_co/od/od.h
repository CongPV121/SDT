/*
 * od.h
 *
 *  Created on: Oct 12, 2022
 *      Author: Dakaka
 */
/*
 *		========================================
 *      ============== DON'T EDIT ==============
 *      ========================================
 */
#ifndef APP_APP_CO_OD_OD_H_
#define APP_APP_CO_OD_OD_H_

#include "comm_od/comm_od.h"
#include "manu_od/manu_od.h"

extern CO_OD *p_co_od;

#define SDO_BOOTLOADER_INDEX                (0x2001)
#define SDO_BOOTLOADER_FW_VERSION_SUB_INDEX (0x00)
#define SDO_BOOTLOADER_FW_SIZE_SUB_INDEX    (0x01)
#define SDO_BOOTLOADER_FW_CRC_SUB_INDEX     (0x02)
#define SDO_BOOTLOADER_SEG_ADDR_SUB_INDEX   (0x03)
#define SDO_BOOTLOADER_SEG_DATA_SUB_INDEX   (0x04)
#define SDO_BOOTLOADER_SEG_CRC_SUB_INDEX    (0x05)
#define SDO_BOOTLOADER_BOOT_STATE_SUB_INDEX (0x06)
#define SDO_BOOTLOADER_EXT_BOOT_REQUEST     (0x07)
#define SDO_BOOTLOADER_VALID_VERSION        (0x08)

#endif /* APP_APP_CO_OD_OD_H_ */
