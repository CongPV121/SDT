#include "downloadfw.h"
#include "views/downfw_config.h"
#include "Controller/config/config.h"
#include "Controller/boot_master_app/boot_master_config.h"

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
    ba = srcHexFile.toLatin1();
    const char* path = ba.data();
    memcpy(src_file,path,srcHexFile.length());
    if(codeDevice == bpMainapp){
        set_download_firmware_par(1,BP_MAINAPP_NODE_ID,src_file,0x10000, bp_reboot_method);

    }
    else if(codeDevice == bpboot1){

    }
    else if(codeDevice == bpboot2){

    }
    else if(codeDevice == pmuMainapp){

    }
    else if(codeDevice == pmuboot1){

    }
    else if(codeDevice == pmuboot2){

    }
    else if(codeDevice == hmiMainapp){

    }
    else if(codeDevice == hmiboot1){

    }
    else if(codeDevice == hmiboot2){

    }
    else if(codeDevice == mcMainapp){

    }
    else if(codeDevice == mcboot1){

    }
    else if(codeDevice == mcboot2){

    }

    return false;
}
