#include "testing_config.h"
#include "ui_testing_config.h"
#include <QMessageBox>
#include "Controller/testing/testing.h"
#include "Controller/testing/testcase/testcase.h"
#include <QtGui/QIntValidator>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "Controller/config/config.h"

testsiute TS_showing;

QVector<QString> testCases = {
    "TC_DUT_IO1",
    "TC_DUT_IO2",
    "TC_DUT_IO3",
    "TC_JIG_IO1",
    "TC_JIG_IO2",
    "TC_JIG_IO3",
    "TC_JIG_IO4",
    "TC_JIG_IO5",
    "TC_JIG_IO6",
    "TC_JIG_IO7",
    "TC_JIG_VOLT1",
    "TC_JIG_VOLT2",
    "TC_JIG_VOLT3",
    "TC_DUT_VOLT1",
    "TC_CAN",
    "TC_DUT_1",
    "TC_BMS_OTP",
    "TC_BMS_CELL_VOLT",
    "TC_BMS_GATE_DRIVER",
    "TC_BMS_SHUTDOWN",
    "CM_IO1",
};

testing_config *testingUi = nullptr;

testing_config::testing_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::testing_config)
{
    ui->setupUi(this);
    this->setStyleSheet("QTableWidgetItem { font-family: 'Times New Roman'; font-size: 18px; font-weight: bold; border: 2px solid red;} ");
    this->ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: green}");
    this->upadateTestList();
}
void testing_config::upadateTestList(void){
    QString folderPath = TestSiuteFolder;
    QDir dir;
    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(TestSiuteFile);
    JigTestList.clear();
    JigTestList = loadJigTestList(srcConfigFile);
    ui->jigTestlist->clear();
    for(int i = 0; i < JigTestList.size();  i ++){
        if(JigTestList[i].name == nullptr) continue;
        QListWidgetItem *item = new QListWidgetItem(JigTestList[i].name);
        ui->jigTestlist->addItem(item);
    }
    ui->groupBoxConfig->setEnabled(0);
}

testing_config::~testing_config()
{
    delete ui;
}
testing_config* testing_config::get_testing_config(){
    testingUi = new testing_config();
    return testingUi;
}
Ui::testing_config *testing_config::getUi()
{
    return ui;
}
/* thay đổi thông số tương ứng với từng testcase*/
void config_dialog::onComboBoxIndexChanged(int index){
    QString text = static_cast<QComboBox*>(sender())->currentText();
    if(text ==  "TC_JIG_VOLT1"){
        this->set_dialog_TC_JIG_VOLT1();
    }
    else if(text ==  "TC_DUT_IO1"){
        this->set_dialog_TC_DUT_IO1();
    }
    else if(text ==  "TC_DUT_IO2"){
        this->set_dialog_TC_DUT_IO2();
    }
    else if( text == "TC_DUT_IO3"){
        this->set_dialog_TC_DUT_IO3();
    }
    else if(text == "TC_JIG_IO1"){
        this->set_dialog_TC_JIG_IO1();
    }
    else if(text ==  "TC_JIG_IO2"){
        this->set_dialog_TC_JIG_IO2();
    }
    else if(text ==  "TC_JIG_IO3"){
        this->set_dialog_TC_JIG_IO3();
    }
    else if( text == "TC_JIG_IO4"){
        this->set_dialog_TC_JIG_IO4();
    }
    else if(text ==  "TC_JIG_IO5"){
        this->set_dialog_TC_JIG_IO5();
    }
    else if(text == "TC_JIG_IO6"){
        this->set_dialog_TC_JIG_IO6();
    }
    else if(text ==  "TC_JIG_IO7"){
        this->set_dialog_TC_JIG_IO7();
    }
    else if(text == "TC_JIG_VOLT1"){
        this->set_dialog_TC_JIG_VOLT1();
    }
    else if(text ==  "TC_JIG_VOLT2"){
        this->set_dialog_TC_JIG_VOLT2();
    }
    else if(text ==  "TC_JIG_VOLT3"){
        this->set_dialog_TC_JIG_VOLT3();
    }
    else if(text ==  "TC_DUT_VOLT1"){
        this->set_dialog_TC_DUT_VOLT1();
    }
    else if(text ==  "TC_CAN"){
        this->set_dialog_TC_CAN();
    }
    else if(text ==  "TC_DUT_1"){
        this->set_dialog_TC_DUT_1();
    }
    else if(text ==  "TC_BMS_OTP"){
        this->set_dialog_TC_BMS_OTP();
    }
    else if(text ==  "TC_BMS_CELL_VOLT"){
        this->set_dialog_TC_BMS_CELL_VOLT();
    }
    else if(text ==   "TC_BMS_GATE_DRIVER"){
        this->set_dialog_TC_BMS_GATE_DRIVER();
    }
    else if( text == "TC_BMS_SHUTDOWN"){
        this->set_dialog_TC_BMS_SHUTDOWN();
    }
    else if(text ==  "CM_IO1"){
        this->set_dialog_CM_IO1();
    }

}
void creatTCShowing(testcase tc){
    TS_showing.TestCase += tc;
}
void updateTSShowing(testsiute ts){
    TS_showing = ts;
}

