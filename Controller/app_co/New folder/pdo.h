#ifndef PDO_H
#define PDO_H

//#include "stdint.h"



class pdo
{
public:
    pdo();
};


typedef struct {
    bool new_msg;
    uint8_t data[8];
} MSG_buff;
typedef struct {
    MSG_buff BP_PDO1;
    MSG_buff BP_PDO2;
    MSG_buff BP_PDO3;
    MSG_buff BP_PDO4;
    MSG_buff BP_PDO5;
    MSG_buff BP_PDO6;
    MSG_buff BP_PDO7;

} BP_PDO;

extern BP_PDO BP_data;
void pdo_process_handle(uint32_t canid, uint8_t *data);



#endif // PDO_H
