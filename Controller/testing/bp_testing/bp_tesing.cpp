#include "bp_tesing.h"
#include "Controller/testing/testing.h"

bp_tesing::bp_tesing()
{

}
void read_bp_infor_config(void){
    push_data_into_queue_to_send(send_write_node_id,
                                 NULL,
                                 0);
}
uint8_t node_id = 1;

void send_write_node_id(void){

    CO_Sub_Object test_object = {.p_data = (uint8_t *)&node_id,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 1,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                0x2003,
                                2,
                                &test_object, 3000);
}
