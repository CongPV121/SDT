#include "logui.h"
#include "ui_logui.h"
#include <QTime>

logui::logui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logui)
{
    ui->setupUi(this);
    connect(this, &logui::on_request_update_logui,this, &logui::on_write_update_logui);

}

logui::~logui()
{
    delete ui;
}
logui* logui::get_logui(){
    static logui* seft;
    if(seft == nullptr){
        seft = new logui();
    }
    return seft;
}
void logui::on_write_update_logui(QString data){
    QStringList dataList = data.split("\n");
    for (const QString &data : dataList) {
        QTime  currentTime = QTime::currentTime();
        QString dataShow ;
        dataShow = "["+currentTime.toString()+"]" +" "+ data;
        this->ui->textBrowser->append(dataShow);

    }

}
void show_data_logui(QString data){
    //    logui* p_logui = logui::get_logui();
    //    emit p_logui->on_request_update_logui(data);
    emit logui::get_logui()->on_request_update_logui(data);
}
