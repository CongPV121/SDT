//
// Created by vnbk on 16/03/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//#include<QtDebug>

#ifdef __linux
#include <unistd.h>
#endif
//#include <QDebug>
#include "cp202.h"
#include "tcp_client.h"

#define CP202_PACKET_LENGTH         13
#define CP202_FRAME_ID_LENGTH       4
#define CP202_FRAME_DATA_LENGTH     8

#define CP202_MAX_PACKET            50
#define CP202_MAX_BUFFER            (CP202_PACKET_LENGTH)


#define CP202_FRAME_INFO_DEFAULT        0x00
#define CP202_FRAME_INFO_LENGTH_MASK    0x0F

typedef struct cp202_packet {
    uint8_t m_info;
    uint32_t m_frame_id;
    uint8_t m_data_len;
    uint8_t m_frame_data[CP202_FRAME_DATA_LENGTH];
}cp202_packet_t;

struct cp202{
    tcp_client_t* m_tcp_client;
    int m_port;
    const char* m_host;

    cp202_can_receive_callback_fn m_callback;
};

static cp202_t g_cp202_df = {
    .m_tcp_client = NULL,
    .m_port = 0,
    .m_host = NULL
};

cp202_t* cp202_create(const char* host, int port){
    tcp_client_t* client = tcp_client_create();
    if(!client){
        return NULL;
    }
    cp202_t* obj = (cp202_t*)malloc(sizeof(cp202_t));
    if(!obj){
        free(client);
        return NULL;
    }
    obj->m_tcp_client = client;
    obj->m_host = host;
    obj->m_port = port;
    return obj;
}

cp202_t* cp202_create_default(const char* host, int port){
    tcp_client_t* client = tcp_client_create_default();
    if(!client){
        return NULL;
    }
    g_cp202_df.m_tcp_client = client;
    g_cp202_df.m_host = host;
    g_cp202_df.m_port = port;

    return &g_cp202_df;
}

int cp202_register_recv_callback(cp202_t* self, cp202_can_receive_callback_fn callback_fn){
    if(!self)
        return -1;

    self->m_callback = callback_fn;
    return 0;
}

int cp202_connect(cp202_t* self){
    if(!tcp_client_is_connected(self->m_tcp_client)){
        if(tcp_client_connect(self->m_tcp_client, self->m_host, self->m_port) < 0){
            //usleep(1000*1000);
            return 0;
            //qDebug()<<"connected";
        }
    }
    //    if(self){
    //        return tcp_client_connect(self->m_tcp_client, self->m_host, self->m_port);
    //    }
    //qDebug()<<"connect fail";
    return 1;
}
int cp202_reconnect(cp202_t *self){
    if(self == NULL) return 0;
    if(tcp_client_connect(self->m_tcp_client, self->m_host, self->m_port) < 0){
        return 0;
    }
    return 1;

}

int cp202_disconnect(cp202_t* self){
    if(self){
        return tcp_client_disconnect(self->m_tcp_client);
    }
    return -1;
}

int cp202_is_connected(cp202_t* self){
    if(self){
        return tcp_client_is_connected(self->m_tcp_client);
    }
    return -1;
}

int cp202_send(cp202_t* self, uint32_t frame_id, const unsigned char* data, int len, int timeout){
    if(!self){
        return -1;
    }
    if(len > CP202_FRAME_DATA_LENGTH){
        return -1;
    }
    uint8_t buf[CP202_PACKET_LENGTH] = {0,};
    int index = 0;
    buf[index++] = CP202_FRAME_INFO_DEFAULT | (len & CP202_FRAME_INFO_LENGTH_MASK);
    buf[index++] = (frame_id >> 24) & 0xFF;
    buf[index++] = (frame_id >> 16) & 0xFF;
    buf[index++] = (frame_id >> 8) & 0xFF;
    buf[index++] = frame_id & 0xFF;
    for(int i = 0; i < len; i++){
        buf[index++] = data[i];
    }

    return tcp_client_send(self->m_tcp_client, buf, index, timeout);
}

int cp202_recv(cp202_t* self, unsigned char* buf, int max_len, int timeout){
    if(self){
        return tcp_client_recv(self->m_tcp_client, buf, max_len, timeout);
    }
    return -1;
}

static int cp202_decode_packet(const uint8_t* data, int len, cp202_packet_t* packets){
    if(len < CP202_PACKET_LENGTH){
        return -1;
    }
    cp202_packet_t* packet = packets;
    int number = 0;

    for(int i = 0; i < len; i += CP202_PACKET_LENGTH){
        memset(packet, 0, sizeof(cp202_packet_t));

        packet->m_info = data[i];
        packet->m_data_len = packet->m_info & CP202_FRAME_INFO_LENGTH_MASK;

        packet->m_frame_id |= ((uint32_t)data[i+1] << 24);
        packet->m_frame_id |= ((uint32_t)data[i+2] << 16);
        packet->m_frame_id |= ((uint32_t)data[i+3] << 8);
        packet->m_frame_id |= ((uint32_t)data[i+4] << 0);

        memcpy(packet->m_frame_data, &data[i+5], CP202_FRAME_DATA_LENGTH);

        packet = &packets[number++];

        //if(packet->m_frame_id == 0x80) {
        //            printf("CanBus Packet Info, data length = %d\n", packet->m_info & CP202_FRAME_INFO_LENGTH_MASK);
        //printf("CanBus Packet Frame ID: 0x%02X\n", packet->m_frame_id);
        //printf("CanBus Packet Frame data0: 0x%02X\n", packet->m_frame_data[0]);
        //            printf("CanBus Packet Frame data1: 0x%02X\n", packet->m_frame_data[1]);
        //            printf("CanBus Packet Frame data2: 0x%02X\n", packet->m_frame_data[2]);
        //}
    }
    return number;
}


int cp202_process(cp202_t* self){
    if(!self) {
        return -1;
    }
    if(!tcp_client_is_connected(self->m_tcp_client)){
        return 0;

        if(tcp_client_connect(self->m_tcp_client, self->m_host, self->m_port) < 0){
            //usleep(1000*1000);
            return 0;
        }
    }

    uint8_t buf[CP202_MAX_BUFFER];
    int len = tcp_client_recv(self->m_tcp_client, buf, CP202_MAX_BUFFER, 0);
    if(len > 0){
        cp202_packet_t packet[CP202_MAX_PACKET];
        int packet_number = cp202_decode_packet(buf, len, packet);
        if(packet_number <= 0){
            return 0;
        }
        if(self->m_callback){
            self->m_callback(packet->m_frame_id, packet->m_frame_data);


        }
    }
}
int get_fd(cp202_t* self){

    return tcp_client_get_fd(self->m_tcp_client);
}
