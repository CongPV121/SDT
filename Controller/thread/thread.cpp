#include "Controller/app_co/init/app_co_init.h"
#include "thread.h"
#include <QtDebug>
#include "Model/canopen/CO.h"
#include "Controller/app_co/od/od_config.h"
#include "Model/boot_master/boot_master_process.h"


thread::thread(QObject *parent) : QObject(parent)
{
    this->timer_10ms = new QTimer();
    this->timer_1ms = new QTimer();
    connect(this->timer_10ms,&QTimer::timeout,this,&thread::timeout_timer_10ms_handle);
    connect(this->timer_1ms,&QTimer::timeout,this,&thread::timeout_timer_1ms_handle);
    timer_10ms->start(1);
    timer_1ms->start(1);
}
uint64_t sys_timestamp = 0;
void thread::timeout_timer_10ms_handle(){
    sys_timestamp += 1;
    boot_master_process(&boot_master,sys_timestamp);

    qDebug()<< "tesst10";
}
void thread::timeout_timer_1ms_handle(){
    qDebug()<< "tesst1";
    CO_process(&CO_DEVICE,1);

}
thread* thread ::start_timer(){
    static thread* seft = new thread();
    return seft;
}
get_event::get_event()
{
}
void get_event::run(){
    while(1){
        app_process();
    }
}
