#include "Controller/app_co/init/app_co_init.h"
#include "thread.h"
#include <QtDebug>
#include "Model/canopen/CO.h"
#include "Controller/app_co/od/od_config.h"
#include "Model/boot_master/boot_master_process.h"
#include "Controller/boot_master_app/boot_master_config.h"
#include "Controller/controler.h"
#include "Controller/testing/testing.h"

thread::thread(QObject *parent) : QObject(parent)
{
    this->timer_10ms            = new QTimer();
    this->timer_1ms             = new QTimer();
    this->timer_testing_process = new QTimer();
    this->timer_Notification    = new QTimer();

    connect(this->timer_10ms, &QTimer::timeout,this, &thread::timeout_timer_10ms_handle);
    connect(this->timer_1ms, &QTimer::timeout,this, &thread::timeout_timer_1ms_handle);
    connect(this->timer_testing_process, &QTimer::timeout,this,&thread::timeout_timer_testing_process_handle);
    connect(this->timer_Notification, &QTimer::timeout,this,&thread::timeout_timer_Notification_handle);

    timer_10ms->start(1);
    timer_1ms->start(1);
    timer_testing_process->start(10);
    timer_Notification->start(10);
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
uint64_t sys_timestamp = 0;
uint8_t value_process = 0;
void thread::timeout_timer_10ms_handle(){
    sys_timestamp += 1;
    boot_master_process(&boot_master,sys_timestamp,
                        &boot_master_config.start_download,
                        boot_master_config.nodeid_device,
                        boot_master_config.src_data_firmware,
                        boot_master_config.flash_image_start);


    //qDebug()<< "tesst10";
}
void thread::timeout_timer_Notification_handle(){
    /* display on ui for download process*/
    switch (boot_master_config.nodeid_device) {
    case HMI_MAINAPP_NODE_ID:
        if(boot_master.results.download_results == DOWNLOAD_SUCESS){
            set_value_processbar(100, (uint8_t)boot_master.base.state);
        }
        else{
            set_value_processbar(boot_master.results.percent_complete, (uint8_t)boot_master.base.state);
        }
        break;
    case BP_MAINAPP_NODE_ID:
        if(boot_master.results.download_results == DOWNLOAD_SUCESS){
            set_value_processbar(100, (uint8_t)boot_master.base.state);
        }
        else{
            set_value_processbar(boot_master.results.percent_complete, (uint8_t)boot_master.base.state);
        }

        break;
    default:
        break;
    }


}
void thread::timeout_timer_1ms_handle(){
    CO_process(&CO_DEVICE,1);

}
uint64_t sys_timestamp_testing = 0;
void thread::timeout_timer_testing_process_handle(){
    value_process ++;
    testing_sdo_process(&SDO_mailbox);


}


