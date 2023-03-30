#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "views/dialog.h"
#include "Controller/thread/thread.h"

get_event can_receive;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    can_receive.start();
}

MainWindow::~MainWindow()
{
    can_receive.quit();
    delete ui;
}

void MainWindow::on_testBpButton_clicked()
{
    bp* p_bp =bp::get_bp();
    p_bp->setModal(true);
    p_bp->exec();

}

void MainWindow::on_testPmuButton_clicked()
{
    pmu* p_pmu = new pmu();
    p_pmu->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    p_pmu->showFullScreen();
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

