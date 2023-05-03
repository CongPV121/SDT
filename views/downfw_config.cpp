#include "downfw_config.h"
#include "ui_downfw_config.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Controller/config/config.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include "Controller/downloadfw/downloadfw.h"
#include "qdebug.h"
downfw_config::downfw_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downfw_config)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(1);
    QStringList headerLabels;
    headerLabels << "Tên Thiết Bị" << "Mã thiết bị" << "Phiên bản" << "File mã nguồn";
    ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
    QStringList headerRows;

    // Thiết lập nhãn tiêu đề cho các hàng của bảng
    ui->tableWidget->setVerticalHeaderLabels(headerRows);

    QString folderPath = FwConfigFolder;
    QDir dir;
    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(FwConfigFile);

    getFwConfigList(srcConfigFile);
    this->showFwConfigList();
}

downfw_config::~downfw_config()
{
    delete ui;
}
downfw_config* downfw_config::get_downfw_config(){
    static downfw_config* seft;
    if(seft == nullptr){
        seft = new downfw_config();
    }
    return seft;
}

void downfw_config::on_pushButton_clicked()
{

    QString nameDevice      = this->ui->nameDevice->text();
    QString codeDevice      = this->ui->codeDevice->currentText();
    int     codeDeviceIndex = this->ui->codeDevice->currentIndex();
    QString version         = this->ui->version->text();
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    if( nameDevice.length() < 3) {
        msgBox.warning(this,"Lỗi","Tên thiết bị quá ngắn");
        return;
    }
    if( codeDeviceIndex == 0) {
        msgBox.warning(this,"Lỗi","Thiết bị chưa được chọn");
        return;
    }
    if( this->linkFile.length() < 3) {
        msgBox.warning(this,"Lỗi","File firmware chưa được chọn");
        return;
    }
    if( version.length() < 3) {
        msgBox.warning(this,"Lỗi","Version chưa được điền");
        return;
    }
    /* create folder*/
    QString folderPath = FwConfigFolder;

    QDir dir;

    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(FwConfigFile);
    /*copy file link*/
    QFileInfo fileInfo(this->linkFile);
    QString fileName = fileInfo.fileName();
    QDir dir1(folderPath);
    QString filePath = dir1.filePath(fileName);

    copyFile(this->linkFile,filePath);
    this->updateListFwDevice(srcConfigFile, nameDevice, codeDevice, filePath, version);
    this->saveConfigPara(srcConfigFile);
    this->showFwConfigList();

}


void downfw_config::on_codeDevice_activated(int index)
{
}

void downfw_config::on_linkFile_clicked()
{
    this->linkFile = nullptr;
    this->ui->linkFileFw->setText(this->linkFile);
    QString path = QFileDialog::getOpenFileName(
                this,
                "Open File",
                "//",
                "hex(*.hex)");
    if( path.length() == 0) return;
    this->linkFile = path;
    this->ui->linkFileFw->setText(this->linkFile);
}

