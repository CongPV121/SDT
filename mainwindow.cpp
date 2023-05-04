#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "views/dialog.h"
#include "Controller/thread/thread.h"
#include "Controller/app_co/init/app_co_init.h"
#include "views/testing_config.h"
#include "views/product_testing.h"

get_event can_receive;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(this, &MainWindow::on_response_CP202_st,this, &MainWindow::on_write_CP202_st);
    ui->setupUi(this);
    can_receive.start();

}

MainWindow::~MainWindow()
{
    can_receive.quit();
    delete ui;

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        // Kiểm tra nếu widget là UI được tạo bởi Qt Designer
        if (widget->objectName().startsWith("ui_")) {
            // Đóng UI
            delete widget;
        }
    }
}

void MainWindow::on_testBpButton_clicked()
{
    bp* p_bp = bp::get_bp();
    p_bp->setModal(true);
    p_bp->show();


}

void MainWindow::on_testPmuButton_clicked()
{
    pmu* p_pmu = new pmu();
    p_pmu->show();
    p_pmu->showMaximized();

}

void MainWindow::on_testHmiButton_clicked()
{
    hmi* p_hmi =hmi::get_hmi();
    p_hmi->setModal(true);
    p_hmi->exec();
    //    p_hmi->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //    p_hmi->showNormal();
}



void MainWindow::on_testMcButton_clicked()
{
    mc* p_mc = mc::get_mc();
    p_mc->setModal(true);
    p_mc->exec();
}
MainWindow* MainWindow::get_MainWindow(){
    static MainWindow* seft;
    if(seft == nullptr){
        seft = new MainWindow();
    }
    return seft;
}
void MainWindow::on_write_CP202_st(int value){
        if( value == 1){
            this->ui->CP202->setText("CP202-2CI: ĐÃ KẾT NỐI");
        }
        else{
            this->ui->CP202->setText("CP202-2CI: MẤT KẾT NỐI");
        }
}
void CP202_set_state(int value){
    MainWindow* p_main = MainWindow::get_MainWindow();
    if(p_main == nullptr){
        return;
    }
    emit p_main->on_response_CP202_st(value);
}

void MainWindow::on_pushButton_clicked()
{
    int value = cp202_device_connect();
    if( value == 1){
        this->ui->CP202->setText("ĐÃ KẾT NỐI");
    }
    else{
        this->ui->CP202->setText("MẤT KẾT NỐI");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    camel* p_camel = camel::get_camel();
    //p_camel->setModal(true);
    p_camel->show();
}



void MainWindow::on_fw_update_config_triggered()
{
    downfw_config* p_downfw_config = downfw_config::get_downfw_config();
    //p_camel->setModal(true);
    p_downfw_config->exec();
}


void MainWindow::on_actionLog_triggered()
{
    logui* p_logui = logui::get_logui();
    p_logui->show();
}

void MainWindow::closeEvent(QCloseEvent *event){
    can_receive.quit();
    delete ui;

}

void MainWindow::on_actionCh_nh_s_a_danh_s_ch_test_triggered()
{
    testing_config *p_testing_config = testing_config::get_testing_config();
    p_testing_config->exec();
}


void MainWindow::on_testvehicleButton_clicked()
{
    product_testing *p_product_testing = product_testing::get_product_testing();
    p_product_testing->exec();
}

