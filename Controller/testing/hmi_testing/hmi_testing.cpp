#include "hmi_testing.h"
#include "Controller/testing/testing.h"
#include "Controller/app_co/od/od.h"

bool testing_hmi = 0;


hmi_testing::hmi_testing(QObject *parent) : QObject(parent)
{

}
hmi_testing test[3];



void read_hmi_infor_config(void){
    push_data_into_queue_to_send(read_device_serial_number,0);
    push_data_into_queue_to_send(read_device_serial_number,0);
}


/*  ______________ download_________________*/

uint8_t data_hmi = 1;
void send_active_test_hmi_icon(void){

    CO_Sub_Object test_object = {.p_data = (uint8_t *)&data_hmi,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 1,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                HMI_TESTING_SDO_INDEX,
                                TEST_ACTIVE_ICON_SDO_SUBINDEX,
                                &test_object, 3000);
}
void send_test_hmi_icon(void){

    CO_Sub_Object test_object = {.p_data = (uint8_t *)&data_hmi,
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
                                HMI_TESTING_SDO_INDEX,
                                TEST_4G_SDO_SUBINDEX,
                                &test_object, 3000);
}
/*  ______________ upload_________________*/

uint8_t device_serial[32];
void read_device_serial_number(void){
    memset(device_serial,0,32);
    CO_Sub_Object fw_version = {.p_data = device_serial,
                                .attr   = ODA_SDO_RW,
                                .len    = 32,
                                .p_ext  = NULL
                               };
    CO_SDOclient_start_upload  (&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                HMI_CONFIG_SDO_INDEX,
                                HMI_SERI_NUMBER_SDO_SUBINDEX,
                                &fw_version, 500);

}
uint8_t esim_number[32];

void read_esim_number(void){
    memset(esim_number,0,32);
    CO_Sub_Object fw_version = {.p_data = esim_number,
                                .attr   = ODA_SDO_RW,
                                .len    = 32,
                                .p_ext  = NULL
                               };
    CO_SDOclient_start_upload  (&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                HMI_CONFIG_SDO_INDEX,
                                HMI_ESIM_NUMBER_SDO_SUBINDEX,
                                &fw_version, 500);

}
uint8_t fw_version_arr[4];

void read_fw_version(void){
    memset(fw_version_arr,0,4);
    CO_Sub_Object fw_version = {.p_data = fw_version_arr,
                                .attr   = ODA_SDO_RW,
                                .len    = 32,
                                .p_ext  = NULL
                               };
    CO_SDOclient_start_upload  (&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                HMI_CONFIG_SDO_INDEX,
                                HMI_FW_VERSION_SDO_SUBINDEX,
                                &fw_version, 500);

}
uint8_t hw_version_arr[4];

void read_hw_version(void){
    memset(hw_version_arr,0,4);
    CO_Sub_Object fw_version = {.p_data = hw_version_arr,
                                .attr   = ODA_SDO_RW,
                                .len    = 32,
                                .p_ext  = NULL
                               };
    CO_SDOclient_start_upload  (&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                HMI_CONFIG_SDO_INDEX,
                                HMI_HW_VERSION_SDO_SUBINDEX,
                                &fw_version, 500);

}
/*  ______________ sdo_ext_confirm_function_________________*/

