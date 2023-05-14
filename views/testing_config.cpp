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
    "Chọn bài kiểm thử",
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

static QVector<testsiute> JigTestList;
testing_config *testingUi = nullptr;
/*Contructor */
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
    this->set_dialog_tc(text);

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
    dialog.set_dialog_tc(testCases[0]);
    dialog.exec();
}
config_dialog::config_dialog(QWidget *parent)
    : QDialog(parent)
{
    this->dialog_init();

}
/*Tạo 1 dialog để nhập thông số bài testcase*/
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
    //comboBox->setCurrentIndex(2);

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
    this->row_continue = 3;
    this->setLayout(layout);

    this->setStyleSheet("QLabel { font-family: 'Times New Roman'; font-size: 18px; font-weight: bold; } "
                        "QLineEdit { font-family: 'Times New Roman'; font-size: 18px; font-weight: bold; } "
                        "QComboBox { font-family: 'Times New Roman'; font-size: 12px; font-weight: bold; } "
                        "QPushButton { font-family: 'Times New Roman'; font-size: 18px; font-weight: bold; } ");

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChanged(int)));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(onbuttonOK_newTC()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(onbuttonCancel()));
}
/*Xử lý sự kiện button ok khi nhập liệu thông số testcase*/
void config_dialog::onbuttonOK_newTC(){

    QLineEdit *lineEdit = this->findChild<QLineEdit *>("nameTC");
    QString nametc = lineEdit->text();
    if(nametc == nullptr) {
        QMessageBox msgBox;
        msgBox.warning(this,"Lỗi","Hãy đặt tên bài test");
        return;
    }
    QComboBox *comboBox = this->findChild<QComboBox*>("comboBox");
    if(comboBox->currentIndex() == 0) {
        QMessageBox msgBox;
        msgBox.warning(this,"Lỗi","Hãy chọn bài kiểm thử");
        return;
    }
    /*thêm tiếp testcase mới vào bảng*/
    Ui::testing_config *uiConfig = testingUi->getUi();
    QTableWidget *p_tableWidget = uiConfig->tableWidget;
    int row = p_tableWidget->rowCount();
    QString showTestCase = this->addRowTableWigdet(row);

    QString text;
    if (comboBox) {
        text = comboBox->currentText();
    }

    QString dataStr = this->get_par_tc(text);
    testcase tc_buff;
    tc_buff.name = this->findChild<QLineEdit *>("nameTC")->text();
    tc_buff.typeTC = comboBox->currentText();
    tc_buff.testParamaters = dataStr;
    tc_buff.testShow = showTestCase;

    creatTCShowing(tc_buff);
    this->close();
}
/*Xử lý sự kiện button OK khi chỉnh sửa thông số testcase*/
void config_dialog::onbuttonOK_editTC(){

    QLineEdit *lineEdit = this->findChild<QLineEdit *>("nameTC");
    QString nametc = lineEdit->text();
    if(nametc == nullptr) {
        QMessageBox msgBox;
        msgBox.warning(this,"Lỗi","Hãy đặt tên bài test");
        return;
    }
    QComboBox *comboBox = this->findChild<QComboBox*>("comboBox");
    if(comboBox->currentIndex() == 0) {
        QMessageBox msgBox;
        msgBox.warning(this,"Lỗi","Hãy chọn bài kiểm thử");
        return;
    }
    /*thay đổi testcase mới vào bảng*/
    Ui::testing_config *uiConfig = testingUi->getUi();
    QTableWidget *p_tableWidget = uiConfig->tableWidget;
    int row = p_tableWidget->currentRow();
    QString showTestCase = this->addRowTableWigdet(row);

    QString text;
    if (comboBox) {
        text = comboBox->currentText();
    }

    QString dataStr = this->get_par_tc(text);
    testcase tc_buff;
    tc_buff.name = this->findChild<QLineEdit *>("nameTC")->text();
    tc_buff.typeTC = comboBox->currentText();
    tc_buff.testParamaters = dataStr;
    tc_buff.testShow = showTestCase;
    TS_showing.TestCase[row] = tc_buff;
    this->close();
}
/*Hiển thị test case trên TableWigdet*/

