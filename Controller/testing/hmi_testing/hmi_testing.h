#ifndef HMI_TESTING_H
#define HMI_TESTING_H

#include <QObject>

#define    HMI_TESTING_SDO_INDEX     0x2210
#define    TEST_ICON_SDO_SUBINDEX    0x00
#define    TEST_BLUE_SDO_SUBINDEX    0x01
#define    TEST_4G_SDO_SUBINDEX      0x02
#define    HMI_NODE_ID               8
class hmi_testing : public QObject
{
    Q_OBJECT
public:
    explicit hmi_testing(QObject *parent = nullptr);

signals:

};

void send_test_hmi_icon(void);
void send_test_hmi_blue(void);
void send_test_hmi_4G(void);
#endif // HMI_TESTING_H
