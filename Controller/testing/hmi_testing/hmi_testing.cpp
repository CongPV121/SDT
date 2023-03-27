#include "hmi_testing.h"
#include "Controller/testing/testing.h"
#include "Controller/app_co/od/od.h"
#include "Controller/controler.h"

bool testing_hmi = 0;


hmi_testing::hmi_testing(QObject *parent) : QObject(parent)
{

}
hmi_testing test[3];



void read_hmi_infor_config(void){
    push_data_into_queue_to_send(read_device_serial_number,
                                 respone_read_device_serial_number,
                                 0);
    push_data_into_queue_to_send(read_fw_version,
                                 respone_read_fw_version,
                                 0);
    push_data_into_queue_to_send(read_hw_version,
                                 respone_read_hw_version,
                                 0);
    push_data_into_queue_to_send(read_esim_number,
                                 respone_read_esim_number,
                                 0);
}
uint8_t hmi_sn[32];

void write_hmi_sn( QString value ){
    if(value.length() < 8){
        return;
    }
    memset(hmi_sn,0,32);
    QByteArray ba;
    ba = value.toLatin1();
    const char* path = ba.data();
    memcpy(hmi_sn,path,value.length());

    push_data_into_queue_to_send(send_write_hmi_sn,
                                 NULL,
                                 0);
}
/*  ______________ download_________________*/
void send_write_hmi_sn(void){

    CO_Sub_Object test_object = {.p_data = hmi_sn,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 16,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                HMI_CONFIG_SDO_INDEX,
                                HMI_DEVICE_NUMBER_SDO_SUBINDEX,
                                &test_object, 3000);
}

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

uint8_t device_serial[32]= "";
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
                                HMI_DEVICE_NUMBER_SDO_SUBINDEX,
                                &fw_version, 500);

}
void respone_read_device_serial_number(void){
    setText_serial_number((char*)device_serial);
}

uint8_t esim_number[32] = "";
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
void respone_read_esim_number (void){
    setText_esim_number((char*)esim_number);
}

uint8_t fw_version_arr[4]= "";

void read_fw_version(void){
    memset(fw_version_arr,0,4);
    CO_Sub_Object fw_version = {.p_data = fw_version_arr,
                                .attr   = ODA_SDO_RW,
                                .len    = 32,
                                .p_ext  = NULL
                               };
    CO_SDOclient_start_upload  (&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                0x100A,
                                0,
                                &fw_version, 500);

}
void respone_read_fw_version(void){
    setText_fw_version(fw_version_arr);
}

uint8_t hw_version_arr[4]=  "";

void read_hw_version(void){
    memset(hw_version_arr,0,4);
    CO_Sub_Object fw_version = {.p_data = hw_version_arr,
                                .attr   = ODA_SDO_RW,
                                .len    = 32,
                                .p_ext  = NULL
                               };
    CO_SDOclient_start_upload  (&CO_DEVICE.sdo_client,
                                HMI_NODE_ID,
                                0x1009,
                                0,
                                &fw_version, 500);

}
void respone_read_hw_version(void){
    setText_hw_version((char*)hw_version_arr);
}
/*  ______________ sdo_ext_confirm_function_________________*/

