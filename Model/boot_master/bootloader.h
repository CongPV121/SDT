/*
 * boot_slave.h
 *
 *  Created on: May 7, 2022
 *      Author: khanh
 */

#ifndef SERVICE_BOOTLOADER_BOOTLOADER_H_
#define SERVICE_BOOTLOADER_BOOTLOADER_H_

#include "stdbool.h"
#include "stdint.h"
#include "Controller/boot_master_app/boot_master_config.h"
#include "Model/boot_master/firmware.h"
#include "Model/boot_master/segment_firmware.h"

typedef enum BOOT_STATE_t{
    BOOT_ST_INIT = 0,
    BOOT_ST_PREPARING,
    BOOT_ST_LOADING_SERVER,
    BOOT_ST_LOADING_LOCAL,
    BOOT_ST_DOWNLOAD_COMPLETED,
    BOOT_ST_FINISH,
    BOOT_ST_FAIL,
    BOOT_ST_VALIDATING,
    BOOT_ST_WAITING_EXT_BOOT,
    BOOT_ST_WRITE_VERSION,
    BOOT_ST_READ_INFO,
    BOOT_ST_NOT_ACTIVE,
    BOOT_ST_EXT_REQUEST
}BOOT_STATE;

typedef struct Bootloader_t Bootloader;
struct Bootloader_t{
    BOOT_STATE  state;
    bool        is_state_change;
    Firmware    fw[MAX_IMAGE_NUM];
    Segment_fw  segment_downloaded;
    uint64_t    timeout;
    Firmware    main_app;
    Firmware    sub_app;
    bool        is_new_version;
    bool        is_ext_boot_request;
    void*       boot_src;
    void        (*start)                 (Bootloader*);
    void        (*download_completed)    (Bootloader*);
    void        (*finish)                (Bootloader*);
    void        (*fail_handle)           (Bootloader*);
    void        (*get_data_from_server)  (Bootloader*);
    void        (*load_data_to_local)    (Bootloader*);
    void        (*save_setting)          (Bootloader*);
    void        (*reboot)                (Bootloader*);
    void        (*request_new_firmware)  (Bootloader*);
    void        (*validate)              (Bootloader*);
};

void boot_read_info     (Bootloader* p_boot);
void boot_update_info   (Bootloader* p_boot, uint8_t* buff);

static inline void boot_start(Bootloader* p_boot){
    p_boot->start(p_boot);
}

static inline void boot_finish(Bootloader* p_boot){
    p_boot->finish(p_boot);
}

static inline void boot_fail_handle(Bootloader* p_boot){
    p_boot->fail_handle(p_boot);
}

static inline void boot_set_state(Bootloader* p_boot, BOOT_STATE state){
    if(p_boot->state == state) return;
    p_boot->state = state;
    p_boot->is_state_change = true;
}

static inline BOOT_STATE boot_get_state(Bootloader* p_boot){
    return p_boot->state;
}

static inline void boot_get_data_from_server(Bootloader* p_boot){
    p_boot->get_data_from_server(p_boot);
}

static inline void boot_set_data_to_local(Bootloader* p_boot){
    p_boot->load_data_to_local(p_boot);
}

static inline void boot_download_completed_handle(Bootloader* p_boot){
    p_boot->download_completed(p_boot);
}

static inline void boot_active_timeout(Bootloader* p_boot, uint32_t timestamp, uint32_t timeout_ms){
    p_boot->timeout = timestamp + timeout_ms;
}

static inline void boot_reset_timeout(Bootloader* p_boot){
    p_boot->timeout = 0;
}

static inline void boot_save_setting(Bootloader* p_boot){
    p_boot->save_setting(p_boot);
}

static inline void boot_reboot(Bootloader* p_boot){
    p_boot->reboot(p_boot);
}
static inline void request_new_firmware(Bootloader* p_boot){
    p_boot->request_new_firmware(p_boot);
}
#endif /* SERVICE_BOOTLOADER_BOOTLOADER_H_ */
