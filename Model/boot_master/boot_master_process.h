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

typedef struct {
    uint16_t length;
    bool is_comming;
    uint32_t addr;
    uint8_t *p_data;
    bool end_record;
    bool end_old_segment;
    uint32_t start_addr;
    uint32_t begin_addr;
    uint8_t begin_ota;
    int err;
    uint32_t addr_t;
}seg_firmware;

extern Boot_master      boot_master;
extern proress_results  download_results;

void boot_master_init(void);
void segment_download_build(Boot_master *p_boot_m);
void boot_master_process(Boot_master *p_boot_m,uint64_t timestamp,
                         uint16_t *active_download,
                         uint16_t nodeid_device,
                         char *path,
                         proress_results *download_results);
seg_firmware* unzip_fw(FILE *file);
bool extract_getsegment(FILE *p_file,uint32_t flash_start);

static inline bool boot_master_is_timeout(Boot_master *p_boot_m,uint64_t timestamp){
    return (timestamp >= p_boot_m->base.timeout) && (p_boot_m->base.timeout != 0);
}

static inline void boot_master_update_timeout(Boot_master *p_boot_m,uint64_t timestamp){
    uint64_t timeout = 0;
    switch (boot_get_state((Bootloader*)p_boot_m) ) {
    case BOOT_ST_INIT :
        timeout = 0;
        break;
    case BOOT_ST_PREPARING:
        timeout = 0;
        break;
    case BOOT_ST_LOADING_SERVER:
        timeout = 1000;
        break;
    case BOOT_ST_LOADING_LOCAL:
        timeout = 2000;
        break;
    case BOOT_ST_DOWNLOAD_COMPLETED:
        timeout = 0;
        break;
    case BOOT_ST_FINISH:
        timeout = 2000;
        break;
    case BOOT_ST_FAIL:
        timeout = 0;
        break;
    case BOOT_ST_VALIDATING:
        timeout = 5000;
        break;
    case BOOT_ST_WAITING_EXT_BOOT:
        timeout = 0;
        break;
    case BOOT_ST_WRITE_VERSION:
        timeout = 0;
        break;
    case BOOT_ST_READ_INFO:
        timeout = 0;
        break;
    case BOOT_ST_NOT_ACTIVE:
        timeout = 0;
        break;
    default:
        break;
    }
    p_boot_m->base.timeout = timestamp + timeout;
    if(timeout == 0){
        p_boot_m->base.timeout = 0;
    }

}
#ifdef __cplusplus
}
#endif

#endif /* APP_BOOT_MASTER_APP_BOOT_MASTER_APP_H_ */
