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
    void set_diaolg_TC_DUT_IO1(void);
    void set_diaolg_TC_JIG_VOLT1(void);

private slots:
    void onComboBoxIndexChanged(int index);
    void onbuttonOK(void);
     void onbuttonCancel(void);
};

extern testing_config *testingUi;
#endif // TESTING_CONFIG_H
