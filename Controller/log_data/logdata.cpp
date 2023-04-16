#include "logdata.h"

QString dataLog;

log::log()
{

}

QString convert_bootMaster_state(int value){
    switch(value) {
    case 0:
        return "BOOT_ST_INIT";
    case 1:
        return "BOOT_ST_PREPARING";
    case 2:
        return "BOOT_ST_LOADING_SERVER";
    case 3:
        return "BOOT_ST_LOADING_LOCAL";
    case 4:
        return "BOOT_ST_DOWNLOAD_COMPLETED";
    case 5:
        return "BOOT_ST_FAIL";
    case 6:
        return "BOOT_ST_VALIDATING";
    case 7:
        return "BOOT_ST_WAITING_EXT_BOOT";
    case 8:
        return "BOOT_ST_WRITE_VERSION";
    case 9:
        return "BOOT_ST_READ_INFO";
    case 10:
        return "BOOT_ST_NOT_ACTIVE";
    case 11:
        return "BOOT_ST_EXT_REQUEST";
    default:
        return "Unknown";

    }

}
