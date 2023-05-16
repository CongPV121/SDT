#include "pdo.h"
#include <stdbool.h>
#include <string.h>
#include "Controller/app_co/init/app_co_init.h"

BP_PDO BP_data;
BP_infor_t BP_infor;

void pdo_bp_process_handle(uint32_t canid, uint8_t *data){

    uint32_t cob_id = canid & 0xFFFFFF80;

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

bool pdo_data_processing(void) {
    //PDO_t pdo = p_app->base.PDO;

    /* BP data processing*/
    uint32_t vol_buff;
    int32_t cur_buff;
    bool new_data = false;
    if (BP_data.BP_PDO1.new_msg == true) {

        uint8_t BP_TPDO1_data[8];
        CO_memcpy(BP_TPDO1_data, BP_data.BP_PDO1.data, 8);
        vol_buff = 10 * (uint32_t) CO_getUint16(BP_TPDO1_data);
        if (vol_buff > 30000 && vol_buff < 75000) {
            BP_infor.vol = vol_buff;
        }
        cur_buff = (-10) * ((int16_t) CO_getUint16(BP_TPDO1_data + 2));
        if (cur_buff > -80000 && cur_buff < 80000) {
            BP_infor.cur = cur_buff;
        }
        BP_infor.soc = BP_TPDO1_data[4];
        BP_infor.soc_x10 = 10 * BP_TPDO1_data[4];
        BP_infor.state = BP_TPDO1_data[5];
        BP_infor.status = CO_getUint16(
                    BP_TPDO1_data + 6);
        BP_data.BP_PDO1.new_msg = false;
        new_data = true;

    }
    if (BP_data.BP_PDO2.new_msg == true) {

        for (uint8_t cell = 0; cell < 4; cell++) {
            BP_infor.cell_vol[cell] = CO_getUint16(
                        BP_data.BP_PDO2.data + 2 * cell);
        }
        BP_data.BP_PDO2.new_msg = false;
        new_data = true;


    }
    if (BP_data.BP_PDO3.new_msg == true) {

        for (uint8_t cell = 0; cell < 4; cell++) {
            BP_infor.cell_vol[cell + 4] = CO_getUint16(
                        BP_data.BP_PDO3.data + 2 * cell);
        }
        BP_data.BP_PDO3.new_msg = false;
        new_data = true;

    }
    if (BP_data.BP_PDO4.new_msg == true) {

        CO_memcpy(BP_infor.temp,
                  BP_data.BP_PDO4.data, 6);
        BP_infor.fet_status =
                BP_data.BP_PDO4.data[6];
        uint8_t soc_buff = BP_data.BP_PDO4.data[7];
        if ((soc_buff > 0) && (soc_buff < 10)) {
            BP_infor.soc_x10 += soc_buff;
        }
        BP_data.BP_PDO4.new_msg = false;
        new_data = true;

    }
    if (BP_data.BP_PDO5.new_msg == true) {

        for (uint8_t cell = 0; cell < 4; cell++) {
            BP_infor.cell_vol[cell + 8] = CO_getUint16(
                        BP_data.BP_PDO5.data + 2 * cell);
        }
        BP_data.BP_PDO5.new_msg = false;
        new_data = true;

    }
    if (BP_data.BP_PDO6.new_msg == true) {
        new_data = true;
        for (uint8_t cell = 0; cell < 4; cell++) {
            BP_infor.cell_vol[cell + 12] = CO_getUint16(
                        BP_data.BP_PDO6.data + 2 * cell);
        }
        BP_data.BP_PDO6.new_msg  = false;
    }
    if (BP_data.BP_PDO7.new_msg == true) {
        new_data = true;
        BP_infor.cycle = CO_getUint16( BP_data.BP_PDO6.data);
        BP_infor.soh    = BP_data.BP_PDO6.data[2];


        BP_data.BP_PDO7.new_msg  = false;
    }
    return new_data;
}
