#include "downloadfw.h"
#include "views/downfw_config.h"
#include "Controller/config/config.h"
#include "Controller/boot_master_app/boot_master_config.h"
#include <QFileDialog>
#include "views/camel.h"

QVector<fwConfig>   fwConfiglist;

downloadFW::downloadFW()
{

}
void downloadfwIntit(void){
    FwConfigListInit();
}

static char src_file[1024];
bool setConfigDevice(QString codeDevice, QString srcHexFile){

    QByteArray ba;
    QFile file(srcHexFile);
    if (!file.exists()) {
        return false;
    }
    ba = srcHexFile.toLatin1();
    const char* path = ba.data();
    memset(src_file,0,1024);
    memcpy(src_file,path,srcHexFile.length());
    if(codeDevice == bpMainapp){
        return set_download_firmware_par(1,BP_MAINAPP_NODE_ID,src_file,0x10000,
                                         boot2_bp_reboot,boot2_bp_exRequest,set_value_processbar_camel);
    }

    else if(codeDevice == bpboot2){
        return set_download_firmware_par(1,BP_MAINAPP_NODE_ID,src_file,0x8000,
                                         boot1_bp_reboot,boot1_bp_exRequest,set_value_processbar_camel);

    }
    else if(codeDevice == pmuMainapp){
        return set_download_firmware_par(1,PMU_MAINAPP_NODE_ID,src_file,0x10000,
                                         boot2_pmu_reboot,boot2_pmu_exRequest,set_value_processbar_camel);

    }
    else if(codeDevice == pmuboot2){
        return set_download_firmware_par(1,PMU_MAINAPP_NODE_ID,src_file,0x8000,
                                         boot1_pmu_reboot,boot1_pmu_exRequest,set_value_processbar_camel);

    }
    else if(codeDevice == hmiMainapp){
        return set_download_firmware_par(1,HMI_MAINAPP_NODE_ID,src_file,0x10000,
                                         boot2_hmi_reboot,boot2_hmi_exRequest,set_value_processbar_camel);

    }
    else if(codeDevice == hmiboot2){
        return set_download_firmware_par(1,HMI_MAINAPP_NODE_ID,src_file,0x8000,
                                         boot1_hmi_reboot,boot1_hmi_exRequest,set_value_processbar_camel);

    }
    else if(codeDevice == mcMainapp){
        return set_download_firmware_par(1,MC_MAINAPP_NODE_ID,src_file,0x08007800,
                                         boot2_mc_reboot,boot2_mc_exRequest, set_value_processbar_camel);

    }
    else if(codeDevice == mcboot2){
        return set_download_firmware_par(1,MC_MAINAPP_NODE_ID,src_file,0x0801A800,
                                         boot1_mc_reboot,boot1_mc_exRequest, set_value_processbar_camel);

    }
    return false;
}