int copyFile(QString sourceFilePath, QString destFilePath ){

    if(sourceFilePath == nullptr){
        return 0;
    }
    if(destFilePath == nullptr){
        return 0;
    }
    QFile sourceFile(sourceFilePath);
    if (!sourceFile.exists()) {
        return 0;
    }
    QFile destFile(destFilePath);
    if (!sourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return 0;
    }

    if (!destFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return 0;
    }

    QByteArray data = sourceFile.readAll();

    destFile.write(data);

    sourceFile.close();

    destFile.close();
    return 1;
}
void downfw_config::showFwConfigList(){

    QTableWidget *p_tableWidget = this->ui->tableWidget;
    int tableRow = fwConfiglist.size();
    ui->tableWidget->setRowCount(tableRow);
    QStringList headerRows;
    // Thiết lập nhãn tiêu đề cho các hàng của bảng
    ui->tableWidget->setVerticalHeaderLabels(headerRows);
    /*Show in tableWidget*/
    for (int row = 0; row < tableRow; row++) {

        QTableWidgetItem *item = new QTableWidgetItem(fwConfiglist[row].nameDevice);
        p_tableWidget->setItem(row, 0, item);
        p_tableWidget->setColumnWidth(1, 150);
        item = new QTableWidgetItem(fwConfiglist[row].codeDevice);
        p_tableWidget->setItem(row, 1, item);

        item = new QTableWidgetItem(fwConfiglist[row].version);
        p_tableWidget->setItem(row, 2, item);

        QFileInfo fileInfo(fwConfiglist[row].linkFile);
        QString fileName = fileInfo.fileName();
        item = new QTableWidgetItem(fileName);

        p_tableWidget->setColumnWidth(3, 300);
        p_tableWidget->setItem(row, 3, item);

    }
}
int downfw_config::saveConfigPara(QString destFilePath){

    QFile file(destFilePath);
    if (file.open(QIODevice::WriteOnly| QIODevice::Text))
    {
        QTextStream stream(&file);
        // xoá file ghi lại từ đầu
        file.resize(0);
        for (int row = 0; row < fwConfiglist.size(); row++) {
            // Ghi các thông số cấu hình vào file
            stream << "configNumber:-----------" << '\n';
            stream << "nameDevice:" << fwConfiglist[row].nameDevice   << '\n';
            stream << "codeDevice:" << fwConfiglist[row].codeDevice   << '\n';
            stream << "linkFile:"   << fwConfiglist[row].linkFile     << '\n';
            stream << "version:"    << fwConfiglist[row].version      << '\n';
        }

        file.close();
    }
    else
    {
        qDebug() << "Failed to save config file.";
        return 0;
    }
    return 1;
}
void downfw_config::updateListFwDevice(QString destFilePath, QString nameDevice,
                                       QString codeDevice, QString linkFile , QString version ){
    (void) destFilePath;
    for (int row = 0; row < fwConfiglist.size(); row++) {
        if(fwConfiglist[row].codeDevice == codeDevice){
            fwConfiglist[row].nameDevice = nameDevice;
            fwConfiglist[row].linkFile = linkFile;
            fwConfiglist[row].version = version;
            return;
        }
    }
    fwConfig buff ;
    buff.codeDevice = codeDevice;
    buff.nameDevice = nameDevice;
    buff.linkFile = linkFile;
    buff.version = version;
    fwConfiglist += buff;
}
void downfw_config::removeConfig(QString codeDevice){

    for (int row = 0; row < fwConfiglist.size(); row++) {
        if(fwConfiglist[row].codeDevice == codeDevice){
            fwConfiglist.erase(fwConfiglist.begin()+row);
            return;
        }
    }
}

void FwConfigListInit(){
    QString folderPath = FwConfigFolder;
    QDir dir;
    dir.mkdir(folderPath);
    QString srcConfigFile = dir.filePath(FwConfigFile);

    getFwConfigList(srcConfigFile);
}

void getFwConfigList(QString srcPath){
    QFile file(srcPath);
    if(!file.exists()){
        return;
    }
    int numConfig = 0;
    fwConfiglist.clear();
    QVector<fwConfig> fwConfiglist_buff(1);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        // Đọc dữ liệu từ file và tìm giá trị của Param1
        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            if (line.contains("nameDevice"))
            {
                fwConfiglist += fwConfiglist_buff;
                QStringList parts = line.split(":");
                if (parts.count() == 2)
                {
                    QString param1Value = parts[1].trimmed();
                    fwConfiglist[numConfig].nameDevice = param1Value;

                }
            }
            if (line.contains("codeDevice"))
            {
                QStringList parts = line.split(":");
                if (parts.count() == 2)
                {
                    QString param1Value = parts[1].trimmed();
                    fwConfiglist[numConfig].codeDevice = param1Value;

                }
            }
            if (line.contains("linkFile"))
            {
                QStringList parts = line.split(":");
                if (parts.count() == 2)
                {
                    QString param1Value = parts[1].trimmed();
                    fwConfiglist[numConfig].linkFile = param1Value;
                    numConfig++;
                }
            }
        }

        file.close();
    }
}

//void downfw_config::on_tableWidget_itemClicked(QTableWidgetItem *item)
//{

//}

void downfw_config::on_pushButton_2_clicked()
{
    QList<QTableWidgetItem*> selectedItems = ui->tableWidget->selectedItems();
    if (selectedItems.isEmpty()) return;
    // Duyệt qua danh sách các hàng được chọn
    foreach (QTableWidgetItem* item, selectedItems) {
        int row = item->row();
        QString codeDevice = ui->tableWidget->item(row, 1)->text();
        ui->tableWidget->removeRow(row);
        this->removeConfig(codeDevice);
        QDir dir;
        QString srcConfigFile = dir.filePath(FwConfigFile);
        this->saveConfigPara(srcConfigFile);

    }
}

