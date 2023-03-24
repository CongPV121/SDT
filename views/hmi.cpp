#include "hmi.h"
#include "ui_hmi.h"
#include <QFileDialog>
#include "Controller/controler.h"

int process_value = 10;
hmi::hmi(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::hmi)
{
    connect(this, &hmi::on_response_read_data_config,this, &hmi::data_read_config);
    connect(this, &hmi::on_response_percents_to_complete,this, &hmi::percents_to_complete);
    ui->setupUi(this);
}
/*data input form*/
void hmi::percents_to_complete(const int& percent){
    int value = percent;
    if(percent >100 ){
        value = 100;
    }
    if(percent < 0){
        value = 0;
    }
    this->ui->download_process->setValue(value);

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
hmi::~hmi()
{
    delete ui;
}

void hmi::on_read_btn_clicked()
{
    emit on_request_read_data_config("hmi");
}

void hmi::on_write_btn_clicked()
{
    QString data_out;
    QString input_serial_vehicle_value = this->ui->input_serial_vehicle->text();
    QString input_serial_module_value = this->ui->input_serual_module->text();
    /*prepare data*/
    emit on_request_write_data_config(data_out);
}

void hmi::on_write_firm_ware_clicked()
{
    QUrl folder_url = QUrl::fromLocalFile(get_link_director());
    emit on_request_write_firmware(folder_url);
    QString str_path = this->link_director;
    if( str_path == NULL) return;
    const char* path = str_path.toUtf8().constData();
   set_download_firmware_par(1,1,path);

}
//set_value_processbar(12);

void hmi::on_choose_file_btn_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                "Open File",
                "//",
                "hex(*.hex);; All File(*.*)");
    if( path == NULL) return;
    set_link_director(path);
    this->ui->link_director_file->setText(get_link_director());
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
void set_value_processbar(const int value){
    emit hmi::get_hmi()->on_response_percents_to_complete(value);
}

