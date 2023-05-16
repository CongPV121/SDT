#include "product_testing.h"
#include "ui_product_testing.h"
#include "Controller/config/config.h"
#include "Controller/testing/testing.h"
#include "Controller/testing/testcase/testcase.h"
#include "views/testing_config.h"
#include <QFile>

static QVector<testsiute> TSiuteList;
static testsiute TestSiuteCur;
product_testing *product_testingUi = nullptr;

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
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: green}");

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
    product_testingUi = new product_testing();
    return product_testingUi;
}

void product_testing::on_SingleStart_clicked()
{

}


void product_testing::on_download_device_clicked()
{
    QString TsName = ui->testsiuteList->currentText();
    for (int i = 0; i < TSiuteList.size(); i++ ){
        if(TSiuteList[i].name == TsName){
            TestSiuteCur = TSiuteList[i];
            this->cleartableWidget();
            this->updateTableTestSuite(TSiuteList[i]);

            this->ui->testSuite->setText(TSiuteList[i].name);
            this->ui->deviceName->setText(TSiuteList[i].device);
            return;

        }
    }
}
void product_testing::cleartableWidget(void)
{
    int numRows = ui->tableWidget->rowCount();
    int numCols = ui->tableWidget->columnCount();

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            QTableWidgetItem *item = ui->tableWidget->takeItem(row, col);
            delete item;
        }
    }
}
void product_testing::updateTableTestSuite(testsiute ts)
{
    ui->tableWidget->setRowCount(ts.TestCase.size());

    for (int row = 0; row < ts.TestCase.size(); row++) {
        QTableWidgetItem *item = new QTableWidgetItem(ts.TestCase[row].name);
        ui->tableWidget->setItem(row, 1, item);
        item = new QTableWidgetItem(ts.TestCase[row].testShow);
        ui->tableWidget->setItem(row, 2, item);
        item = new QTableWidgetItem("Chưa Kiểm Tra");
        item->setBackground(QBrush(QColor(255, 255, 153)));
        ui->tableWidget->setItem(row, 3, item);

    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}

void product_testing::on_AllStart_clicked()
{
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        QTableWidgetItem *item;
        item = new QTableWidgetItem("Chưa Kiểm Tra");
        item->setBackground(QBrush(QColor(255, 255, 153)));
        ui->tableWidget->setItem(row, 3, item);

    }
    uint8_t ret[1024] ;
    ret[0] = 1;
    product_testingUi->update_testing_result_tableWidget(2,TC_JIG_VOLT1_ID,ret);
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();

}

