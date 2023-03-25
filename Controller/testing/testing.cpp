#include "testing.h"
//#include "Controller/testing/hmi_testing/hmi_testing.h"

sdo_send_mailbox SDO_mailbox ={.msg_waiting = 0};
testing::testing(QObject *parent) : QObject(parent)
{

}

bool push_data_into_queue_to_send(void (*method)(void),uint32_t time_delay){
    if(method == NULL){
        return 0;
    }
    if(SDO_mailbox.msg_waiting > 31){
        return 0;
    }
    SDO_mailbox.sdo_send_msg[SDO_mailbox.msg_waiting].method            = method;
    SDO_mailbox.sdo_send_msg[SDO_mailbox.msg_waiting].time_delay_10ms   = time_delay;
    SDO_mailbox.msg_waiting ++;
    return 1;
}
static bool shift_left(sdo_send_mailbox *mailbox){
    for(int i = 0; i < 31; i++){
        mailbox->sdo_send_msg[i] = mailbox->sdo_send_msg[i + 1];
    }
    mailbox->msg_waiting --;
    return 1;
}

void testing_sdo_process(sdo_send_mailbox *mailbox){
    if( mailbox->msg_waiting <= 0 ){
        return;
    }
    if(mailbox->sdo_send_msg[0].method == NULL) {
        shift_left(mailbox);
        return;
    }

    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;

    switch( CO_SDO_get_status(p_sdo) ){
    case CO_SDO_RT_idle:
        if(mailbox->sdo_send_msg[0].time_delay_10ms > 0){
            mailbox->sdo_send_msg[0].time_delay_10ms --;
            break;
        }
        mailbox->sdo_send_msg[0].method();
        shift_left(mailbox);
        break;

    case CO_SDO_RT_busy:
        break;

    case CO_SDO_RT_success:
        CO_SDO_reset_status(p_sdo);
        // p_seg->write_state = next_state;
        break;

    case CO_SDO_RT_abort:
        CO_SDO_reset_status(p_sdo);
        break;
    }
}
