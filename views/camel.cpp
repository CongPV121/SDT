#include "camel.h"
#include "ui_camel.h"
#include <QFileDialog>
#include "Controller/controler.h"
#include "Controller/testing/testing.h"
#include <QMessageBox>
#include <QtCore>
#include "Controller/downloadfw/downloadfw.h"
#include "views/downfw_config.h"
#include <QMessageBox>

camel::camel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::camel)
{
    connect(this, &camel::on_response_percents_to_complete,this, &camel::percents_to_complete);
    ui->setupUi(this);
    /* Update device list update firmware*/
    FwConfigListInit();
    ui->deviceList->addItem("Select Device");
    for (int i = 0; i < fwConfiglist.size(); i++ ){
        if(fwConfiglist[i].codeDevice != nullptr){
            ui->deviceList->addItem(fwConfiglist[i].codeDevice);
        }
    }
}

camel::~camel()
{
    delete ui;
}
/*--------------------Slots-----------------------*/
static int old_percents = 0;
static int war_success = 0;
void camel::percents_to_complete(const int& percent){
    int value = percent;
    if(percent >100 ){
        value = 100;
    }
    if(percent < 0){
        value = 0;
    }
    //this->ui->download_process_2->setValue(value);
    if( war_success == 0 &&  percent == 100){
        war_success = 1;
        QMessageBox::information(this,"Download Firmware mc","Success");
    }
    if( war_success == 1 &&  percent < 5){
        war_success = 0;
    }
    old_percents = percent;


}
//void camel::on_choose_file_btn_2_clicked()
//{
//    QString path = QFileDialog::getOpenFileName(
//                this,
//                "Open File",
//                "//",
//                "hex(*.hex);; All File(*.*)");
//    if( path.length() == 0) return;
//    set_link_director(path);
//    //this->ui->link_director_file_2->setText(get_link_director());
//    this->ui->write_firm_ware->setEnabled(0);
//}
QString camel::get_link_director() const{
    return this->link_director;
}
void camel::set_link_director(const QString& link_director){
    this->link_director  = link_director;
}
camel* camel::get_camel(){
    static camel* seft;
    if(seft == nullptr){
        seft = new camel();
    }
    return seft;
}
static char src_file[1024];
void camel::on_connect_dut_clicked()
{
//    QUrl folder_url = QUrl::fromLocalFile(get_link_director());
//    emit on_request_write_firmware(folder_url);
//    QString str_path = this->link_director;
//    if( str_path.length() == 0) return;
//    if(str_path.length() >= 1024){
//        QMessageBox::information(this,"ERROR","The path to the file is too long !");
//        return;
//    }
//    QByteArray ba;
//    ba = str_path.toLatin1();
//    const char* path = ba.data();
//    memcpy(src_file,path,str_path.length());

//    set_download_firmware_par(1,BP_MAINAPP_NODE_ID,src_file,0x8000,boot1_bp_reboot_method);

    this->ui->write_fw->setEnabled(1);
}
void set_value_processbar_camel(const int value, uint8_t state_process){
    camel* camel = camel::get_camel();
    if(camel == nullptr){
        return;
    }
    if(state_process == 11){
        emit camel->on_response_write_fw_button(0);
    }
    emit camel->on_response_percents_to_complete(value);
}


//void camel::on_write_firm_ware_clicked()
//{
//    active_download_firmware();
//}



//void camel::on_connect_dut_clicked()
//{

//}


void camel::on_deviceList_currentIndexChanged(int index)
{
    QString codeDevice      = ui->deviceList->currentText();
    for (int i = 0; i < fwConfiglist.size(); i++ ){
        if(fwConfiglist[i].codeDevice == codeDevice){
            ui->link_director_file->setText(fwConfiglist[i].linkFile);
        }
    }

}

void camel::on_write_fw_clicked()
{
    QString codeDevice      = ui->deviceList->currentText();
    if( ui->deviceList->currentIndex() < 1){
        return;
    }
    QString infor;
    infor = "Nạp Code " + codeDevice + "?";

    QFont font;
    font.setFamily("Arial"); // Đặt tên phông chữ
    font.setPointSize(12); // Đặt kích thước phông chữ
    font.setBold(true); // Đặt đậm cho phông chữ
    QMessageBox msgBox;
    msgBox.setFont(font);

    if(msgBox.question(this,"Tiếp tục",infor) == QMessageBox::Yes ){
        //    QUrl folder_url = QUrl::fromLocalFile(get_link_director());
        //    emit on_request_write_firmware(folder_url);
        //    QString str_path = this->link_director;
        //    if( str_path.length() == 0) return;
        //    if(str_path.length() >= 1024){
        //        QMessageBox::information(this,"ERROR","The path to the file is too long !");
        //        return;
        //    }
        //    QByteArray ba;
        //    ba = str_path.toLatin1();
        //    const char* path = ba.data();
        //    memcpy(src_file,path,str_path.length());

            set_download_firmware_par(1,BP_MAINAPP_NODE_ID,src_file,0x8000,boot1_bp_reboot_method);
    }

}