QString config_dialog::addRowTableWigdet(int row){
    Ui::testing_config *uiConfig = testingUi->getUi();
    QTableWidget *p_tableWidget = uiConfig->tableWidget;

    QLineEdit *lineEdit = this->findChild<QLineEdit *>("nameTC");
    QString nametc = lineEdit->text();

    int rowcnt = p_tableWidget->rowCount();
    if(row >= rowcnt){
        uiConfig->tableWidget->setRowCount(rowcnt + 1);
    }

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
void config_dialog::change_connect_button(){
    QPushButton *buttonOk = this->findChild<QPushButton *>("buttonOk");
    disconnect(buttonOk, SIGNAL(clicked()), this, SLOT(onbuttonOK_newTC()));
    connect(buttonOk, SIGNAL(clicked()), this, SLOT(onbuttonOK_editTC()));
}
/*xoá hiển thị tất cả các testcase trên TableWigdet*/
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

/*lưu testsuite*/
void testing_config::on_saveTestSuite_clicked()
{
    
    int deviceIndex = ui->deviceTest->currentIndex();
    if(deviceIndex <= 0){
        QMessageBox::information(this, "Cảnh báo", "Chọn thiết bị kiểm thử");
        return;
    }
    QString folderPath = TestSiuteFolder;
    QDir dir;
    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(TestSiuteFile);
    TS_showing.device = ui->deviceTest->currentText();
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
    ui->saveTestSuite->setEnabled(0);
    ui->groupBoxConfig->setEnabled(0);
}
/*load testsuite*/

void testing_config::on_pushButton_2_clicked()
{
    QString folderPath = TestSiuteFolder;
    QDir dir;
    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(TestSiuteFile);

    QVector<testsiute> JigTestList = loadJigTestList(srcConfigFile);

}
/*lưu JigTestList vào file dang Json */
void saveJigTestList(const QVector<testsiute>& jigTestList, const QString& fileName)
{
    // Tạo một đối tượng JSON từ đối tượng JigTestList
    QJsonObject json;
    QJsonArray testSuiteArray;
    for (const auto& testSuite : jigTestList)
    {
        QJsonObject testSuiteJson;
        testSuiteJson["name"] = testSuite.name;
        testSuiteJson["device"] = testSuite.device;
        QJsonArray testCaseArray;
        for (const auto& testCase : testSuite.TestCase)
        {
            QJsonObject testCaseJson;
            testCaseJson["name"]            = testCase.name;
            testCaseJson["typeTC"]            = testCase.typeTC;
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
        testSuite.device = testSuiteObj["device"].toString();
        QJsonArray testCaseArray = testSuiteObj["testCases"].toArray();
        for (const auto& testCaseJson : testCaseArray)
        {
            testcase testCase;
            QJsonObject testCaseObj = testCaseJson.toObject();
            testCase.name           = testCaseObj["name"].toString();
            testCase.typeTC         = testCaseObj["typeTC"].toString();
            testCase.testParamaters = testCaseObj["testParameters"].toString();
            testCase.testShow       = testCaseObj["testShow"].toString();
            testSuite.TestCase.append(testCase);
        }
        jigTestList.append(testSuite);
    }

    return jigTestList;
}
/*hiển thị các testcase hủa testsiute khi doubleClicked vào một dòng của ListWigdet*/
void testing_config::on_jigTestlist_itemDoubleClicked(QListWidgetItem *item)
{
    int row = ui->jigTestlist->currentRow();
    QListWidgetItem *clickedItem = ui->jigTestlist->item(row);
    QString text = clickedItem->text();
    for(int ts = 0; ts < JigTestList.size();  ts ++){
        if(text == JigTestList[ts].name){
            updateTSShowing(JigTestList[ts]);
            this->clearTableListTest();
            ui->nameTs->setText(text);
            this->update_table_testCase(TS_showing);
            /*thiết bị đang được chọn*/
            for(int index = 0; index < ui->deviceTest->count(); index++){
                if(JigTestList[ts].device == ui->deviceTest->itemText(index)){
                    ui->deviceTest->setCurrentIndex(index);
                }
            }
            /**/
            ui->saveTestSuite->setEnabled(0);
            ui->groupBoxConfig->setEnabled(0);
            return;
        }
    }
}
/*Xoá các phần tử của tableWidget*/
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
/*Tạo mới một testsiute*/
void testing_config::on_newTestSiute_clicked()
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
        this->clearTableListTest();
        dialog->close();
    });

    QObject::connect(cancelButton, &QPushButton::clicked, [=](){
        dialog->close();
    });

    dialog->exec();
}

void testing_config::on_editTS_clicked()
{
    ui->saveTestSuite->setEnabled(1);
    ui->groupBoxConfig->setEnabled(1);
}
void testing_config::on_tableWidget_cellDoubleClicked(int row, int column)
{
    config_dialog dialog;
    dialog.change_connect_button();

    int comboxIndex = dialog.findChild<QComboBox *>("comboBox")
            ->findText(TS_showing.TestCase[row].typeTC);
    dialog.findChild<QComboBox *>("comboBox")->setCurrentIndex(comboxIndex);
    dialog.set_par_tc(TS_showing.TestCase[row]);
    dialog.exec();

    //    QString text = static_cast<QComboBox*>(sender())->currentText();
    //    this->set_dialog_tc(text);

    //    QString str = TS_showing.TestCase[row].testParamaters;
    //    QByteArray ba = str.toUtf8();
    //    const uint8_t *data = reinterpret_cast<const uint8_t *>(ba.constData());
    //    int length = ba.size();
}

/*Xóa testCase*/
void testing_config::on_pushButton_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    TS_showing.TestCase.remove(currentRow);
    this->update_table_testCase(TS_showing);
}
void testing_config::update_table_testCase(testsiute ts){
    ui->tableWidget->setRowCount(ts.TestCase.size());

    for (int row = 0; row < ts.TestCase.size(); row++) {
        QTableWidgetItem *item = new QTableWidgetItem(ts.TestCase[row].name);
        ui->tableWidget->setItem(row, 0, item);
        item = new QTableWidgetItem(ts.TestCase[row].testShow);
        ui->tableWidget->setItem(row, 2, item);
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
}


void testing_config::on_tableWidget_cellActivated(int row, int column)
{

}

