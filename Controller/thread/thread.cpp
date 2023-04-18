#include "Controller/app_co/init/app_co_init.h"
#include "thread.h"
#include <QtDebug>
#include "Model/canopen/CO.h"
#include "Model/boot_master/boot_master_process.h"

#include "Controller/app_co/od/od_config.h"
#include "Controller/boot_master_app/boot_master_config.h"
#include "Controller/controler.h"
#include "Controller/testing/testing.h"
#include "Controller/app_co/pdo/pdo.h"
#include "Controller/log_data/logdata.h"

#include "views/bp.h"
#include "views/mc.h"
#include "views/camel.h"
#include "mainwindow.h"
#include "views/logui.h"

#include "Model/cp202-2ci/cp202.h"


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
                        boot_master_config.flash_image_start,
                        boot_master_config.src_data_firmware,
                        boot_master_config.reboot,
                        boot_master_config.ex_request);
    if(boot_master.base.is_state_change == true){
        ui_dataLog += convert_bootMaster_state((uint8_t)boot_master.base.state) +"\n";
    }
}
void thread::timeout_timer_Notification_handle(){
    /* display on ui for download process*/

    if(boot_master_config.show_proccess == nullptr) return;

        if(boot_master.results.download_results == DOWNLOAD_SUCESS){
            boot_master_config.show_proccess(100, (uint8_t)boot_master.base.state);
        }
        else{
            boot_master_config.show_proccess(boot_master.results.percent_complete,
                                    (uint8_t)boot_master.base.state);
        }

}
void thread::timeout_timer_1ms_handle(){
    CO_process(&CO_DEVICE,1);

}
/* timer 10ms*/
uint64_t sys_timestamp_testing = 0;
int cp202_st;
void thread::timeout_timer_testing_process_handle(){
    if( debounce_fw_download > 0){
        debounce_fw_download -= 10;
    }
    value_process ++;
    testing_sdo_process(&SDO_mailbox);
    if(pdo_data_processing()){
        bp_information_show();
    }
    int cp202_st_read = cp202_device_is_connected();
    if(cp202_st != cp202_st_read){
        cp202_st = cp202_st_read;
        CP202_set_state(cp202_st_read);
    }
    /*show data log*/
    update_ui_dataLog(logDataArr);

    QString dataUpdate = ui_dataLog;
    ui_dataLog.clear();
    if(dataUpdate.size() > 0){
        show_data_logui(dataUpdate);

    }


}


