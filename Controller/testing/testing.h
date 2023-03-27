#ifndef TESTING_H
#define TESTING_H

#include <QObject>
#include "Controller/app_co/od/od.h"
#include "Controller/testing/hmi_testing/hmi_testing.h"

class testing : public QObject
{
    Q_OBJECT
public:

    explicit testing(QObject *parent = nullptr);
};

typedef struct sdo_msg_buff_t sdo_msg_buff;
typedef struct sdo_send_mailbox_t sdo_send_mailbox;

struct sdo_msg_buff_t{

    void        (*method)(void);
    void        (*response_fucntion)(void);
    uint32_t    time_delay_10ms;// time delay before start


};

struct sdo_send_mailbox_t{
    sdo_msg_buff    sdo_send_msg[32];
    uint16_t        msg_waiting = 0;

};

extern sdo_send_mailbox SDO_mailbox ;

void testing_sdo_process            (sdo_send_mailbox *mailbox);
bool push_data_into_queue_to_send(void (*method)(void),void (*response)(void),
                                  uint32_t time_delay);

#endif // TESTING_H