void testing_config::on_new_test_clicked()
{
    config_dialog dialog;
    dialog.exec();
}
config_dialog::config_dialog(QWidget *parent)
    : QDialog(parent)
{
    this->dialog_init();

}
void config_dialog::dialog_init(){
    QFont font("Times New Roman", 18, QFont::Bold);

    this->setWindowTitle("Test Case");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QLabel *label1 = new QLabel("Tên bài test:", this);
    QLineEdit *nameTC = new QLineEdit(this);
    nameTC->setObjectName("nameTC");
    nameTC->setText("Bài kiểm tra 1");

    QLabel *label2 = new QLabel("ID:", this);
    QLineEdit *lineEdit2 = new QLineEdit(this);

    QLabel *label3 = new QLabel("Loại bài test:", this);
    QComboBox *comboBox = new QComboBox(this);
    comboBox->setObjectName("comboBox");

    for(int i = 0; i < testCases.size(); i++){
        comboBox->addItem(testCases[i]);
    }

    QPushButton *buttonOk = new QPushButton("OK", this);
    buttonOk->setObjectName("buttonOk");

    QPushButton *buttonCancel = new QPushButton("Cancel", this);
    buttonCancel->setObjectName("buttonCancel");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(label1, 0, 0);
    layout->addWidget(nameTC, 0, 1);
    layout->addWidget(label2, 1, 0);
    layout->addWidget(lineEdit2, 1, 1);
    layout->addWidget(label3, 2, 0);
    layout->addWidget(comboBox, 2, 1);
    layout->addWidget(buttonOk, 3, 1, Qt::AlignRight);
    layout->addWidget(buttonCancel, 3, 0, Qt::AlignRight);


    this->setLayout(layout);

    this->setStyleSheet("QLabel { font-family: 'Times New Roman'; font-size: 18px; font-weight: bold; } "
                        "QLineEdit { font-family: 'Times New Roman'; font-size: 18px; font-weight: bold; } "
                        "QComboBox { font-family: 'Times New Roman'; font-size: 12px; font-weight: bold; } "
                        "QPushButton { font-family: 'Times New Roman'; font-size: 18px; font-weight: bold; } ");

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChanged(int)));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(onbuttonOK()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(onbuttonCancel()));
}
/*----------------Button OK-------------------------*/
void config_dialog::onbuttonOK(){


    QLineEdit *lineEdit = this->findChild<QLineEdit *>("nameTC");
    QString nametc = lineEdit->text();
    if(nametc == nullptr) {
        QMessageBox msgBox;
        msgBox.warning(this,"Lỗi","Hãy đặt tên bài test");
        return;
    }

    QString showTestCase = this->showTableWigdet();
    QComboBox *comboBox = this->findChild<QComboBox*>("comboBox");
    QString text;
    if (comboBox) {
        text = comboBox->currentText();
    }
    TC_Dut_Volt1_Para tc_jig_vol;

    if(text ==  "TC_JIG_VOLT1"){
        tc_jig_vol.dut_tc_id = this->findChild<QLineEdit *>("dut_tc_id_edit")->text().toUInt() ;
        tc_jig_vol.max_avg_volt_mv = this->findChild<QLineEdit *>("volMax_edit")->text().toUInt() ;
        tc_jig_vol.min_avg_volt_mv = this->findChild<QLineEdit *>("volMin_edit")->text().toUInt() ;
        tc_jig_vol.ripple_volt_mv = this->findChild<QLineEdit *>("volDelta_edit")->text().toUInt() ;
        tc_jig_vol.timeout_ms = this->findChild<QLineEdit *>("timeout_ms_edit")->text().toUInt() ;
        tc_jig_vol.type = this->findChild<QLineEdit *>("dut_tc_id_edit")->text().toUInt() ;
    }

    uint8_t data[sizeof (TC_Dut_Volt1_Para)];
    memcpy(data,(uint8_t*)&tc_jig_vol,sizeof (TC_Dut_Volt1_Para));
    QString dataStr = QString::fromUtf8(reinterpret_cast<const char*>(data), sizeof(data));

    testcase tc_buff;
    tc_buff.name = this->findChild<QLineEdit *>("nameTC")->text();
    tc_buff.testParamaters = dataStr;
    tc_buff.testShow = showTestCase;

    creatTCShowing(tc_buff);
    this->close();
}
QString config_dialog::showTableWigdet(){
    Ui::testing_config *uiConfig = testingUi->getUi();
    QTableWidget *p_tableWidget = uiConfig->tableWidget;

    QLineEdit *lineEdit = this->findChild<QLineEdit *>("nameTC");
    QString nametc = lineEdit->text();

    int row = p_tableWidget->rowCount();
    uiConfig->tableWidget->setRowCount(row + 1);

    QTableWidgetItem *item = new QTableWidgetItem(nametc);
    p_tableWidget->setItem(row, 0, item);

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    QString label1;
    for(int gridRow = 1; gridRow < gridLayout->rowCount(); gridRow++){

        QString textLabel = nullptr;
        QLabel* label = nullptr;
        QLayoutItem* itemlabel = gridLayout->itemAtPosition(gridRow, 0);
        if (itemlabel != nullptr) {
            label = dynamic_cast<QLabel*>(itemlabel->widget());
        }
        if (label != nullptr) {
            textLabel = label->text()+ " ";
        }

        QString textlineEdit = nullptr;
        QLineEdit* lineEdit = nullptr;
        QLayoutItem* item = gridLayout->itemAtPosition(gridRow, 1);
        if (item != nullptr) {
            lineEdit = dynamic_cast<QLineEdit*>(item->widget());
        }
        if (lineEdit != nullptr) {
            textlineEdit = lineEdit->text();
        }

        QString textCombo = nullptr;
        QComboBox* Combo = nullptr;
        QLayoutItem* itemCombo = gridLayout->itemAtPosition(gridRow, 1);
        if (itemCombo != nullptr) {
            Combo = dynamic_cast<QComboBox*>(item->widget());
        }
        if (Combo != nullptr) {
            textCombo = Combo->currentText() ;
        }

        label1 +=  textLabel;
        label1 +=  textlineEdit;
        label1 +=  textCombo;
        label1 += "\n";
    }
    item = new QTableWidgetItem(label1);
    p_tableWidget->setItem(row, 2, item);

    p_tableWidget->resizeRowsToContents();
    p_tableWidget->resizeColumnsToContents();
    return label1;
}

