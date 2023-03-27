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


class sdo_msg_buff
{
public:

    void        (*method)(void);
    void        (*response_fucntion)(void);
    uint32_t    time_delay_10ms;// time delay before start


};

class sdo_send_mailbox
{
public:

    sdo_msg_buff    sdo_send_msg[32];
    uint16_t        msg_waiting;

};

extern sdo_send_mailbox SDO_mailbox ;

void testing_sdo_process            (sdo_send_mailbox *mailbox);
bool push_data_into_queue_to_send(void (*method)(void),void (*response)(void),
                                  uint32_t time_delay);

#endif // TESTING_H
