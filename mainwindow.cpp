#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_testBpButton_clicked()
{

}

void MainWindow::on_testPmuButton_clicked()
{
    pmu* p_pmu=new pmu();
    p_pmu->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    p_pmu->showFullScreen();
}

void MainWindow::on_testHmiButton_clicked()
{
    hmi* p_hmi =hmi::get_hmi();
    p_hmi->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    p_hmi->showFullScreen();
}
