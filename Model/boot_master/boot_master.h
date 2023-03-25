/*
 * boot_master.h
 *
 *  Created on: Jun 18, 2022
 *      Author: khanh
 */

#ifndef SERVICE_BOOT_MASTER_BOOT_MASTER_H_
#define SERVICE_BOOT_MASTER_BOOT_MASTER_H_

#include "Model/boot_master/bootloader.h"
#include "Model/boot_master/boot_master_process.h"

typedef enum{
    NOT_DOWNLOAD    = 0,
    DOWNLOADING     = 1,
    DOWNLOAD_SUCESS = 2,
    DOWNLOAD_FAIL   = 3

}DOWNLOAD_ST ;
typedef struct{
    BOOT_STATE      state;
    DOWNLOAD_ST     download_results;
    uint16_t        percent_complete;
    uint16_t        error_code;
}proress_results ;

typedef struct Boot_master_t Boot_master;
struct Boot_master_t{
    Bootloader      base;
    uint32_t        boot_id_src;                // Node ID of CAN
    uint16_t        total_segment;
    uint8_t         *data_firmware;
    Signature       fw_signature;
    proress_results results;

};
void update_download_process(Boot_master *p_boot_m);

#endif /* SERVICE_BOOT_MASTER_BOOT_MASTER_H_ */
