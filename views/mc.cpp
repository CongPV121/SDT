#include "mc.h"
#include "ui_mc.h"

mc::mc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mc)
{
    ui->setupUi(this);
}

mc::~mc()
{
    delete ui;
}
