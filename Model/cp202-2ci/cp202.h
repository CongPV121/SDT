//
// Created by vnbk on 16/03/2023.
//

#ifndef CO_LIB_CP202_H
#define CO_LIB_CP202_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CP202_HOST_DEFAULT "192.168.1.254"
#define CP202_PORT_DEFAULT 32000

typedef struct cp202 cp202_t;

typedef void (*cp202_can_receive_callback_fn)(const uint32_t, uint8_t*);

cp202_t *cp202_create(const char *host, int port);

cp202_t *cp202_create_default(const char *host, int port);

int cp202_register_recv_callback(cp202_t* self, cp202_can_receive_callback_fn callback_fn);

int cp202_connect(cp202_t *self);

int cp202_disconnect(cp202_t *self);

int cp202_is_connected(cp202_t *self);

int cp202_send(cp202_t *self, uint32_t frame_id, const unsigned char *data, int len, int timeout);

int cp202_recv(cp202_t *self, unsigned char *buf, int max_len, int timeout);

int cp202_process(cp202_t *self);

#ifdef __cplusplus
}
#endif

#endif //CO_LIB_CP202_H
