#ifndef TESTCASE_H
#define TESTCASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
typedef enum{
    TC_DUT_IO1_ID = 10,
    TC_DUT_IO2_ID = 11,
    TC_DUT_IO3_ID = 12,
    TC_JIG_IO1_ID = 20,
    TC_JIG_IO2_ID = 21,
    TC_JIG_IO3_ID = 22,
    TC_JIG_IO4_ID = 23,
    TC_JIG_IO5_ID = 24,
    TC_JIG_IO6_ID = 25,
    TC_JIG_IO7_ID = 26,
    TC_JIG_VOLT1_ID = 30,
    TC_JIG_VOLT2_ID = 31,
    TC_JIG_VOLT3_ID = 32,
    TC_DUT_VOLT1_ID = 40,
    TC_CAN_ID = 50,
    TC_DUT_1_ID = 60,
    TC_BMS_OTP_ID = 70,
    TC_BMS_CELL_VOLT_ID= 71,
    TC_BMS_GATE_DRIVER_ID = 72,
    TC_BMS_SHUTDOWN_ID = 73,
    CM_IO1_ID= 80
}type_TC;
typedef struct TC_DUT_IO1_t         TC_DUT_IO1;
typedef struct TC_DUT_IO2_t         TC_DUT_IO2;
typedef struct TC_DUT_IO3_t         TC_DUT_IO3;
typedef struct TC_JIG_IO1_t         TC_JIG_IO1;
typedef struct TC_JIG_IO2_t         TC_JIG_IO2;
typedef struct TC_JIG_IO3_t         TC_JIG_IO3;
typedef struct TC_JIG_IO4_t         TC_JIG_IO4;
typedef struct TC_JIG_IO5_t         TC_JIG_IO5;
typedef struct TC_JIG_IO6_t         TC_JIG_IO6;
typedef struct TC_JIG_IO7_t         TC_JIG_IO7;
typedef struct TC_JIG_VOLT1_t		TC_JIG_VOLT1;
typedef struct TC_JIG_VOLT2_t		TC_JIG_VOLT2;
typedef struct TC_JIG_VOLT3_t		TC_JIG_VOLT3;
typedef struct TC_DUT_VOLT1_t		TC_DUT_VOLT1;
typedef struct TC_CAN_t             TC_CAN;
typedef struct TC_DUT_1_t           TC_DUT_1;
typedef struct TC_BMS_OTP_t         TC_BMS_OTP;
typedef struct TC_BMS_CELL_VOLT_t		TC_BMS_CELL_VOLT;
typedef struct TC_BMS_GATE_DRIVER_t		TC_BMS_GATE_DRIVER;
typedef struct TC_BMS_SHUTDOWN_t		TC_BMS_SHUTDOWN;
typedef struct CM_IO1_t             CM_IO1;
/*----------------------------------*/

typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
}TC_Can_Result;

typedef struct
{
    /*Common*/
    uint8_t	type;					//<< always byte[0]
    uint32_t timeout_ms;			//<< always byte[1-4]
    /**/
}TC_Can_Para;

typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
    uint8_t actual_level;
}TC_Dut_Io1_Result;
/*----------------------------------*/

typedef struct
{
    /*Common*/
    uint8_t	type;
    uint32_t timeout_ms;			//<< always byte[0-3]
    /**/
    uint8_t dut_tc_id;				//<< DUT test case ID
    uint8_t correct_level;
}TC_Dut_Io1_Para;

typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
    uint8_t logic_1_is_pass;
    uint8_t logic_0_is_pass;
}TC_Dut_Io3_Result;
/*----------------------------------*/

typedef struct
{
    /*Common*/
    uint8_t	type;
    uint32_t timeout_ms;			//<< always byte[1-4]
    /**/
    uint8_t dut_tc_id;				//<< DUT test case ID
    uint8_t io_output_x_channel;
}TC_Dut_Io3_Para;
/*----------------------------------*/
typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
    uint32_t avg_volt_mv;
    uint32_t ripple_volt_mv;
}TC_Dut_Volt1_Result;

typedef struct
{
    /*Common*/
    uint8_t	type;					//<< always byte[0]
    uint32_t timeout_ms;			//<< always byte[1-4]
    /**/
    uint8_t dut_tc_id;				//<< DUT test case ID

    /*Show*/
    uint32_t max_avg_volt_mv;
    uint32_t min_avg_volt_mv;
    uint32_t ripple_volt_mv;

}TC_Dut_Volt1_Para;

/*----------------------------------*/
typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
}TC_Dut1_Result;

typedef struct
{
    /*Common*/
    uint8_t	type;
    uint32_t timeout_ms;			//<< always byte[1-4]
    /**/
    uint8_t dut_tc_id;				//<< DUT test case ID
}TC_Dut1_Para;

/*----------------------------------*/
typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
    uint8_t logic_1_is_pass;
    uint8_t logic_0_is_pass;
}TC_Jig_Io5_Result;

typedef struct
{
    /*Common*/
    uint8_t	type;					//<< always byte[0]
    uint32_t timeout_ms;			//<< always byte[1-4]
    /**/
    uint8_t dut_tc_id;				//<< DUT test case ID
    uint8_t io_input_y_channel;
}TC_Jig_Io5_Para;

/*----------------------------------*/
typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
    uint8_t logic_1_is_pass;
    uint8_t logic_0_is_pass;
}TC_Jig_Io7_Result;

typedef struct
{
    /*Common*/
    uint8_t	type;					//<< always byte[0]
    uint32_t timeout_ms;			//<< always byte[1-4]
    /**/
    uint8_t io_output_x_channel;
    uint8_t io_output_y_channel;
    uint8_t io_input_z_channel;
    uint8_t io_output_x_lv;
}TC_Jig_Io7_Para;

/*----------------------------------*/
typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
    uint32_t avg_volt_mv;
    uint32_t ripple_volt_mv;
}TC_Jig_Volt1_Result;

typedef struct
{
    /*Common*/
    uint8_t	type;					//<< always byte[0]
    uint32_t timeout_ms;			//<< always byte[1-4]
    /**/
    uint8_t adc_channel;
    uint32_t voltage_devision_ratio_1000;		//<< devide by 1000 before using
    uint8_t cycle_time_ms;
    uint16_t sample_number;

    /*Show*/
    uint32_t max_avg_volt_mv;
    uint32_t min_avg_volt_mv;
    uint32_t ripple_volt_mv;

}TC_Jig_Volt1_Para;

/*----------------------------------*/
typedef struct
{
    /*Common*/
    uint8_t result;					//<< always byte[0]
    /**/
    uint32_t avg_volt_mv;
    uint32_t ripple_volt_mv;
}TC_Jig_Volt2_Result;

typedef struct
{
    /*Common*/
    uint8_t	type;					//<< always byte[0]
    uint32_t timeout_ms;			//<< always byte[1-4]
    /**/
    uint8_t dut_tc_id;				//<< DUT test case ID
    uint8_t adc_channel;
    uint32_t voltage_devision_ratio_1000;		//<< devide by 1000 before using
    uint8_t cycle_time_ms;
    uint16_t sample_number;

    /*Show*/
    uint32_t max_avg_volt_mv;
    uint32_t min_avg_volt_mv;
    uint32_t ripple_volt_mv;

}TC_Jig_Volt2_Para;

/*----------------------------------*/



/*----------------------------------*/

#ifdef __cplusplus
}
#endif

#endif // TESTCASE_H
