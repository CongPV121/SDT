/*
 * segment_driver.h
 *
 *  Created on: Mar 15, 2022
 *      Author: khanh
 */

#ifndef SERVICE_SEGMENT_DRIVER_SEGMENT_DRIVER_H_
#define SERVICE_SEGMENT_DRIVER_SEGMENT_DRIVER_H_

#include "stdbool.h"
#include "stdint.h"

#define SEGMENT_BLANK   10

typedef struct Digit_bitmap_t Digit_bitmap;
struct Digit_bitmap_t{
    uint8_t  a:1;
    uint8_t  b:1;
    uint8_t  c:1;
    uint8_t  d:1;
    uint8_t  e:1;
    uint8_t  f:1;
    uint8_t  g:1;
};

typedef struct bits_t bits;
struct bits_t{
    uint8_t    b0:1;
    uint8_t    b1:1;
    uint8_t    b2:1;
    uint8_t    b3:1;
    uint8_t    b4:1;
    uint8_t    b5:1;
    uint8_t    b6:1;
    uint8_t    b7:1;
};

typedef struct Segment_element_t Seg_element;
struct Segment_element_t{
    int32_t  value;
    bool     is_blink;
    void     (*update_segment_data) (Seg_element*, const int32_t);
    void     (*write_segment_buffer)(Seg_element*, const int32_t);
};

typedef union Segment_bytes_t Segment_bytes;
union Segment_bytes_t{
    uint8_t byte;
    bits    bits;
};

void segment_clear_digit_value(Digit_bitmap* p_seg, const uint8_t digit_num);
void segment_set_error_value(Digit_bitmap* p_seg, const uint8_t digit_num);
void segment_update_digit_value(Digit_bitmap* p_seg, const uint8_t digit_num, const uint8_t min_digit_show, const int32_t val);
void segment_icon_blink(Seg_element* p_seg, uint8_t blink_src);
void segment_digit_blink(Seg_element* p_seg, uint8_t blink_src);

static inline void update_segment_data(Seg_element* p_seg, const int32_t new_val){
    p_seg->update_segment_data(p_seg, new_val);
}

static inline void write_segment_data(Seg_element* p_seg, const int32_t new_val){
    p_seg->write_segment_buffer(p_seg, new_val);
}

static inline void blink_segment_icon(Seg_element* p_seg, bool blink_state){
    p_seg->is_blink = blink_state;
}

#endif /* SERVICE_SEGMENT_DRIVER_SEGMENT_DRIVER_H_ */
