#ifndef BP_TESING_H
#define BP_TESING_H

#include <QObject>
#define BMS_OBJECT_INDEX										0x2003
#define BMS_SERIAL_NUMBER_OBJECT_SUB_INDEX						0x00
#define BMS_MAINSWITCH_SUB_INDEX								0x01
#define SLAVE_ID_NUMBER_OBJECT_SUB_INDEX						0x02

#define MATING_INDEX											0x2004
#define BP_MATING_STATE_SN_OBJECT_SUB_INDEX						0x00
#define VEHICLE_SN_OBJECT_SUB_INDEX								0x01

#define BMS_CONFIG_INDEX									    0x2005
#define WRITE_SERIAL_NUMBER_SUB_INDEX							0x00

#define BMS_LOG_DATA_INDEX									    0x2006
#define PDO_REQUEST_SUB_INDEX									0x00

#define NEW_FIRMWARE_REQUEST_INDEX								0x2001
class bp_tesing : public QObject
{
    Q_OBJECT
public:
    bp_tesing();
};
void read_bp_infor_config(void);

void  request_pdo1(void);
void  request_pdo2(void);
void  request_pdo3(void);
void  request_pdo4(void);
void  request_pdo5(void);
void  request_pdo6(void);
void  read_sn(void);
void  read_hw_bp_version(void);
void  read_fw_bp_version(void);
void  read_device_mating(void);
void  send_device_sn_mating_bp(void);
void  send_sn_bp(void);
bool  write_device_mating( QString value );
bool  write_sn_number( QString value );

#endif // BP_TESING_H
