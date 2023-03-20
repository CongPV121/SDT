/*
 * segment_firmware.h
 *
 *  Created on: Jun 13, 2022
 *      Author: khanh
 */

#ifndef SERVICE_SEGMENT_FIRMWARE_SEGMENT_FIRMWARE_H_
#define SERVICE_SEGMENT_FIRMWARE_SEGMENT_FIRMWARE_H_

#include "stdint.h"
#include "stdbool.h"
#include "CRC.h"
#include "app_boot_config.h"

typedef enum WRITE_SEGMENT_FW_STATE_t WRITE_SEGMENT_FW_STATE;
enum WRITE_SEGMENT_FW_STATE_t{
    SEGMENT_WRITE_NONE = 0,
    SEGMENT_WRITE_ADDR,
    SEGMENT_WRITE_DATA,
    SEGMENT_WRITE_CRC,
    SEGMENT_WRITE_SUCCESS,
    SEGMENT_WRITE_FAIL
};

typedef struct Segment_fw_t Segment_fw;
struct Segment_fw_t{
    WRITE_SEGMENT_FW_STATE write_state;
    uint32_t addr;
    uint16_t size;
    uint16_t id;
    uint16_t crc_code;
    uint8_t  *data;
    uint16_t data_index;
    bool     is_last;
    void     (*write_addr)(Segment_fw*);
    void     (*write_data)(Segment_fw*);
    void     (*write_crc)(Segment_fw*);
};

bool segment_fw_is_valid(Segment_fw*);
void reset_id_segment_download(Segment_fw* p_seg);
static inline void segment_set_addr(Segment_fw* this, uint32_t addr){
    this->addr = addr;
}

static inline void segment_set_data(Segment_fw* this, uint8_t value, uint16_t id){
    this->data_index = id+1;
    this->data[id] = value;
}

static inline void segment_set_crc_code(Segment_fw* this, uint16_t crc){
    this->crc_code = crc;
}


#endif /* SERVICE_SEGMENT_FIRMWARE_SEGMENT_FIRMWARE_H_ */
