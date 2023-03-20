/*
 * app_can_config.h
 *
 *  Created on: Jan 10, 2022
 *      Author: Ha
 */

#ifndef APP_CONFIG_APP_CAN_CONFIG_H_
#define APP_CONFIG_APP_CAN_CONFIG_H_

#define TOTAL_CAN_SLAVE_NUM             5
#define TOTAL_BP_NUM                    3

#define PMU_NODE_ID_NUM                 1
#define MC_NODE_ID_NUM                  2
#define HMI_NODE_ID_NUM                 8
#define BP_IDLE_NODE_ID_NUM             4
#define BP_START_NODE_ID_NUM            5

#define CO_SLAVE_INACTIVE_TIMEOUT_mS    1800U

#define MC_INACTIVE_TIMEOUT_mS          1800U
#define PMU_INACTIVE_TIMEOUT_mS         1800U
#define BP_INACTIVE_TIMEOUT_mS          1800U

#define CAN_TIMEOUT_ERR_CODE_DEFAULT    99

#define SDO_BOOTLOADER_INDEX                (0x2001)
#define SDO_BOOTLOADER_FW_VERSION_SUB_INDEX (0x00)
#define SDO_BOOTLOADER_FW_SIZE_SUB_INDEX    (0x01)
#define SDO_BOOTLOADER_FW_CRC_SUB_INDEX     (0x02)
#define SDO_BOOTLOADER_SEG_ADDR_SUB_INDEX   (0x03)
#define SDO_BOOTLOADER_SEG_DATA_SUB_INDEX   (0x04)
#define SDO_BOOTLOADER_SEG_CRC_SUB_INDEX    (0x05)
#define SDO_BOOTLOADER_BOOT_STATE_SUB_INDEX (0x06)
#define SDO_BOOTLOADER_EXT_BOOT_REQUEST     (0x07)
#define MAIN_APP_REQUEST_NEW_FIRMWARE     	(0x01)
#define SDO_BOOTLOADER_VALID_VERSION        (0x08)

#define SDO_SEGMENT_WRITE_RETRY_NUM     5


#define SDO_DEVICE_MODE_INDEX               (0x2130)
#define SDO_DEVICE_MODE_SUB_INDEX           (0x00)

#define SDO_LIMIT_SPEED_INDEX               (0x2140)
#define SDO_LIMIT_SPEED_SUB_INDEX           (0x00)

#endif /* APP_CONFIG_APP_CAN_CONFIG_H_ */
