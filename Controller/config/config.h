#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

class config
{
public:
    config();
};
/*---------------------------------Firmware Download Config---------------------*/
#define FwConfigFolder      "Data/FwConfig"
#define FwConfigFile        "Data/FwConfig/FwConfig.txt"

#define bpMainapp       "BP - MainApp"
#define bpboot1         "BP - Bootloader 1"
#define bpboot2         "BP - Bootloader 2"

#define pmuMainapp      "PMU - MainApp"
#define pmuboot1        "PMU - Bootloader 1"
#define pmuboot2        "PMU - Bootloader 2"

#define hmiMainapp      "HMI - MainApp"
#define hmiboot1        "HMI - Bootloader 1"
#define hmiboot2        "HMI - Bootloader 2"

#define mcMainapp       "MC - MainApp"
#define mcboot1         "MC - Bootloader 1"
#define mcboot2         "MC - Bootloader 2"
/*---------------------------------BP TESTING CONFIG---------------------*/
#define wirteConfigKey    "selex123@"
/*---------------------------------TESTCASE---------------------*/
#define TestSiuteFolder      "TestSiute"
#define TestSiuteFile        "TestSiute/TestSiute.json"


#endif // CONFIG_H
