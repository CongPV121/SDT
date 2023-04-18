#ifndef LOGDATA_H
#define LOGDATA_H

#include <QObject>
class log
{
public:
    log();
};
extern QString ui_dataLog;
QString convert_bootMaster_state(int value);
void update_ui_dataLog(char *data);

#endif // LOGDATA_H
