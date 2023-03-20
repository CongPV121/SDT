/*
 * intel_hex.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Admin
 */

#ifndef MAIN_APP_OTA_BMS_INTEL_HEX_H_
#define MAIN_APP_OTA_BMS_INTEL_HEX_H_


#include "stdio.h"
#include "stdlib.h"
#include "math.h"

typedef enum{
	INTEL_HEX_Data = 0x00,
	INTEL_HEX_EndFile= 0x01,
	INTEL_HEX_Extended_Segment_Address = 0x02, // mcu 32bit not user
	INTEL_HEX_Start_Segment_Address = 0x03, // mcu 32bit not user
	INTEL_HEX_Extended_Linear_Address = 0x04,
	INTEL_HEX_Start_Linear_Address = 0x05
}Record_type_t;

typedef struct intel_hex_t intel_hex;

struct intel_hex_t{
	uint8_t start_code; // 1 byte
	uint8_t byte_count;// 1 byte
	uint8_t addr[2]; //2 byte
	Record_type_t record_type; //1 byte
	uint8_t *data; // (1 * byte_count) byte
	uint8_t checksum; // 1 byte
};



intel_hex* intel_hex_process(uint8_t* data, uint16_t length);
uint8_t intel_hex_checksum(uint8_t* data, uint16_t length);

typedef union{
	uint32_t word;
	uint8_t byte[4];
}word_to_byte_t;

typedef union{
	uint16_t haftword;
	uint8_t byte[2];
}haftword_to_byte_t;

int string_to_hex(char* data, uint16_t length,uint8_t *dest);
uint16_t byte_to_hardword(uint8_t* src);
uint32_t byte_to_word(uint8_t* src);
uint32_t byte_to_word_cr(uint8_t* src);

#endif /* MAIN_APP_OTA_BMS_INTEL_HEX_H_ */
