#include "bp_tesing.h"
#include "Controller/app_co/pdo/pdo.h"
#include "Controller/testing/testing.h"
#include "views/bp.h"
#include "Controller/config/config.h"
#include "Controller/app_co/sdo/sdo.h"
bp_tesing::bp_tesing()
{

}
void static bp_hw_version_sucsess();
void static bp_fw_version_sucsess();
void static bp_sn_show_sucsess();
void static bp_device_mating_sucsess();

void read_bp_infor_config(void){

    push_data_into_queue_to_send(read_sn,
                                 bp_sn_show_sucsess,
                                 NULL,
                                 0);
    push_data_into_queue_to_send(read_hw_bp_version,
                                 bp_hw_version_sucsess,
                                 NULL,
                                 0);
    push_data_into_queue_to_send(read_fw_bp_version,
                                 bp_fw_version_sucsess,
                                 NULL,
                                 0);
    push_data_into_queue_to_send(read_device_mating,
                                 bp_device_mating_sucsess,
                                 NULL,
                                 0);
    push_data_into_queue_to_send(request_pdo1,
                                 NULL,
                                 NULL,
                                 10);
    push_data_into_queue_to_send(request_pdo2,
                                 NULL,
                                 NULL,
                                 10);
    push_data_into_queue_to_send(request_pdo3,
                                 NULL,
                                 NULL,
                                 10);
    push_data_into_queue_to_send(request_pdo4,
                                 NULL,
                                 NULL,
                                 10);
    push_data_into_queue_to_send(request_pdo5,
                                 NULL,
                                 NULL,
                                 10);
    push_data_into_queue_to_send(request_pdo6,
                                 NULL,
                                 NULL,
                                 10);
}

void  read_sn(void){
    memset(BP_infor.sn,0,32);
    CO_Sub_Object test_object = {.p_data = BP_infor.sn,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 32,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_upload(&CO_DEVICE.sdo_client,
                              0,
                              0x2003,
                              0,
                              &test_object, 3000);
}

void  read_hw_bp_version(void){
    memset(BP_infor.hw_ver,0,32);
    CO_Sub_Object test_object = {.p_data = BP_infor.hw_ver,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 32,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_upload(&CO_DEVICE.sdo_client,
                              0,
                              0x1009,
                              0,
                              &test_object, 3000);
}

void  read_fw_bp_version(void){
    memset(BP_infor.fw_ver,0,32);
    CO_Sub_Object test_object = {.p_data = BP_infor.fw_ver,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 32,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_upload(&CO_DEVICE.sdo_client,
                              0,
                              0x100A,
                              0,
                              &test_object, 3000);
}
void  read_device_mating(void){
    memset(BP_infor.device_mating,0,32);
    CO_Sub_Object test_object = {.p_data = BP_infor.device_mating,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 32,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_upload(&CO_DEVICE.sdo_client,
                              0,
                              0x2004,
                              1,
                              &test_object, 3000);
}

uint8_t pdo1_id = 1;

void  request_pdo1(void){
    CO_Sub_Object test_object = {.p_data = (uint8_t *)&pdo1_id,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 1,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                0x2006,
                                0,
                                &test_object, 3000);
}
uint8_t pdo2_id = 2;

void  request_pdo2(void){
    CO_Sub_Object test_object = {.p_data = (uint8_t *)&pdo2_id,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 1,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                0x2006,
                                0,
                                &test_object, 3000);
}
uint8_t pdo3_id = 3;

void  request_pdo3(void){
    CO_Sub_Object test_object = {.p_data = (uint8_t *)&pdo3_id,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 1,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                0x2006,
                                0,
                                &test_object, 3000);
}
uint8_t pdo4_id = 4;

void  request_pdo4(void){
    CO_Sub_Object test_object = {.p_data = (uint8_t *)&pdo4_id,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 1,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                0x2006,
                                0,
                                &test_object, 3000);
}
uint8_t pdo5_id = 5;

void  request_pdo5(void){
    CO_Sub_Object test_object = {.p_data = (uint8_t *)&pdo5_id,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 1,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                0x2006,
                                0,
                                &test_object, 3000);
}
uint8_t pdo6_id = 6;

void  request_pdo6(void){
    CO_Sub_Object test_object = {.p_data = (uint8_t *)&pdo6_id,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 1,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                0x2006,
                                0,
                                &test_object, 3000);
}
void bp_hw_version_show(QString s_value);
void bp_fw_version_show(QString s_value);
void bp_sn_show(QString s_value);
void bp_device_mating_show(QString s_value);

void static bp_hw_version_sucsess(){
    QString s_value;
    for(uint8_t i = 0; i < 3; i++){
        s_value += QString::number(BP_infor.hw_ver[2-i]);
        s_value += ".";
    }
    bp_hw_version_show(s_value);
}
void static bp_fw_version_sucsess(){
    QString s_value;
    for(uint8_t i = 0; i < 3; i++){
        s_value += QString::number(BP_infor.fw_ver[2-i]);
        s_value += ".";
    }
    bp_fw_version_show(s_value);
}
void static bp_sn_show_sucsess(){
    QString sn =QString((char*)BP_infor.sn);
    QString snRev;
    for (int i = sn.length() - 1; i >= 0; --i) {
        snRev.append(sn.at(i));
    }
    bp_sn_show(snRev);
}
void static bp_device_mating_sucsess(){
    bp_device_mating_show(QString((char*)BP_infor.device_mating));
}
/* Write bp config paramater*/

static char device_sn[32];
bool write_device_mating( QString value ){
    if(value.length() < 8){
        return 0;
    }
    memset(device_sn,0,32);
    QByteArray ba;
    ba = value.toLatin1();
    const char* path = ba.data();
    memcpy(device_sn,path,value.length());

    push_data_into_queue_to_send(send_device_sn_mating_bp,
                                 NULL,
                                 NULL,
                                 0);
    return 1;
}
void  send_device_sn_mating_bp(void){
    CO_Sub_Object test_object = {.p_data = device_sn,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 32,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                MATING_INDEX,
                                VEHICLE_SN_OBJECT_SUB_INDEX,
                                &test_object, 3000);
}
static char bp_sn[41];

bool  write_sn_number( QString value ){
    if(value.length() < 8){

        return 0;
    }
    memset(bp_sn,0,41);
    /* Write key*/
    QString key = wirteConfigKey;
    QByteArray key_arr = key.toLatin1();
    const char* key_c = key_arr.data();
    memcpy(bp_sn,key_c,9);
    /* Write data*/
    QString valueRev;
    for (int i = value.length() - 1; i >= 0; --i) {
        valueRev.append(value.at(i));
    }
    QByteArray ba;
    ba = valueRev.toLatin1();
    const char* path = ba.data();
    memcpy(bp_sn + 9,path,valueRev.length());

    push_data_into_queue_to_send(send_sn_bp,
                                 NULL,
                                 NULL,
                                 10);
    return 1;

}
void  send_sn_bp(void){
    CO_Sub_Object test_object = {.p_data = bp_sn,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 41,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_download(&CO_DEVICE.sdo_client,
                                0,
                                BMS_CONFIG_INDEX,
                                WRITE_SERIAL_NUMBER_SUB_INDEX,
                                &test_object, 3000);
}
