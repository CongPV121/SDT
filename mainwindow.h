#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "views/pmu.h"
#include "views/hmi.h"
#include "views/bp.h"
#include "views/mc.h"
#include "views/camel.h"
#include "views/downfw_config.h"
#include "views/logui.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow* get_MainWindow();

public slots:
    void on_write_CP202_st      (int value);

private slots:    
    void on_testBpButton_clicked();

    void on_testPmuButton_clicked();

    void on_testHmiButton_clicked();


    void on_testMcButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_fw_update_config_triggered();

    void on_actionLog_triggered();

    void on_actionCh_nh_s_a_danh_s_ch_test_triggered();

    void on_testvehicleButton_clicked();

private:
    Ui::MainWindow *ui;
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void on_response_CP202_st                 (int value);

};

void CP202_set_state(int value);
#endif // MAINWINDOW_H
