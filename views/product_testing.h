#ifndef PRODUCT_TESTING_H
#define PRODUCT_TESTING_H

#include <QDialog>
#include "Controller/testing/testing.h"

namespace Ui {
class product_testing;
}

class product_testing : public QDialog
{
    Q_OBJECT

public:
    explicit product_testing(QWidget *parent = nullptr);
    ~product_testing();
    static product_testing* get_product_testing();
    void cleartableWidget(void);
    void updateTableTestSuite(testsiute ts);

    QString get_result_TC_DUT_IO1(const uint8_t *);
    QString get_result_TC_DUT_IO2(const uint8_t *);
    QString get_result_TC_DUT_IO3(const uint8_t *);
    QString get_result_TC_JIG_IO1(const uint8_t *);
    QString get_result_TC_JIG_IO2(const uint8_t *);
    QString get_result_TC_JIG_IO3(const uint8_t *);
    QString get_result_TC_JIG_IO4(const uint8_t *);
    QString get_result_TC_JIG_IO5(const uint8_t *);
    QString get_result_TC_JIG_IO6(const uint8_t *);
    QString get_result_TC_JIG_IO7(const uint8_t *);
    QString get_result_TC_JIG_VOLT1(const uint8_t *);
    QString get_result_TC_JIG_VOLT2(const uint8_t *);
    QString get_result_TC_JIG_VOLT3(const uint8_t *);
    QString get_result_TC_DUT_VOLT1(const uint8_t *);
    QString get_result_TC_CAN(const uint8_t *);
    QString get_result_TC_DUT_1(const uint8_t *);
    QString get_result_TC_BMS_OTP(const uint8_t *);
    QString get_result_TC_BMS_CELL_VOLT(const uint8_t *);
    QString get_result_TC_BMS_GATE_DRIVER(const uint8_t *);
    QString get_result_TC_BMS_SHUTDOWN(const uint8_t *);
    QString get_result_CM_IO1(const uint8_t *);

    QString get_result_tc(int type, uint8_t * result);


    void update_testing_result_tableWidget(int row,int typeTC, uint8_t *);

private slots:
    void on_SingleStart_clicked();


    void on_download_device_clicked();

    void on_AllStart_clicked();

signals:
    void on_request_update_testing_result   (int row,int typeTC, QString result );
private:
    Ui::product_testing *ui;
};
void update_testing_result(int testCaseNum, uint8_t *result);
#endif // PRODUCT_TESTING_H
