#ifndef TESTING_H
#define TESTING_H

#include <QObject>
#include "Controller/app_co/od/od.h"

class testing : public QObject
{
    Q_OBJECT
public:

    explicit testing(QObject *parent = nullptr);
};

//class sdo_msg_buff
//{
//public:

//    CO_Sub_Object   sdo_object;

//    uint32_t        server_node_id;
//    uint16_t        index;
//    uint8_t         sub_index;
//    uint16_t        allowed_timeout_ms;

//};

//class sdo_send_mailbox
//{
//public:

//    sdo_msg_buff    sdo_send_msg[32];
//    uint16_t        msg_waiting;

//};
//sdo_send_mailbox SDO_mailbox ={.msg_waiting = 0};
//bool push_data_into_queue_to_send(sdo_msg_buff mailbox);
#endif // TESTING_H
