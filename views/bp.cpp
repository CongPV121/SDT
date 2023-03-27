#include "bp.h"
#include "ui_bp.h"
#include <QFileDialog>
#include "Controller/controler.h"
#include "Controller/testing/testing.h"

bp::bp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bp)
{
    ui->setupUi(this);
}

bp::~bp()
{
    delete ui;
}

void bp::on_write_firm_ware_clicked()
{

}


void bp::on_choose_file_btn_clicked()
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