void product_testing::update_testing_result_tableWidget(int row,int typeTC, uint8_t*  result ){

    int typeResult = result[0];

    QString resultShow = this->get_result_tc(typeTC,result);
    QTableWidgetItem *item = new QTableWidgetItem(resultShow);
    if( typeResult == 0){
        item->setBackground(Qt::red);
    }
    else{
        item->setBackground(Qt::green);
    }
    ui->tableWidget->setItem(row, 3, item);

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}
void update_testing_result(int testCaseNum, uint8_t *result){

    if(testCaseNum >= TestSiuteCur.TestCase.size()){
        return;
    }
    QByteArray byteArray = TestSiuteCur.TestCase[testCaseNum].testParamaters.toUtf8();
    const uint8_t* par = reinterpret_cast<const uint8_t*>(byteArray.constData());

    product_testingUi->update_testing_result_tableWidget(testCaseNum,par[0],result);
}
/*------------------------------------------------------------------*/
/*------------------------Show testing result------------------*/
/*------------------------------------------------------------------*/
QString product_testing::get_result_tc(int type, uint8_t* data){

    QString ret;
    if(type ==  TC_JIG_VOLT1_ID){

        ret = this->get_result_TC_JIG_VOLT1(data);
    }
    else if(type ==  TC_DUT_IO1_ID){

        ret =  this->get_result_TC_DUT_IO1(data);
    }
    else if(type ==  TC_DUT_IO2_ID){
        ret = this->get_result_TC_DUT_IO2(data);
    }
    else if( type == TC_DUT_IO3_ID){
        ret =  this->get_result_TC_DUT_IO3(data);
    }
    else if(type == TC_JIG_IO1_ID){
        ret = this->get_result_TC_JIG_IO1(data);
    }
    else if(type ==  TC_JIG_IO2_ID){
        ret = this->get_result_TC_JIG_IO2(data);
    }
    else if(type ==  TC_JIG_IO3_ID){
        ret =  this->get_result_TC_JIG_IO3(data);
    }
    else if( type == TC_JIG_IO4_ID){
        ret = this->get_result_TC_JIG_IO4(data);
    }
    else if(type ==  TC_JIG_IO5_ID){
        ret = this->get_result_TC_JIG_IO5(data);
    }
    else if(type == TC_JIG_IO6_ID){
        ret =  this->get_result_TC_JIG_IO6(data);
    }
    else if(type ==  TC_JIG_IO7_ID){
        ret = this->get_result_TC_JIG_IO7(data);
    }
    else if(type == TC_JIG_VOLT1_ID){
        ret = this->get_result_TC_JIG_VOLT1(data);
    }
    else if(type ==  TC_JIG_VOLT2_ID){
        ret = this->get_result_TC_JIG_VOLT2(data);
    }
    else if(type ==  TC_JIG_VOLT3_ID){
        ret = this->get_result_TC_JIG_VOLT3(data);
    }
    else if(type ==  TC_DUT_VOLT1_ID){
        ret = this->get_result_TC_DUT_VOLT1(data);
    }
    else if(type ==  TC_CAN_ID){
        ret = this->get_result_TC_CAN(data);
    }
    else if(type ==  TC_DUT_1_ID){
        ret = this->get_result_TC_DUT_1(data);
    }
    else if(type ==  TC_BMS_OTP_ID){
        ret =  this->get_result_TC_BMS_OTP(data);
    }
    else if(type ==  TC_BMS_CELL_VOLT_ID){
        ret = this->get_result_TC_BMS_CELL_VOLT(data);
    }
    else if(type ==   TC_BMS_GATE_DRIVER_ID){
        ret = this->get_result_TC_BMS_GATE_DRIVER(data);
    }
    else if( type == TC_BMS_SHUTDOWN_ID){
        ret = this->get_result_TC_BMS_SHUTDOWN(data);
    }
    else if(type ==  CM_IO1_ID){
        ret = this->get_result_CM_IO1(data);
    }
    return ret;
}
/*------------------------------------------------------------------*/
/*------------------------get testing result------------------*/
/*------------------------------------------------------------------*/
QString product_testing::get_result_TC_DUT_IO1(const uint8_t * result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_DUT_IO2(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_DUT_IO3(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_JIG_IO1(const uint8_t *result){
    QString ret;

    TC_Dut_Io1_Result tc_jig;
    /* get testcase struct*/
    int size = sizeof (tc_jig);
    memcpy((uint8_t*)&tc_jig,result,size);

    ret += "actual_level: " + QString::number(tc_jig.actual_level) + "\n";
    return ret;
};
QString product_testing::get_result_TC_JIG_IO2(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_JIG_IO3(const uint8_t *result){
    QString ret;

    TC_Dut_Io3_Result tc_jig;
    /* get testcase struct*/
    int size = sizeof (tc_jig);
    memcpy((uint8_t*)&tc_jig,result,size);

    ret += "logic_1_is_pass: " + QString::number(tc_jig.logic_1_is_pass) + "\n";
    ret += "logic_0_is_pass: " + QString::number(tc_jig.logic_0_is_pass) + "\n";
    return ret;
};
QString product_testing::get_result_TC_JIG_IO4(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_JIG_IO5(const uint8_t *result){
    QString ret;

    TC_Jig_Io5_Result tc_jig;
    /* get testcase struct*/
    int size = sizeof (tc_jig);
    memcpy((uint8_t*)&tc_jig,result,size);

    ret += "logic_1_is_pass: " + QString::number(tc_jig.logic_1_is_pass) + "\n";
    ret += "logic_0_is_pass: " + QString::number(tc_jig.logic_0_is_pass) + "\n";
    return ret;
};
QString product_testing::get_result_TC_JIG_IO6(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_JIG_IO7(const uint8_t *result){
    QString ret;

    TC_Jig_Io7_Result tc_jig;
    /* get testcase struct*/
    int size = sizeof (tc_jig);
    memcpy((uint8_t*)&tc_jig,result,size);

    ret += "logic_1_is_pass: " + QString::number(tc_jig.logic_1_is_pass) + "\n";
    ret += "logic_0_is_pass: " + QString::number(tc_jig.logic_0_is_pass) + "\n";
    return ret;
};
QString product_testing::get_result_TC_JIG_VOLT1(const uint8_t *result){
    QString ret;

    TC_Jig_Volt1_Result tc_jig;
    /* get testcase struct*/
    int size = sizeof (tc_jig);
    memcpy((uint8_t*)&tc_jig,result,size);

    ret += "avg_volt_mv: " + QString::number(tc_jig.avg_volt_mv) + "\n";
    ret += "ripple_volt_mv: " + QString::number(tc_jig.ripple_volt_mv) + "\n";
    return ret;
};
QString product_testing::get_result_TC_JIG_VOLT2(const uint8_t *result){
    QString ret;

    TC_Jig_Volt2_Result tc_jig;
    /* get testcase struct*/
    int size = sizeof (tc_jig);
    memcpy((uint8_t*)&tc_jig,result,size);

    ret += "avg_volt_mv: " + QString::number(tc_jig.avg_volt_mv) + "\n";
    ret += "ripple_volt_mv: " + QString::number(tc_jig.ripple_volt_mv) + "\n";
    return ret;
};
QString product_testing::get_result_TC_JIG_VOLT3(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_DUT_VOLT1(const uint8_t *result){
    QString ret;

    TC_Dut_Volt1_Result tc_jig;
    /* get testcase struct*/
    int size = sizeof (tc_jig);
    memcpy((uint8_t*)&tc_jig,result,size);

    ret += "avg_volt_mv: " + QString::number(tc_jig.avg_volt_mv) + "\n";
    ret += "ripple_volt_mv: " + QString::number(tc_jig.ripple_volt_mv) + "\n";
    return ret;
};
QString product_testing::get_result_TC_CAN(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_DUT_1(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_BMS_OTP(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_BMS_CELL_VOLT(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_BMS_GATE_DRIVER(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_TC_BMS_SHUTDOWN(const uint8_t *result){
    QString ret;
    return ret;
};
QString product_testing::get_result_CM_IO1(const uint8_t *result){
    QString ret;
    return ret;
};
