#include "product_testing.h"
#include "ui_product_testing.h"
#include "Controller/config/config.h"
#include "Controller/testing/testing.h"
#include "Controller/testing/testcase/testcase.h"
#include "views/testing_config.h"
#include <QFile>

static QVector<testsiute> TSiuteList;
product_testing::product_testing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::product_testing)
{
    ui->setupUi(this);
    ui->exportData->setStyleSheet("QGroupBox { border: 1px solid red; }");
    ui->start_testing->setStyleSheet("QGroupBox { border: 2px solid blue; }");
    ui->stop_testing->setStyleSheet("QGroupBox { border: 2px solid red; }");
    ui->test_proccess->setStyleSheet("QGroupBox { border: 2px solid green; }");
    ui->test_proccess->setStyleSheet("QGroupBox { background-color: #c1ffc1; }");
    ui->groupBox_2->setStyleSheet("QGroupBox { border: 1px solid black; }");
    ui->groupBox_3->setStyleSheet("QGroupBox { border: 1px solid black; }");
    ui->groupBox_4->setStyleSheet("QGroupBox { border: 1px solid black; }");

    QFont font("Times New Roman", 12);
    ui->tableWidget->setFont(font);

    QString folderPath = TestSiuteFolder;
    QDir dir;
    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(TestSiuteFile);
    TSiuteList.clear();
    TSiuteList = loadJigTestList(srcConfigFile);

    for (int i = 0; i < TSiuteList.size(); i++ ){
        if(TSiuteList[i].name != nullptr){
            ui->testsiuteList->addItem(TSiuteList[i].name);
        }
    }
}

product_testing::~product_testing()
{
    delete ui;
}
product_testing* product_testing::get_product_testing(){
    product_testing* seft = new product_testing();
    return seft;
}

void product_testing::on_SingleStart_clicked()
{

}

