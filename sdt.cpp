#include "sdt.h"
#include "ui_sdt.h"
#include <QTimer>
#include <QtDebug>

#include "Model/canopen/CO.h"
#include "Controller/app_co/od/od_config.h"


SDT::SDT(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SDT)
{
    ui->setupUi(this);

}

SDT::~SDT()
{
    delete ui;
}


