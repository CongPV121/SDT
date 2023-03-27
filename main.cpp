#include <QtQuick>
#include <QApplication>
#include "Controller/thread/thread.h"
#include <QThread>
#include <QtDebug>
#include "Controller/app_co/init/app_co_init.h"
#include "Model/boot_master/boot_master_process.h"
#include "moc_predefs.h"
#include "mainwindow.h"
//can_handle * can_receive;
uint8_t data[8] = {1};
uint8_t data0 = 0;
int write_cnt = 0;

#ifdef WIN32
#include <winsock2.h>
#endif

int main(int argc, char *argv[])
{
#ifdef WIN32
WSADATA wsadata;
if (WSAStartup(MAKEWORD(1,1), &wsadata) == SOCKET_ERROR) {
printf("Error creating socket.");
return -1;
}
#endif
    QApplication a(argc, argv);
    MainWindow w;
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
