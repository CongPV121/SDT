#ifndef DOWNLOADFW_H
#define DOWNLOADFW_H

#include <QObject>


class downloadFW
{
public:
    downloadFW();
};

typedef struct
{
    QString nameDevice;
    QString codeDevice;
    QString linkFile ;
    QString version ;

}fwConfig;

void downloadfwIntit(void);
bool setConfigDevice(QString codeDevice,QString srcHexFile);

extern QVector<fwConfig>   fwConfiglist;

#endif // DOWNLOADFW_H
