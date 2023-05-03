#ifndef TESTING_CONFIG_H
#define TESTING_CONFIG_H

#include <QDialog>
#include <QFileDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "QDialogButtonBox"
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include "Controller/testing/testing.h"

namespace Ui {
class testing_config;
}

class testing_config : public QDialog
{
    Q_OBJECT

public:
    static   testing_config* get_testing_config();
    explicit testing_config(QWidget *parent = nullptr);
    ~testing_config();
    Ui::testing_config *getUi();
private slots:
    void on_new_test_clicked();

private:
    Ui::testing_config *ui;
};



class config_dialog : public QDialog
{
    Q_OBJECT

public:
    config_dialog(QWidget *parent = nullptr) ;
    void set_dialog_TC_DUT_IO1(void);
    void set_dialog_TC_DUT_IO2(void);
    void set_dialog_TC_DUT_IO3(void);
    void set_dialog_TC_JIG_IO1(void);
    void set_dialog_TC_JIG_IO2(void);
    void set_dialog_TC_JIG_IO3(void);
    void set_dialog_TC_JIG_IO4(void);
    void set_dialog_TC_JIG_IO5(void);
    void set_dialog_TC_JIG_IO6(void);
    void set_dialog_TC_JIG_IO7(void);
    void set_dialog_TC_JIG_VOLT1(void);
    void set_dialog_TC_JIG_VOLT2(void);
    void set_dialog_TC_JIG_VOLT3(void);
    void set_dialog_TC_DUT_VOLT1(void);
    void set_dialog_TC_CAN(void);
    void set_dialog_TC_DUT_1(void);
    void set_dialog_TC_BMS_OTP(void);
    void set_dialog_TC_BMS_CELL_VOLT(void);
    void set_dialog_TC_BMS_GATE_DRIVER(void);
    void set_dialog_TC_BMS_SHUTDOWN(void);
    void set_dialog_CM_IO1(void);

private slots:
    void onComboBoxIndexChanged(int index);
    void onbuttonOK(void);
     void onbuttonCancel(void);
};

extern testing_config *testingUi;
#endif // TESTING_CONFIG_H
