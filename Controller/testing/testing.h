#ifndef TESTING_H
#define TESTING_H

#include <QObject>
#include <QVector>
#include <QString>
#include "Controller/app_co/od/od.h"
#include "Controller/testing/hmi_testing/hmi_testing.h"

class testing : public QObject
{
    Q_OBJECT
public:

    explicit testing(QObject *parent = nullptr);
};

typedef struct sdo_msg_buff_t sdo_msg_buff;
typedef struct sdo_send_mailbox_t sdo_send_mailbox;

struct sdo_msg_buff_t{

    void        (*method)(void);
    void        (*response_fucntion)(void);
    uint32_t    time_delay_10ms;// time delay before start


};

struct sdo_send_mailbox_t{
    sdo_msg_buff    sdo_send_msg[32];
    uint16_t        msg_waiting = 0;

};
/*-------------------------------------------------------*/
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

struct TC_DUT_IO1_t {
    const QString testName = "TC_DUT_IO1";
};

struct TC_DUT_IO2_t {
    const QString testName = "TC_DUT_IO2";

};
struct TC_DUT_IO3_t {
    const QString testName = "TC_JIG_IO1";

};
struct TC_JIG_IO1_t {
    const QString testName = "TC_JIG_IO2";

};
struct TC_JIG_IO2_t {
    const QString testName = "TC_JIG_IO2";

};
struct TC_JIG_IO3_t {
    const QString testName = "TC_JIG_IO3";

};
struct TC_JIG_IO4_t {
    const QString testName = "TC_JIG_IO4";

};
struct TC_JIG_IO5_t {
    const QString testName = "TC_JIG_IO5";

};
struct TC_JIG_IO6_t {
    const QString testName = "TC_JIG_IO6";

};
struct TC_JIG_IO7_t {
    const QString testName = "TC_JIG_IO7";

};
struct TC_JIG_VOLT1_t {
    const QString testName = "TC_JIG_VOLT1";

};
struct TC_JIG_VOLT2_t {
    const QString testName = "TC_JIG_VOLT2";

};
struct TC_JIG_VOLT3_t {
    const QString testName = "TC_JIG_VOLT3";

};
struct TC_DUT_VOLT1_t {
    const QString testName = "TC_DUT_VOLT1";

};
struct TC_CAN_t {
    const QString testName = "TC_CAN";

};
struct TC_DUT_1_t {
    const QString testName = "TC_DUT_1";

};
struct TC_BMS_OTP_t {
    const QString testName = "TC_BMS_OTP";

};
struct TC_BMS_CELL_VOLT_t {
    const QString testName = "TC_BMS_CELL_VOLT";

};
struct TC_BMS_GATE_DRIVER_t {
    const QString testName = "TC_BMS_GATE_DRIVER";

};
struct TC_BMS_SHUTDOWN_t {
    const QString testName = "TC_BMS_SHUTDOWN";

};
struct CM_IO1_t {
    const QString testName = "CM_IO1";

};


/*-------------------------------------------------------*/
extern QVector<QString> testCases ;

extern sdo_send_mailbox SDO_mailbox ;

void testing_sdo_process            (sdo_send_mailbox *mailbox);
bool push_data_into_queue_to_send(void (*method)(void ),void (*response)(void),
                                  uint32_t time_delay);

#endif // TESTING_H
