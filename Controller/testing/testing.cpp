#include "testing.h"
#include "Controller/app_co/pdo/pdo.h"
#include "Controller/app_co/od/od.h"
#include "Controller/app_co/sdo/sdo.h"
#include "views/product_testing.h"

QVector<testsiute> JigTestList;

testing::testing(QObject *parent) : QObject(parent)
{

}

#define JIG_NODEID                                      126
#define JIG_PDO1                                        (0x181 + JIG_NODEID)

static MSG_buff jig_pdo;
void pdo_testing_process_handle(uint32_t canid, uint8_t *data){
    uint32_t cob_id = canid & 0xFFFFFF80;

    uint8_t node_id = (uint8_t) (canid & 0x7F);
    if (node_id != JIG_NODEID){
        return;
    }
    switch (cob_id) {
    case JIG_PDO1:

        jig_pdo.new_msg = true;
        memcpy(jig_pdo.data, data, 8);
        break;
    default:
        break;

    }
}
uint8_t testCaseID;

void pdo_testing_processing(void) {

    if (jig_pdo.new_msg == true) {
        jig_pdo.new_msg = false;
        if(jig_pdo.data[6] == STATUS_SFPI_success){
            testCaseID = jig_pdo.data[7];
            push_data_into_queue_to_send(read_testing_result,
                                         update_table_testing_result,NULL,10);
        }
    }
}

uint8_t test_result[1024];

void  read_testing_result(void){
    memset(test_result,0,1024);
    CO_Sub_Object test_object = {.p_data = BP_infor.sn,
                                 .attr   = ODA_SDO_RW,
                                 .len    = 32,
                                 .p_ext  = NULL
                                };
    CO_SDOclient_start_upload(&CO_DEVICE.sdo_client,
                              0,
                              0x2002,
                              1,
                              &test_object, 3000);
}
void update_table_testing_result(void){

     update_testing_result( testCaseID, test_result);

}
