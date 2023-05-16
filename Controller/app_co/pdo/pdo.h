#ifndef PDO_H
#define PDO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"

#define BP_VOL_CUR_TPDO_COBID                           0x180
#define BP_1_4CELLS_VOL_TPDO_COBID                     	0x280
#define BP_5_8CELLS_VOL_TPDO_COBID                    	0x380
#define BP_TEMP_TPDO_COBID                              0x480
#define BP_9_12CELLS_VOL_TPDO_COBID                     0x200
#define BP_13_16CELLS_VOL_TPDO_COBID                    0x300

typedef struct {
    bool new_msg;
    uint8_t data[8];
} MSG_buff;
typedef struct {
    MSG_buff BP_PDO1;
    MSG_buff BP_PDO2;
    MSG_buff BP_PDO3;
    MSG_buff BP_PDO4;
    MSG_buff BP_PDO5;
    MSG_buff BP_PDO6;
    MSG_buff BP_PDO7;

} BP_PDO;
typedef enum {
    BP_STT_OK		= 0,
    BP_STT_RSVD_0	= 1,
    BP_STT_CUV 		= 4,
    BP_STT_COV 		= 8,
    BP_STT_OCC 		= 16,
    BP_STT_OCD1 	= 32,
    BP_STT_OCD2		= 64,
    BP_STT_SCD 		= 128
}BP_STATUS;
typedef enum BMS_SWICTH_STATE{
    BMS_OFF_ENTIRE = 0,
    BMS_ON_ENTIRE = 3,
    BMS_OFF_CHARGE = 4,
    BMS_ON_SOFTSTART = 5,
} BMS_SWICTH_STATE;
typedef enum BP_STATE{
    BP_ST_INIT=0,
    BP_ST_IDLE,
    BP_ST_SOFTSTART,
    BP_ST_DISCHARGING,
    BP_ST_CHARGING,
    BP_ST_FAULT,
    BP_ST_SHIPMODE,
    BP_ST_SYSTEM_BOOST_UP,
    BP_ST_ID_ASSIGN_START,
    BP_ST_ID_ASSIGN_WAIT_CONFIRM,
    BP_ST_ID_ASSIGN_CONFIRMED,
    BP_ST_ID_ASSIGN_WAIT_SLAVE_SELECT,
    BP_ST_START_AUTHENTICATE,
    BP_ST_AUTHENTICATING,
    BP_ST_STANDBY
} BP_STATE;

typedef struct {
    BP_STATE	state;
    BMS_SWICTH_STATE 	sw_state;
    BMS_SWICTH_STATE 	pre_sw_state;
    uint16_t 	sw_state_check_cnt;
    uint8_t 	pos;
    uint8_t 	soc;
    uint16_t 	soc_x10;
    uint8_t 	soh;
    uint32_t 	vol;
    uint32_t 	cur_limit;
    int32_t 	cur;
    uint32_t 	cycle;
    uint16_t 	cell_vol[16];
    uint8_t 	temp[6];
    BP_STATUS 	status;
    uint8_t 	fet_status;
    uint16_t 	cnt_remove_bp_invalid;
    uint8_t     sn[32];
    uint8_t     hw_ver[32];
    uint8_t     fw_ver[32];
    uint8_t     device_mating[32];
    float 		power_discharge;// Wh


}BP_infor_t;

extern BP_PDO BP_data;
extern BP_infor_t BP_infor;

void pdo_bp_process_handle(uint32_t canid, uint8_t *data);
bool pdo_data_processing(void);
#ifdef __cplusplus
}
#endif

#endif // PDO_H
