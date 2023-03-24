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
#include "Controller/boot_master_app/boot_master_config.h"

typedef enum {
    SEGMENT_WRITE_NONE = 0,
    SEGMENT_WRITE_ADDR,
    SEGMENT_WRITE_DATA,
    SEGMENT_WRITE_CRC,
    SEGMENT_WRITE_SUCCESS,
    SEGMENT_WRITE_FAIL
}WRITE_SEGMENT_FW_STATE;

typedef struct Segment_fw_t Segment_fw;
struct Segment_fw_t{
    WRITE_SEGMENT_FW_STATE write_state;
    uint32_t addr;
    uint16_t size;
    uint16_t transmitted_seg;
    uint16_t crc_code;
    uint8_t  data[SEGMENT_MEMORY_SIZE];
    uint16_t data_index;
    bool     is_last;
    void     (*write_addr)(Segment_fw*);
    void     (*write_data)(Segment_fw*);
    void     (*write_crc)(Segment_fw*);
    Segment_fw      (*get_segment_download)(Segment_fw*);
};

bool segment_fw_is_valid(Segment_fw*);
void reset_id_segment_download(Segment_fw* p_seg);
static inline void segment_set_addr(Segment_fw* seg_fw, uint32_t addr){
    seg_fw->addr = addr;
}

static inline void segment_set_data(Segment_fw* seg_fw, uint8_t value, uint16_t id){
    seg_fw->data_index = id+1;
    seg_fw->data[id] = value;
}

static inline void segment_set_crc_code(Segment_fw* seg_fw, uint16_t crc){
    seg_fw->crc_code = crc;
}


#endif /* SERVICE_SEGMENT_FIRMWARE_SEGMENT_FIRMWARE_H_ */
