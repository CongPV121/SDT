/*
 * segment_firmware.c
 *
 *  Created on: Jun 13, 2022
 *      Author: khanh
 */

#include "segment_firmware.h"


bool segment_fw_is_valid(Segment_fw* p_seg){

    uint16_t crc_cal = CRC_CalculateCRC16(p_seg->data, p_seg->size);
    return (crc_cal == p_seg->crc_code);
}
void reset_id_segment_download(Segment_fw* p_seg){
	p_seg->id = 0;
}
