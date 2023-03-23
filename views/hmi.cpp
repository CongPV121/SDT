#include "hmi.h"
#include "ui_hmi.h"
#include <QFileDialog>
hmi::hmi(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::hmi)
{
    connect(this, &hmi::on_response_read_data_config,this, &hmi::data_read_config);
    connect(this, &hmi::on_response_percents_to_complete,this, &hmi::percents_to_complete);
    ui->setupUi(this);
}
/*data input form*/
void hmi::percents_to_complete(const int &percent){

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
}

void hmi::on_choose_file_btn_clicked()
{
    QFileDialog dialog(this);
       dialog.setFileMode(QFileDialog::DirectoryOnly);
       if (dialog.exec()) {
           QString folderPath = dialog.selectedFiles().first();
           set_link_director(folderPath);

           this->ui->link_director_file->setText(get_link_director());

       }
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
