/*
 * app_co_init.h
 *
 *  Created on: Jun 17, 2022
 *      Author: Dakaka
 */

#ifndef APP_APP_CANOPEN_APP_CO_INIT_H_
#define APP_APP_CANOPEN_APP_CO_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Model/canopen/CO.h"
#include "Controller/app_co/od/od_config.h"

extern CO CO_DEVICE;

extern void *tpdo_build_data_impl[TPDO_NUMBER];

void app_co_init(void);

void app_process(void);

void app_co_can_receive(const uint32_t can_id, uint8_t *data);
void can_send(const uint32_t can_id, uint8_t* data,uint32_t dlc);

#ifdef __cplusplus
}
#endif

#endif /* APP_APP_CANOPEN_APP_CO_INIT_H_ */