void config_dialog::onbuttonCancel(){
    this->close();
}
void config_dialog::dialog_clear(void){
    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row_cnt = gridLayout->rowCount();
    int col_cnt = gridLayout->columnCount();
    /* tìm và lấy con trỏ 2 button*/
    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");

    for (int row = 3; row < row_cnt - 1; ++row) {
        for (int col = 0; col < col_cnt ; ++col) {
            QLayoutItem *layoutItem = gridLayout->itemAtPosition(row, col);
            if(layoutItem == nullptr) continue;
            QWidget *widget = layoutItem->widget();
            if (widget != nullptr) {
                QPushButton *pushButton = qobject_cast<QPushButton*>(widget);
                /* giữ lại 2 button*/
                if(buttonOk == pushButton) continue;
                if(buttonCancel == pushButton) continue;
                widget->deleteLater();
            }
        }
    }

}

/*----------------Show config test case-------------------------*/
void config_dialog::set_dialog_TC_DUT_IO1(void){
    this->dialog_clear();
    //    QFont font("Times New Roman", 18, QFont::Bold);

    //    QLabel *label3 = new QLabel("Age:", this);
    //    label3->setFont(font);
    //    QLineEdit *lineEdit3 = new QLineEdit(this);
    //    lineEdit3->setPlaceholderText("Enter age");
    //    lineEdit3->setFont(font);

    //    QLayout *layout = this->layout();
    //    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    //    gridLayout->addWidget(label3, 4, 0);
    //    gridLayout->addWidget(lineEdit3, 4, 1);

    //    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    //    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    //    row++;
    //    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    //    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();
}

