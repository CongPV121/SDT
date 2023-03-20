#include "sdt.h"
#include <QApplication>
#include "Controller/thread/thread.h"
#include <QThread>
#include <QtDebug>
#include "Controller/app_co/init/app_co_init.h"
#include "Model/boot_master/boot_master_process.h"

//can_handle * can_receive;
uint8_t data[8] = {1};
uint8_t data0 = 0;
int write_cnt = 0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SDT w;
    w.show();

    app_co_init();
    boot_master_init();

    /* start receive can msg */
    get_event can_receive;
    can_receive.start();

    /* start timer processing  */
    thread::start_timer();
    return a.exec();
}
