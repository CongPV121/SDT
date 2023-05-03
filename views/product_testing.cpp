#include "product_testing.h"
#include "ui_product_testing.h"

product_testing::product_testing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::product_testing)
{
    ui->setupUi(this);
    ui->exportData->setStyleSheet("QGroupBox { border: 1px solid red; }");
    ui->start_testing->setStyleSheet("QGroupBox { border: 2px solid blue; }");
    ui->stop_testing->setStyleSheet("QGroupBox { border: 2px solid red; }");
    ui->test_proccess->setStyleSheet("QGroupBox { border: 2px solid green; }");
    ui->test_proccess->setStyleSheet("QGroupBox { background-color: green; }");
    ui->groupBox_2->setStyleSheet("QGroupBox { border: 1px solid black; }");
    ui->groupBox_3->setStyleSheet("QGroupBox { border: 1px solid black; }");
    ui->groupBox_4->setStyleSheet("QGroupBox { border: 1px solid black; }");

    QFont font("Times New Roman", 12);
    ui->tableWidget->setFont(font);

//    QTableWidgetItem *checkbox_item = new QTableWidgetItem();
//    checkbox_item->setFlags(checkbox_item->flags() | Qt::ItemIsUserCheckable);
//    checkbox_item->setCheckState(Qt::Checked);
//    for(int i = 0; i< ui->tableWidget->rowCount(); i++){
//        QTableWidgetItem *checkbox_item = new QTableWidgetItem();
//        checkbox_item->setFlags(checkbox_item->flags() | Qt::ItemIsUserCheckable);
//        checkbox_item->setCheckState(Qt::Checked);
//        ui->tableWidget->setItem(i, 0, checkbox_item);
//    }
}

product_testing::~product_testing()
{
    delete ui;
}
product_testing* product_testing::get_product_testing(){
    static product_testing* seft;
    if(seft == nullptr){
        seft = new product_testing();
    }
    return seft;
}