void config_dialog::set_dialog_TC_JIG_VOLT1(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);
    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);

    QLabel *adcChanel_label   = new QLabel("Cổng ADC:", this);
    QLabel *adcVolt_div_label = new QLabel("Tỷ số bộ chia điện áp:", this);
    QLabel *sampleTime_label  = new QLabel("Chu kỳ lấy mẫu (ms):", this);
    QLabel *sampleNum_label   = new QLabel("Số lần trích mẫu:", this);
    QLabel *volMax_label      = new QLabel("Giá trị điện áp trung bình lớn nhất (mV):", this);
    QLabel *volMin_label      = new QLabel("Giá trị điện áp trung bình nhỏ nhất (mV):", this);
    QLabel *volDelta_label    = new QLabel("Giá trị điện áp dao động lớn nhất "
                                           "\n giữa các lần lấy mẫu (mV):", this);
    QLabel *dut_tc_id_label             = new QLabel("Mã số bài test của DUT:", this);

    QLineEdit *timeout_ms_edit             = new QLineEdit(this);

    QLineEdit *adcChanel_edit     = new QLineEdit(this);
    QLineEdit *adcVolt_div_edit   = new QLineEdit( this);
    QLineEdit *sampleTime_edit    = new QLineEdit( this);
    QLineEdit *sampleNum_edit     = new QLineEdit( this);
    QLineEdit *volMax_edit        = new QLineEdit(this);
    QLineEdit *volMin_edit        = new QLineEdit( this);
    QLineEdit *volDelta_edit      = new QLineEdit( this);
    QLineEdit *dut_tc_id_edit              = new QLineEdit( this);

    //    timeout_ms_edit->setObjectName("timeout_ms_edit");
    //    adcChanel_edit->setObjectName("adcChanel_edit");
    //    adcVolt_div_edit->setObjectName("adcVolt_div_edit");
    //    sampleTime_edit->setObjectName("sampleTime_edit");
    sampleNum_edit->setValidator(new QIntValidator(0, 255, sampleNum_edit));
    volMax_edit->setValidator(new QIntValidator(0, 99999, volMax_edit));
    volMin_edit->setValidator(new QIntValidator(0, 99999, volMin_edit));
    volDelta_edit->setValidator(new QIntValidator(0, 99999, volDelta_edit));
    dut_tc_id_edit->setValidator(new QIntValidator(0, 255, dut_tc_id_edit));

    timeout_ms_edit->setObjectName("timeout_ms_edit");
    adcChanel_edit->setObjectName("adcChanel_edit");
    adcVolt_div_edit->setObjectName("adcVolt_div_edit");
    sampleTime_edit->setObjectName("sampleTime_edit");
    sampleNum_edit->setObjectName("sampleNum_edit");
    volMax_edit->setObjectName("volMax_edit");
    volMin_edit->setObjectName("volMin_edit");
    volDelta_edit->setObjectName("volDelta_edit");
    dut_tc_id_edit->setObjectName("dut_tc_id_edit");

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = 3;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(adcChanel_label,      row++, 0);
    gridLayout->addWidget(adcVolt_div_label,    row++, 0);
    gridLayout->addWidget(sampleTime_label,     row++, 0);
    gridLayout->addWidget(sampleNum_label,      row++, 0);
    gridLayout->addWidget(volMax_label,         row++, 0);
    gridLayout->addWidget(volMin_label,         row++, 0);
    gridLayout->addWidget(volDelta_label,       row++, 0);
    gridLayout->addWidget(dut_tc_id_label,      row++, 0);
    row = 3;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(adcChanel_edit,      row++, 1);
    gridLayout->addWidget(adcVolt_div_edit,    row++, 1);
    gridLayout->addWidget(sampleTime_edit,     row++, 1);
    gridLayout->addWidget(sampleNum_edit,      row++, 1);
    gridLayout->addWidget(volMax_edit,         row++, 1);
    gridLayout->addWidget(volMin_edit,         row++, 1);
    gridLayout->addWidget(volDelta_edit,       row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,      row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();

}

