#ifndef HMI_TESTING_H
#define HMI_TESTING_H

#include <QObject>

#define    HMI_TESTING_SDO_INDEX             0x2210
#define    TEST_ACTIVE_ICON_SDO_SUBINDEX     0x00
#define    TEST_ICON_SDO_SUBINDEX            0x01

#define    TEST_BLUE_SDO_SUBINDEX            0x03
#define    TEST_4G_SDO_SUBINDEX              0x04

#define    HMI_CONFIG_SDO_INDEX              0x2211
#define    HMI_SERI_NUMBER_SDO_SUBINDEX      0
#define    HMI_DEVICE_NUMBER_SDO_SUBINDEX    1
#define    HMI_FW_VERSION_SDO_SUBINDEX       2
#define    HMI_HW_VERSION_SDO_SUBINDEX       3
#define    HMI_ESIM_NUMBER_SDO_SUBINDEX      4

#define    HMI_CONFIG_PAR_INDEX              0x2800
#define    HMI_READ_EVID_SUBINDEX              0
#define    HMI_WRITE_EVID_SUBINDEX              1
#define    HMI_ESIM_NUMBER_SUBINDEX             4


#define    HMI_NODE_ID                       8
class hmi_testing : public QObject
{
    Q_OBJECT
public:
    explicit hmi_testing(QObject *parent = nullptr);

signals:

};
extern bool testing_hmi;
void read_hmi_infor_config(void);
void write_hmi_sn( QString value );


void send_test_hmi_icon              (void);
void send_test_hmi_blue              (void);
void send_test_hmi_4G                (void);
void send_write_hmi_sn               (void);

void read_device_serial_number       (void);
void read_esim_number                (void);
void read_fw_version                 (void);
void read_hw_version                 (void);
void respone_read_device_serial_number       (void);
void respone_read_esim_number                (void);
void respone_read_fw_version                 (void);
void respone_read_hw_version                 (void);

bool  write_ev_id( QString value );
void send_write_ev_id(void);

#endif // HMI_TESTING_H
