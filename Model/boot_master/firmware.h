/*
 * firmware.h
 *
 *  Created on: Jun 13, 2022
 *      Author: khanh
 */

#ifndef SERVICE_FIRMWARE_FIRMWARE_H_
#define SERVICE_FIRMWARE_FIRMWARE_H_

#include "segment_firmware.h"

typedef struct Signature_t Signature;
struct Signature_t{
    uint8_t  version[3];
    uint32_t addr;
    uint32_t size;
    uint16_t crc;
    bool     is_valid;
};

typedef struct Firmware_t Firmware;
struct Firmware_t{
    Signature   signature;
    Segment_fw* segment;
    bool        valid_state;
    uint32_t    signature_addr;
    bool        (*is_valid)(Firmware*);
    bool        (*write_segment)(Firmware*);
    bool        (*get_info)(Firmware*);
    void        (*clear_all)(Firmware*);
    void        (*save_signature)(Firmware*);
};

void firmware_update_signature  (Firmware* fw, uint8_t* buff);
void firmware_set_signature     (Firmware* fw, uint8_t* buff);

static inline bool firmware_is_valid(Firmware* fw){
    return fw->is_valid(fw);
}

static inline bool firmware_write_segment(Firmware* fw){
    return fw->write_segment(fw);
}

static inline bool firmware_get_info(Firmware* fw){
    return fw->get_info(fw);
}

static inline void firmware_clear_all(Firmware* fw){
    return fw->clear_all(fw);
}

static inline void firmware_save_signature(Firmware* fw){
    fw->save_signature(fw);
}

#endif /* SERVICE_FIRMWARE_FIRMWARE_H_ */
