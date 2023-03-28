#include "bp.h"
#include "ui_bp.h"
#include <QFileDialog>
#include "Controller/controler.h"
#include "Controller/testing/testing.h"
#include <QMessageBox>
#include "Controller/boot_master_app/boot_master_config.h"

bp::bp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bp)
{
    connect(this, &bp::on_response_bp_percents_to_complete,this, &bp::percents_bp_to_complete);
    connect(this, &bp::on_response_write_fw_button,this, &bp::on_write_write_fw_button);

    ui->setupUi(this);
}

bp::~bp()
{
    delete ui;
}
/*--------------------Slots-----------------------*/
static int old_percents = 0;
static int war_success = 0;
void bp::percents_bp_to_complete(const int& percent){
    int value = percent;
    if(percent >100 ){
        value = 100;
    }
    if(percent < 0){
        value = 0;
    }
    this->ui->download_process->setValue(value);
    if( war_success == 0 &&  percent == 100){
        war_success = 1;
        QMessageBox::information(this,"Download Firmware HMI","Success");
    }
    if( war_success == 1 &&  percent == 2){
        war_success = 0;
    }
    old_percents = percent;
} //percent download code


void bp::on_write_write_fw_button(int value){
    this->ui->write_firm_ware->setEnabled(value);
}

void bp::on_choose_file_btn_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                "Open File",
                "//",
                "hex(*.hex);; All File(*.*)");
    if( path.length() == 0) return;
    set_link_director(path);
    this->ui->link_director_file->setText(get_link_director());
}
QString bp::get_link_director() const{
    return this->link_director;
}
void bp::set_link_director(const QString& link_director){
    this->link_director  = link_director;
}
bp* bp::get_bp(){
    static bp* seft;
    if(seft == nullptr){
        seft = new bp();
    }
    return seft;
}
static char src_file[1024];

void bp::on_write_firm_ware_clicked()
{

     active_download_firmware();
}

void set_value_processbar_bp(const int value, uint8_t state_process){
    bp* p_bp = bp::get_bp();
    if(p_bp == nullptr){
        return;
    }
    if(state_process == 11){
        emit p_bp->on_response_write_fw_button(0);
    }
    emit p_bp->on_response_bp_percents_to_complete(0);
}

void bp::on_connect_dut_clicked()
{

    QUrl folder_url = QUrl::fromLocalFile(get_link_director());
    emit on_request_write_firmware(folder_url);
    QString str_path = this->link_director;
    if( str_path.length() == 0) return;
    if(str_path.length() >= 1024){
        QMessageBox::information(this,"ERROR","The path to the file is too long !");
        return;
    }
    QByteArray ba;
    ba = str_path.toLatin1();
    const char* path = ba.data();
    memcpy(src_file,path,str_path.length());
    set_download_firmware_par(1,HMI_MAINAPP_NODE_ID,src_file,0x10000);
    this->ui->write_firm_ware->setEnabled(1);
}


void bp::on_write_fw_clicked()
{

}