void config_dialog::set_dialog_TC_DUT_IO2(void){

}
void config_dialog::set_dialog_TC_DUT_IO3(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);

    QLabel *timeout_ms_label            = new QLabel("Timeout:", this);
    QLabel *io_output_x_channel_label   = new QLabel("IO Channel:", this);
    QLabel *dut_tc_id_label             = new QLabel("Mã số bài test của DUT:", this);

    QLineEdit *timeout_ms_edit             = new QLineEdit(this);
    QLineEdit *io_output_x_channel_edit    = new QLineEdit( this);
    QLineEdit *dut_tc_id_edit              = new QLineEdit( this);

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = 3;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(io_output_x_channel_label,    row++, 0);
    gridLayout->addWidget(dut_tc_id_label,    row++, 0);

    row = 3;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(io_output_x_channel_edit,    row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,    row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1,     Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);
    /*tự động điều chỉnh kích thước dialog*/
    this->adjustSize();

}
void config_dialog::set_dialog_TC_JIG_IO1(void){

}
void config_dialog::set_dialog_TC_JIG_IO2(void){

}
void config_dialog::set_dialog_TC_JIG_IO3(void){

}
void config_dialog::set_dialog_TC_JIG_IO4(void){

}
void config_dialog::set_dialog_TC_JIG_IO5(void){

}
void config_dialog::set_dialog_TC_JIG_IO6(void){

}
void config_dialog::set_dialog_TC_JIG_IO7(void){

}
void config_dialog::set_dialog_TC_JIG_VOLT2(void){

}
void config_dialog::set_dialog_TC_JIG_VOLT3(void){

}
void config_dialog::set_dialog_TC_DUT_VOLT1(void){
    this->dialog_clear();
    QFont font("Times New Roman", 18, QFont::Bold);

    QLabel *timeout_ms_label   = new QLabel("Timeout:", this);
    QLabel *dut_tc_id_label     = new QLabel("Mã số bài test của DUT:", this);
    QLabel *max_avg_volt_mv_label  = new QLabel("Giá trị điện áp trung bình lớn nhất (mV):", this);
    QLabel *min_avg_volt_mv_label   = new QLabel("Giá trị điện áp trung bình nhỏ nhất (mV):", this);
    QLabel *ripple_volt_mv_label      = new QLabel("Giá trị điện áp dao động (mV):", this);


    QLineEdit *timeout_ms_edit     = new QLineEdit(this);
    QLineEdit *dut_tc_id_edit   = new QLineEdit( this);
    QLineEdit *max_avg_volt_mv_edit    = new QLineEdit( this);
    QLineEdit *min_avg_volt_mv_edit     = new QLineEdit( this);
    QLineEdit *ripple_volt_mv_edit        = new QLineEdit(this);
    QLineEdit *volMin_edit        = new QLineEdit( this);
    QLineEdit *volDelta_edit      = new QLineEdit( this);

    QLayout *layout = this->layout();
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(layout);
    int row = 3;
    gridLayout->addWidget(timeout_ms_label,      row++, 0);
    gridLayout->addWidget(dut_tc_id_label,    row++, 0);
    gridLayout->addWidget(max_avg_volt_mv_label,     row++, 0);
    gridLayout->addWidget(min_avg_volt_mv_label,      row++, 0);
    gridLayout->addWidget(ripple_volt_mv_label,         row++, 0);
    //    gridLayout->addWidget(volMin_label,         row++, 0);
    //    gridLayout->addWidget(volDelta_label,       row++, 0);

    row = 3;
    gridLayout->addWidget(timeout_ms_edit,      row++, 1);
    gridLayout->addWidget(dut_tc_id_edit,    row++, 1);
    gridLayout->addWidget(max_avg_volt_mv_edit,     row++, 1);
    gridLayout->addWidget(min_avg_volt_mv_edit,      row++, 1);
    gridLayout->addWidget(ripple_volt_mv_edit,         row++, 1);
    gridLayout->addWidget(volMin_edit,         row++, 1);
    gridLayout->addWidget(volDelta_edit,       row++, 1);

    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    QPushButton *buttonCancel = this->findChild<QPushButton *>("buttonCancel");
    row++;
    gridLayout->addWidget(buttonOk,row , 1, Qt::AlignRight);
    gridLayout->addWidget(buttonCancel, row, 0, Qt::AlignRight);

}
void config_dialog::set_dialog_TC_CAN(void){

}
void config_dialog::set_dialog_TC_DUT_1(void){

}
void config_dialog::set_dialog_TC_BMS_OTP(void){

}
void config_dialog::set_dialog_TC_BMS_CELL_VOLT(void){

}
void config_dialog::set_dialog_TC_BMS_GATE_DRIVER(void){

}
void config_dialog::set_dialog_TC_BMS_SHUTDOWN(void){

}
void config_dialog::set_dialog_CM_IO1(void){

}

