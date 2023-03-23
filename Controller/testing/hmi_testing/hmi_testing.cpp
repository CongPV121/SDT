#include "hmi_testing.h"
#include "Controller/app_co/od/od.h"

hmi_testing::hmi_testing(QObject *parent) : QObject(parent)
{

}
hmi_testing test[3];
void send_test_hmi_icon(void){

    uint8_t data = 1;
    CO_Sub_Object test_object = {.p_data = &data,
                             .attr   = ODA_SDO_RW,
                             .len    = 1,
                             .p_ext  = NULL
                            };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                HMI_TESTING_SDO_INDEX,
                                TEST_ICON_SDO_SUBINDEX,
                                &test_object, 3000);
}
void send_test_hmi_blue(void){
    uint8_t data = 1;
    CO_Sub_Object test_object = {.p_data = &data,
                             .attr   = ODA_SDO_RW,
                             .len    = 1,
                             .p_ext  = NULL
                            };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                HMI_TESTING_SDO_INDEX,
                                TEST_BLUE_SDO_SUBINDEX,
                                &test_object, 3000);
}
void send_test_hmi_4G(void){
    uint8_t data = 1;
    CO_Sub_Object test_object = {.p_data = &data,
                             .attr   = ODA_SDO_RW,
                             .len    = 1,
                             .p_ext  = NULL
                            };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                SDO_BOOTLOADER_INDEX,
                                TEST_4G_SDO_SUBINDEX,
                                &test_object, 3000);
}
//static void segment_fw_write_process      (Segment_fw* p_seg, void (*method)(Segment_fw*), WRITE_SEGMENT_FW_STATE next_state);

static void testing_sdo_process(){
    CO_SDO* p_sdo = &CO_DEVICE.sdo_client;

    switch( CO_SDO_get_status(p_sdo) ){
    case CO_SDO_RT_idle:
        //method(p_seg);
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
