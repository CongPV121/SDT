#include "pdo.h"
#include <stdbool.h>
#include <string.h>
BP_PDO BP_data;

//pdo::pdo()
//{

//}
void pdo_process_handle(uint32_t canid, uint8_t *data){

    uint32_t cob_id = canid & 0xFFFFFF80;

//    if( (  cob_id != 0x180)
//        ||(cob_id != 0x280)
//        ||(cob_id != 0x380)
//        ||(cob_id != 0x480)
//        ||(cob_id != 0x200)
//        ||(cob_id != 0x300)) {

//    }



    uint8_t node_id = (uint8_t) (canid & 0x7F);
    if (node_id != 0){
        return;
    }

    switch (cob_id) {
    case BP_VOL_CUR_TPDO_COBID:

        BP_data.BP_PDO1.new_msg = true;
        memcpy(BP_data.BP_PDO1.data, data, 8);
        break;
    case BP_1_4CELLS_VOL_TPDO_COBID:
        BP_data.BP_PDO2.new_msg = true;
        memcpy(BP_data.BP_PDO2.data, data, 8);
        break;
    case BP_5_8CELLS_VOL_TPDO_COBID:
        BP_data.BP_PDO3.new_msg = true;
        memcpy(BP_data.BP_PDO3.data, data, 8);
        break;
    case BP_TEMP_TPDO_COBID:
        BP_data.BP_PDO4.new_msg = true;
        memcpy(BP_data.BP_PDO4.data, data, 8);
        break;
    case BP_9_12CELLS_VOL_TPDO_COBID:
        BP_data.BP_PDO5.new_msg = true;
        memcpy(BP_data.BP_PDO5.data, data, 8);
        break;
    case BP_13_16CELLS_VOL_TPDO_COBID:
        BP_data.BP_PDO6.new_msg = true;
        memcpy(BP_data.BP_PDO6.data, data, 8);
        break;
    default:
        break;

    }
}
