QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/app_co/init/app_co_init.c \
    Controller/app_co/od/comm_od/comm_od.c \
    Controller/app_co/od/comm_od/comm_od_default_value.c \
    Controller/app_co/od/manu_od/manu_od.c \
    Controller/app_co/od/manu_od/manu_od_default_value.c \
    Controller/app_co/od/od.c \
    Controller/boot_master_app/boot_master_config.c \
    Controller/thread/thread.cpp \
    Model/boot_master/CRC.c \
    Model/boot_master/boot_master.c \
    Model/boot_master/boot_master_process.c \
    Model/boot_master/bootloader.c \
    Model/boot_master/firmware.c \
    Model/boot_master/segment_driver.c \
    Model/boot_master/segment_firmware.c \
    Model/canopen/CO.c \
    Model/canopen/CO_CAN_Msg.c \
    Model/canopen/CO_CRC.c \
    Model/canopen/CO_EMCY.c \
    Model/canopen/CO_FLASH.c \
    Model/canopen/CO_NMT.c \
    Model/canopen/CO_OD.c \
    Model/canopen/CO_OD_sign.c \
    Model/canopen/CO_OD_storage.c \
    Model/canopen/CO_Object.c \
    Model/canopen/CO_PDO.c \
    Model/canopen/CO_RPDO.c \
    Model/canopen/CO_SDO.c \
    Model/canopen/CO_SDOclient.c \
    Model/canopen/CO_SDOserver.c \
    Model/canopen/CO_SYNC.c \
    Model/canopen/CO_TPDO.c \
    Model/cp202-2ci/cp202.c \
    Model/cp202-2ci/tcp_client.c \
    Model/extract_file/CRC.c \
    Model/extract_file/boot_master.c \
    Model/extract_file/boot_master_app.c \
    Model/extract_file/bootloader.c \
    Model/extract_file/firmware.c \
    Model/extract_file/intel_hex.c \
    Model/extract_file/ota_bms.c \
    Model/extract_file/segment_firmware.c \
    main.cpp \
    sdt.cpp

    # Default rules for deployment.
    qnx: target.path = /tmp/$${TARGET}/bin
    else: unix:!android: target.path = /opt/$${TARGET}/bin
    !isEmpty(target.path): INSTALLS += target
HEADERS += \
    Controller/app_co/init/app_co_init.h \
    Controller/app_co/od/comm_od/comm_od.h \
    Controller/app_co/od/comm_od/comm_od_default_value.h \
    Controller/app_co/od/manu_od/manu_od.h \
    Controller/app_co/od/manu_od/manu_od_default_value.h \
    Controller/app_co/od/od.h \
    Controller/app_co/od/od_config.h \
    Controller/boot_master_app/app_can_config.h \
    Controller/boot_master_app/boot_master_config.h \
    Controller/thread/thread.h \
    Model/boot_master/CO_utils.h \
    Model/boot_master/CRC.h \
    Model/boot_master/boot_master.h \
    Model/boot_master/boot_master_process.h \
    Model/boot_master/bootloader.h \
    Model/boot_master/firmware.h \
    Model/boot_master/segment_driver.h \
    Model/boot_master/segment_firmware.h \
    Model/canopen/CO.h \
    Model/canopen/CO_CAN_Msg.h \
    Model/canopen/CO_CRC.h \
    Model/canopen/CO_EMCY.h \
    Model/canopen/CO_FLASH.h \
    Model/canopen/CO_NMT.h \
    Model/canopen/CO_OD.h \
    Model/canopen/CO_OD_sign.h \
    Model/canopen/CO_OD_storage.h \
    Model/canopen/CO_Object.h \
    Model/canopen/CO_PDO.h \
    Model/canopen/CO_RPDO.h \
    Model/canopen/CO_SDO.h \
    Model/canopen/CO_SDOclient.h \
    Model/canopen/CO_SDOserver.h \
    Model/canopen/CO_SYNC.h \
    Model/canopen/CO_TPDO.h \
    Model/canopen/CO_config.h \
    Model/canopen/CO_slave.h \
    Model/canopen/CO_utils.h \
    Model/cp202-2ci/cp202.h \
    Model/cp202-2ci/tcp_client.h \
    Model/extract_file/CRC.h \
    Model/extract_file/app_boot_config.h \
    Model/extract_file/boot_master.h \
    Model/extract_file/boot_master_app.h \
    Model/extract_file/bootloader.h \
    Model/extract_file/firmware.h \
    Model/extract_file/intel_hex.h \
    Model/extract_file/ota_bms.h \
    Model/extract_file/segment_firmware.h \
    sdt.h

FORMS += \
    sdt.ui


