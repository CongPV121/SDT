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

void firmware_update_signature  (Firmware* this, uint8_t* buff);
void firmware_set_signature     (Firmware* this, uint8_t* buff);

static inline bool firmware_is_valid(Firmware* this){
    return this->is_valid(this);
}

static inline bool firmware_write_segment(Firmware* this){
    return this->write_segment(this);
}

static inline bool firmware_get_info(Firmware* this){
    return this->get_info(this);
}

static inline void firmware_clear_all(Firmware* this){
    return this->clear_all(this);
}

static inline void firmware_save_signature(Firmware* this){
    this->save_signature(this);
}

#endif /* SERVICE_FIRMWARE_FIRMWARE_H_ */
