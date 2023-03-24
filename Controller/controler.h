#ifndef CONTROLER_H
#define CONTROLER_H

#include <QObject>
#include "Controller/boot_master_app/boot_master_config.h"
#include "views/hmi.h"

class Controler : public QObject
{
    Q_OBJECT
public:
    explicit Controler(QObject *parent = nullptr);

signals:

};

#endif // CONTROLER_H