void testing_config::on_saveTestSuite_clicked()
{
    QString folderPath = TestSiuteFolder;
    QDir dir;
    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(TestSiuteFile);
    JigTestList += TS_showing;
    for (int i = 0; i < JigTestList.size() -1; ++i) {
        if(TS_showing.name == JigTestList[i].name){
            JigTestList[i] = TS_showing;
            JigTestList.removeLast();
            break;
        }
    }
    saveJigTestList(JigTestList,srcConfigFile);
    this->upadateTestList();
}


void testing_config::on_pushButton_2_clicked()
{
    QString folderPath = TestSiuteFolder;
    QDir dir;
    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(TestSiuteFile);

    QVector<testsiute> JigTestList = loadJigTestList(srcConfigFile);

}

void saveJigTestList(const QVector<testsiute>& jigTestList, const QString& fileName)
{
    // Tạo một đối tượng JSON từ đối tượng JigTestList
    QJsonObject json;
    QJsonArray testSuiteArray;
    for (const auto& testSuite : jigTestList)
    {
        QJsonObject testSuiteJson;
        testSuiteJson["name"] = testSuite.name;

        QJsonArray testCaseArray;
        for (const auto& testCase : testSuite.TestCase)
        {
            QJsonObject testCaseJson;
            testCaseJson["name"]            = testCase.name;
            testCaseJson["testParameters"]  = testCase.testParamaters;
            testCaseJson["testShow"]        = testCase.testShow;
            testCaseArray.append(testCaseJson);
        }

        testSuiteJson["testCases"] = testCaseArray;
        testSuiteArray.append(testSuiteJson);
    }
    json["testSuites"] = testSuiteArray;

    // Lưu đối tượng JSON vào tệp tin
    QJsonDocument doc(json);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        // xoá file ghi lại từ đầu
        file.resize(0);
        file.write(doc.toJson());
        file.close();
    }
}
QVector<testsiute> loadJigTestList(const QString& fileName)
{
    QVector<testsiute> jigTestList;

    // Đọc dữ liệu từ tệp tin
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return jigTestList;

    QByteArray data = file.readAll();
    file.close();

    // Phân tích dữ liệu JSON và tạo các đối tượng tương ứng
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();
    QJsonArray testSuiteArray = json["testSuites"].toArray();

    for (const auto& testSuiteJson : testSuiteArray)
    {
        testsiute testSuite;
        QJsonObject testSuiteObj = testSuiteJson.toObject();
        testSuite.name = testSuiteObj["name"].toString();

        QJsonArray testCaseArray = testSuiteObj["testCases"].toArray();
        for (const auto& testCaseJson : testCaseArray)
        {
            testcase testCase;
            QJsonObject testCaseObj = testCaseJson.toObject();
            testCase.name           = testCaseObj["name"].toString();
            testCase.testParamaters = testCaseObj["testParameters"].toString();
            testCase.testShow       = testCaseObj["testShow"].toString();
            testSuite.TestCase.append(testCase);
        }
        jigTestList.append(testSuite);
    }

    return jigTestList;
}

