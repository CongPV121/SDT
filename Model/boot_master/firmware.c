/*
 * firmware.c
 *
 *  Created on: Jun 13, 2022
 *      Author: khanh
 */

#include "firmware.h"
#include "string.h"
#include "CO_utils.h"

/* Flash layout for Firmware Signature (bytes index):
 * [0 - 3]   size
 * [4 - 7]   flash base address
 * [8]       valid state
 * [9 - 11]  firmware version
 * [12 - 13] crc-16 code
 */

void firmware_update_signature (Firmware* this, uint8_t* buff) {

    this->signature.size = CO_getUint32(buff);
    this->signature.addr = CO_getUint32(buff+4);
    this->signature.is_valid = buff[8];
    memcpy(this->signature.version, buff+9, 3);
    this->signature.crc  = CO_getUint16(buff+12);
}

void firmware_set_signature (Firmware* this, uint8_t* buff) {

    CO_setUint32(buff, this->signature.size);
    CO_setUint32(buff+4, this->signature.addr);
    buff[8] = this->signature.is_valid;
    memcpy(buff+9, this->signature.version, 3);
    CO_setUint16(buff+12, this->signature.crc);
}

