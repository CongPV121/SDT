#include "bp.h"
#include "ui_bp.h"
#include <QFileDialog>
#include <QMessageBox>
#include "Controller/boot_master_app/boot_master_config.h"
#include "Controller/testing/bp_testing/bp_tesing.h"
#include "Controller/app_co/pdo/pdo.h"

bp::bp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bp)
{
    connect(this, &bp::on_response_bp_percents_to_complete,this, &bp::percents_bp_to_complete);
    connect(this, &bp::on_response_write_fw_button,this, &bp::on_write_write_fw_button);
    connect(this, &bp::on_response_read_bp_information_display,this, &bp::on_write_bp_information_display);

    connect(this, &bp::on_response_read_serial_number,this, &bp::on_write_serial_number);
    connect(this, &bp::on_response_read_fw_version,this, &bp::on_write_fw_version);
    connect(this, &bp::on_response_read_hw_version,this, &bp::on_write_hw_version);
    connect(this, &bp::on_response_device_mating,this, &bp::on_write_device_mating);

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
    emit p_bp->on_response_bp_percents_to_complete(value);

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
    set_download_firmware_par(1,BP_MAINAPP_NODE_ID,src_file,0x10000, bp_reboot_method,nullptr,nullptr);
    this->ui->write_firm_ware->setEnabled(1);
}


void bp::on_write_fw_clicked()
{

}


void bp::on_read_btn_clicked()
{

    read_bp_infor_config();

}
void bp_information_show(){
    bp* p_bp = bp::get_bp();
    if(p_bp == nullptr){
        return;
    }
    emit p_bp->on_response_read_bp_information_display();

}
void bp::on_write_bp_information_display(){
    this->ui->Vol->setText(QString::number(BP_infor.vol) + " mV");
    this->ui->soc->setText(QString::number(BP_infor.soc) + " %");
    this->ui->Cur->setText(QString::number(10*BP_infor.cur) + " mA");
    this->ui->soh->setText(QString::number(10*BP_infor.soh) + " %");
    this->ui->state->setText(QString::number(BP_infor.state) );
    this->ui->status->setText(QString::number(BP_infor.status) );
    this->ui->error_code->setText(QString::number(BP_infor.status) );
    this->ui->cycle->setText(QString::number(BP_infor.cycle) );
    /*Temp*/
    this->ui->temp1->setText(QString::number(BP_infor.temp[0]) + " oC");
    this->ui->temp2->setText(QString::number(BP_infor.temp[1]) + " oC");
    this->ui->temp3->setText(QString::number(BP_infor.temp[2]) + " oC");
    this->ui->temp4->setText(QString::number(BP_infor.temp[3]) + " oC");
    this->ui->temp5->setText(QString::number(BP_infor.temp[4]) + " oC");
    this->ui->temp6->setText(QString::number(BP_infor.temp[5]) + " oC");
    /*Cell Vol*/
    this->ui->V_cell->setText(QString::number(BP_infor.cell_vol[0]) + " mV");
    this->ui->V_cell_2->setText(QString::number(BP_infor.cell_vol[1]) + " mV");
    this->ui->V_cell_3->setText(QString::number(BP_infor.cell_vol[2]) + " mV");
    this->ui->V_cell_4->setText(QString::number(BP_infor.cell_vol[3]) + " mV");
    this->ui->V_cell_5->setText(QString::number(BP_infor.cell_vol[4]) + " mV");
    this->ui->V_cell_6->setText(QString::number(BP_infor.cell_vol[5]) + " mV");
    this->ui->V_cell_7->setText(QString::number(BP_infor.cell_vol[6]) + " mV");
    this->ui->V_cell_8->setText(QString::number(BP_infor.cell_vol[7]) + " mV");
    this->ui->V_cell_9->setText(QString::number(BP_infor.cell_vol[8]) + " mV");
    this->ui->V_cell_10->setText(QString::number(BP_infor.cell_vol[9]) + " mV");
    this->ui->V_cell_11->setText(QString::number(BP_infor.cell_vol[10]) + " mV");
    this->ui->V_cell_12->setText(QString::number(BP_infor.cell_vol[11]) + " mV");
    this->ui->V_cell_13->setText(QString::number(BP_infor.cell_vol[12]) + " mV");
    this->ui->V_cell_14->setText(QString::number(BP_infor.cell_vol[13]) + " mV");
    this->ui->V_cell_15->setText(QString::number(BP_infor.cell_vol[14]) + " mV");
    this->ui->V_cell_16->setText(QString::number(BP_infor.cell_vol[15]) + " mV");
    /* */
    uint16_t vol_cell_min = BP_infor.cell_vol[0];
    uint16_t vol_cell_max = BP_infor.cell_vol[0];
    for(uint8_t i = 1; i < 16; i++){
        if(BP_infor.cell_vol[i] >  vol_cell_max){
            vol_cell_max = BP_infor.cell_vol[i];
        }
        if(BP_infor.cell_vol[i] <  vol_cell_min){
            vol_cell_min = BP_infor.cell_vol[i];
        }
    }
    BP_infor.sn[0]='1';
    this->ui->cell_vol_max->setText(QString::number(vol_cell_max) + " mV");
    this->ui->cell_vol_min->setText(QString::number(vol_cell_min) + " mV");
}
void bp_hw_version_show(QString s_value){
    bp::get_bp()->on_response_read_hw_version(s_value);
}
void bp::on_write_hw_version(QString s_value){
    this->ui->hw_version->setText(s_value);
}

void bp_fw_version_show(QString s_value){
    bp::get_bp()->on_response_read_fw_version(s_value);

}
void bp::on_write_fw_version(QString s_value){
    this->ui->fw_version->setText(s_value);
}

void bp_sn_show(QString s_value){
    bp::get_bp()->on_write_serial_number(s_value);

}
void bp::on_write_serial_number(QString s_value){
    this->ui->seri_number->setText(s_value);
}

void bp_device_mating_show(QString s_value){
    bp::get_bp()->on_response_device_mating(s_value);

}
void bp::on_write_device_mating(QString s_value){
    this->ui->device_sn->setText(s_value);
}

void bp::on_write_btn_clicked()
{

}

void bp::on_write_firm_ware_2_clicked()
{

}


void bp::on_connect_dut_2_clicked()
{
    this->ui->write_config->setEnabled(1);
}


void bp::on_write_config_clicked()
{
    if(QMessageBox::question(this,"Tiếp tục","Nạp Cấu Hình ?") == QMessageBox::Yes ){
        QString bp_sn = this->ui->input_serial_vehicle->text();
        QString bp_sn_Upper = bp_sn.toUpper();
        write_sn_number(bp_sn_Upper);

        QString device_sn = this->ui->input_device_sn->text();
        QString snVehicle_Upper = device_sn.toUpper();
        write_device_mating(snVehicle_Upper);
    }

}

