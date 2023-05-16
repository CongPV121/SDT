#ifndef SDO_H
#define SDO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
/*----------------------SDO BUFF---------------------------------*/

typedef struct sdo_msg_buff_t sdo_msg_buff;
typedef struct sdo_send_mailbox_t sdo_send_mailbox;

struct sdo_msg_buff_t{

    void        (*method)(void);
    void        (*response_fucntion)(void);
    void        (*response_fucntion_abort)(void);
    uint32_t    time_delay_10ms;// time delay before start

};

struct sdo_send_mailbox_t{
    sdo_msg_buff    sdo_send_msg[32];
    uint16_t        msg_waiting ;

};

extern sdo_send_mailbox SDO_mailbox ;

void send_sdo_process            (sdo_send_mailbox *mailbox);
bool push_data_into_queue_to_send(void (*method)(void ),void (*response)(void),
                                  void (*response_fucntion_abort)(void),
                                  uint32_t time_delay);

#ifdef __cplusplus
}
#endif

#endif // SDO_H
