#include "pmu.h"
#include "ui_pmu.h"
#include <QFileDialog>
pmu::pmu(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::pmu)
{
    connect(this, &pmu::on_response_read_data_config,this, &pmu::data_read_config);
    ui->setupUi(this);
}
//void pmu::data_read_config(const QString &data){

//}
/*data input form ""*/
void pmu::data_read_config(const QString &data){
    QString esim, serial_module,serial_vehicle, firm_ware_ver, hard_ware_ver;
    /*process data*/


    /*add to value*/
    this->ui->esim_num->setText(esim);
    this->ui->serial_module->setText(serial_module);
    this->ui->serial_vehicle->setText(serial_vehicle);
    this->ui->firm_ware_ver->setText(firm_ware_ver);
    this->ui->hard_ware_ver->setText(hard_ware_ver);
}
pmu::~pmu()
{
    delete ui;
}

void pmu::on_read_btn_clicked()
{
    emit on_request_read_data_config("pmu");
}

void pmu::on_write_btn_clicked()
{
    QString data_out;
    QString input_serial_vehicle_value = this->ui->input_serial_vehicle->text();
    QString input_serial_module_value = this->ui->input_serual_module->text();
    /*prepare data*/
    emit on_request_write_data_config(data_out);
}

void pmu::on_write_firm_ware_clicked()
{
//    QFileDialog dialog(this);
//       dialog.setFileMode(QFileDialog::DirectoryOnly);
//       if (dialog.exec()) {
//           QString folderPath = dialog.selectedFiles().first();
//           QUrl folder_url = QUrl::fromLocalFile(folderPath);
//           this->ui->link_director_file->setText(folderPath);
//           emit on_request_write_firmware(folder_url);
//       }
}
