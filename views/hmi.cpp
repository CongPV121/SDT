#include "hmi.h"
#include "ui_hmi.h"
#include <QFileDialog>
#include "Controller/controler.h"
#include "Controller/testing/testing.h"
#include <QMessageBox>
#include <QtCore>

hmi::hmi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hmi)
{
    connect(this, &hmi::on_response_read_data_config,this, &hmi::data_read_config);
    connect(this, &hmi::on_response_percents_to_complete,this, &hmi::percents_to_complete);
    connect(this, &hmi::on_response_read_serial_number,this, &hmi::on_write_serial_number);
    connect(this, &hmi::on_response_read_fw_version,this, &hmi::on_write_fw_version);
    connect(this, &hmi::on_response_read_hw_version,this, &hmi::on_write_hw_version);
    connect(this, &hmi::on_response_read_esim_number,this, &hmi::on_write_esim_number);
    connect(this, &hmi::on_response_write_fw_button,this, &hmi::on_write_write_fw_button);

    ui->setupUi(this);
}

hmi::~hmi()
{
    delete ui;
}

/*--------------------Slots-----------------------*/
static int old_percents = 0;
static int war_success = 0;
void hmi::percents_to_complete(const int& percent){
    int value = percent;
    if(percent >100 ){
        value = 100;
    }
    if(percent < 0){
        value = 0;
    }
    this->ui->download_process->setValue(20);
    if( war_success == 0 &&  percent == 100){
        war_success = 1;
        QMessageBox::information(this,"Download Firmware HMI","Success");
    }
    if( war_success == 1 &&  percent == 2){
        war_success = 0;
    }
    old_percents = percent;


}
void hmi::data_read_config(const QString &data){
    QString esim, serial_module,serial_vehicle, firm_ware_ver, hard_ware_ver;
    /*process data*/


    /*add to value*/
    this->ui->esim_num->setText(esim);
    this->ui->serial_module->setText(serial_module);
    this->ui->serial_vehicle->setText(serial_vehicle);
    this->ui->firm_ware_ver->setText(firm_ware_ver);
    this->ui->hard_ware_ver->setText(hard_ware_ver);
}
void hmi::on_write_serial_number(QString value){
    this->ui->serial_vehicle->setText(value);
}
void hmi::on_write_fw_version(QString value){
    this->ui->firm_ware_ver->setText(value);
}
void hmi::on_write_hw_version(QString value){
    this->ui->hard_ware_ver->setText(value);
}
void hmi::on_write_esim_number(QString value){
    this->ui->esim_num->setText(value);
}
void hmi::on_write_write_fw_button(int value){
    this->ui->write_firm_ware->setEnabled(value);
}

/*--------------------Signals-----------------------*/
char arr[] = "101BE1";

void hmi::on_read_btn_clicked()
{
    read_hmi_infor_config();
}

void hmi::on_write_btn_clicked()
{
    QString input_serial_vehicle_value = this->ui->input_serial_vehicle->text();
    QString input_serial_module_value = this->ui->input_serual_module->text();
    QString snVehicle_Upper = input_serial_vehicle_value.toUpper();
    write_hmi_sn(snVehicle_Upper);
    //this->ui->esim_num->setText(snVehicle_Upper);
    /*prepare data*/
    //emit on_request_write_data_config(data_out);
}
static char src_file[1024];
void hmi::on_write_firm_ware_clicked()
{
    active_download_firmware();

}
void hmi::on_choose_file_btn_clicked()
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
QString hmi::get_link_director() const{
    return this->link_director;
}
void hmi::set_link_director(const QString& link_director){
    this->link_director  = link_director;
}
hmi* hmi::get_hmi(){
    static hmi* seft;
    if(seft == nullptr){
        seft = new hmi();
    }
    return seft;
}

void hmi::on_write_process_valueChanged(int value)
{

}
void set_value_processbar(const int value, uint8_t state_process){
    hmi* p_hmi = hmi::get_hmi();
    if(p_hmi == nullptr){
        qDebug()<<"err: hmi null";
        return;
    }
    if(state_process == 11){
        emit p_hmi->on_response_write_fw_button(0);
    }
    emit p_hmi->on_response_percents_to_complete(value);
}
void setText_serial_number(const char* value){

    QString s_value = QString(value);
    hmi::get_hmi()->on_write_serial_number(s_value);
}
void setText_esim_number(const char* value){

    QString s_value = QString(value);
    hmi::get_hmi()->on_write_esim_number(s_value);
}
void setText_hw_version(const char* value){

    QString s_value;
    for(uint8_t i = 0; i < 3; i++){
        s_value += QString::number(value[2-i]);
        s_value += ".";
    }
    hmi::get_hmi()->on_write_hw_version(s_value);

}
void setText_fw_version(const uint8_t* value){
    QString s_value;
    for(uint8_t i = 0; i < 3; i++){
        s_value += QString::number(value[2-i]);
        s_value += ".";
    }
    hmi::get_hmi()->on_write_fw_version(s_value);
}

void hmi::on_connect_dut_clicked()
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


void hmi::on_read_btn_2_clicked()
{

}


