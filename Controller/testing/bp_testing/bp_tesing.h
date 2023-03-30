#ifndef BP_TESING_H
#define BP_TESING_H

#include <QObject>

class bp_tesing : public QObject
{
    Q_OBJECT
public:
    bp_tesing();
};
void read_bp_infor_config(void);

void send_write_node_id(void);
#endif // BP_TESING_H