void testing_config::on_jigTestlist_itemDoubleClicked(QListWidgetItem *item)
{
    int row = ui->jigTestlist->currentRow();
    QListWidgetItem *clickedItem = ui->jigTestlist->item(row);
    QString text = clickedItem->text();
    for(int i = 0; i < JigTestList.size();  i ++){
        if(text == JigTestList[i].name){

            ui->groupBoxConfig->setEnabled(1);
            updateTSShowing(JigTestList[i]);
            this->clearTableListTest();
            ui->nameTs->setText(text);
            ui->tableWidget->setRowCount(JigTestList[i].TestCase.size());

            for (int row = 0; row < JigTestList[i].TestCase.size(); row++) {
                QTableWidgetItem *item = new QTableWidgetItem(JigTestList[i].TestCase[row].name);
                ui->tableWidget->setItem(row, 0, item);
                item = new QTableWidgetItem(JigTestList[i].TestCase[row].testShow);
                ui->tableWidget->setItem(row, 2, item);
            }

            ui->tableWidget->resizeRowsToContents();
            ui->tableWidget->resizeColumnsToContents();
            return;
        }
    }
}
void testing_config::clearTableListTest(void)
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


void testing_config::on_pushButton_clicked()
{
    QDialog *dialog = new QDialog();
    QLabel *label = new QLabel("Tên bộ kiểm thử");
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setText("Bộ kiểm thử 1");
    QPushButton *okButton = new QPushButton("OK");
    QPushButton *cancelButton = new QPushButton("Cancel");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(label);
    mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(buttonLayout);

    dialog->setLayout(mainLayout);
    dialog->setStyleSheet("QLabel { font-family: 'Times New Roman'; font-size: 12px; font-weight: bold; } "
                          "QLineEdit { font-family: 'Times New Roman'; font-size: 12px; font-weight: bold; } "
                          "QComboBox { font-family: 'Times New Roman'; font-size: 12px; font-weight: bold; } "
                          "QPushButton { font-family: 'Times New Roman'; font-size: 12px; font-weight: bold; } ");

    // Kết nối sự kiện button
    QObject::connect(okButton, &QPushButton::clicked, [=](){
        QString text = lineEdit->text();
        if(text == nullptr) {
            QMessageBox::information(this, "Cảnh báo", "Nhập tên bộ kiểm thử");
        }
        for(int i = 0; i < JigTestList.size();  i ++){
            if(text == JigTestList[i].name){
                QMessageBox::information(this, "Cảnh báo", "Bộ kiểm thử đã tồn tại");
                return;
            }
        }
        testsiute new_TS;
        new_TS.name = text;
        updateTSShowing(new_TS);
        Ui::testing_config *uiConfig = testingUi->getUi();
        QListWidget *p_tableWidget = uiConfig->jigTestlist;
        QListWidgetItem *item = new QListWidgetItem(text);
        p_tableWidget->addItem(item);
        uiConfig->nameTs->setText(text);

        ui->groupBoxConfig->setEnabled(1);

        dialog->close();
    });

    QObject::connect(cancelButton, &QPushButton::clicked, [=](){
        dialog->close();
    });

    dialog->exec();
}

