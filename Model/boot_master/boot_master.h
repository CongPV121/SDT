/*
 * boot_master.h
 *
 *  Created on: Jun 18, 2022
 *      Author: khanh
 */

#ifndef SERVICE_BOOT_MASTER_BOOT_MASTER_H_
#define SERVICE_BOOT_MASTER_BOOT_MASTER_H_

#include "Model/boot_master/bootloader.h"

typedef struct Boot_master_t Boot_master;
struct Boot_master_t{
    Bootloader      base;
    uint32_t        boot_id_src;                // Node ID of CAN
    uint16_t        total_segment;
    uint8_t         *data_firmware;
    Signature       fw_signature;
};

#endif /* SERVICE_BOOT_MASTER_BOOT_MASTER_H_ */
