#ifndef TESTING_H
#define TESTING_H

#include <QObject>
#include <QVector>
#include <QString>
#include "Controller/app_co/od/od.h"
#include "Controller/testing/hmi_testing/hmi_testing.h"
#include "Controller/testing/testcase/testcase.h"

class testing : public QObject
{
    Q_OBJECT
public:

    explicit testing(QObject *parent = nullptr);
};


/*----------------------device information---------------------------------*/
typedef struct {
    uint16_t CRC;
    char deivce_name[10];
    char serial[16];
    char ev_id[32];
    char PCBA_id[16];
    char date_manufacture[16];
    char hw_ver[3];
    char sw_ver[3];
}device_infor;

/*-----------------------test case - test siute--------------------------------*/
class testcase
{
public:
    testcase() {};
    QString name;
    QString typeTC;
    QString testParamaters;
    QString testShow;
};
class testsiute
{
public:
    testsiute() {};
    QString name;
    QString device;
    QVector<testcase> TestCase;
};
/*-------------------------------------------------------*/

void pdo_testing_process_handle(uint32_t canid, uint8_t *data);
void read_testing_result(void);
void update_table_testing_result(void);
void pdo_testing_processing(void);

#endif // TESTING_H
