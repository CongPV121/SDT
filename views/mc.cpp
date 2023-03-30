#include "mc.h"
#include "ui_mc.h"
#include <QFileDialog>
#include "Controller/controler.h"
#include "Controller/testing/testing.h"
#include <QMessageBox>
#include <QtCore>

mc::mc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mc)
{
    connect(this, &mc::on_response_percents_to_complete,this, &mc::percents_to_complete);

    ui->setupUi(this);
}

mc::~mc()
{
    delete ui;
}
/*--------------------Slots-----------------------*/
static int old_percents = 0;
static int war_success = 0;
void mc::percents_to_complete(const int& percent){
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
        QMessageBox::information(this,"Download Firmware mc","Success");
    }
    if( war_success == 1 &&  percent < 5){
        war_success = 0;
    }
    old_percents = percent;


}
void mc::data_read_config(const QString &data){
    QString esim, serial_module,serial_vehicle, firm_ware_ver, hard_ware_ver;
    /*process data*/


    /*add to value*/
    this->ui->esim_num->setText(esim);
    this->ui->serial_module->setText(serial_module);
    this->ui->serial_vehicle->setText(serial_vehicle);
    this->ui->firm_ware_ver->setText(firm_ware_ver);
    this->ui->hard_ware_ver->setText(hard_ware_ver);
}
void mc::on_write_serial_number(QString value){
}
void mc::on_write_fw_version(QString value){
}
void mc::on_write_hw_version(QString value){
}
void mc::on_write_esim_number(QString value){
}
void mc::on_write_write_fw_button(int value){
}

/*--------------------Signals-----------------------*/

void mc::on_read_btn_clicked()
{
    //read_mc_infor_config();
}

void mc::on_write_btn_clicked()
{
    QString input_serial_vehicle_value = this->ui->input_serial_vehicle->text();
    QString input_serial_module_value = this->ui->input_serual_module->text();
    QString snVehicle_Upper = input_serial_vehicle_value.toUpper();
    // write_hmi_sn(snVehicle_Upper);
    //this->ui->esim_num->setText(snVehicle_Upper);
    /*prepare data*/
    //emit on_request_write_data_config(data_out);
}
static char src_file[1024];
void mc::on_write_firm_ware_clicked()
{
    active_download_firmware();

}
void mc::on_choose_file_btn_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                "Open File",
                "//",
                "hex(*.hex);; All File(*.*)");
    if( path.length() == 0) return;
    set_link_director(path);
    this->ui->link_director_file->setText(get_link_director());
    this->ui->write_firm_ware->setEnabled(0);
}
QString mc::get_link_director() const{
    return this->link_director;
}
void mc::set_link_director(const QString& link_director){
    this->link_director  = link_director;
}
mc* mc::get_mc(){
    static mc* seft;
    if(seft == nullptr){
        seft = new mc();
    }
    return seft;
}

void mc::on_write_process_valueChanged(int value)
{

}
void mc::on_connect_dut_clicked()
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

    set_download_firmware_par(1,MC_MAINAPP_NODE_ID,src_file,0x08007800);

    this->ui->write_firm_ware->setEnabled(1);
}


void mc::on_read_btn_2_clicked()
{

}

void set_value_processbar_mc(const int value, uint8_t state_process){
    mc* p_mc = mc::get_mc();
    if(p_mc == nullptr){
        return;
    }
    if(state_process == 11){
        emit p_mc->on_response_write_fw_button(0);
    }
    emit p_mc->on_response_percents_to_complete(value);
}

