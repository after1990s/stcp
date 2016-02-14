#ifndef __STCP_H
#define __STCP_H
#include <assert.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "stcp_errno.h"

enum stcp_class_enum
{
	STCP_SOCKET_ACCEPT,
	STCP_SOCKET_CONNECT,
	STCP_SOCKET_LISTEN,

};

enum stcp_packet_cmd
{
    
};

enum stcp_socket_status
{
    STCP_STATUS_NULL,
    STCP_STATUS_CREATED,
    STCP_STATUS_BINDED,
    STCP_STATUS_LISTENED,
    STCP_STATUS_CONNECTING,
    STCP_STATUS_CONNECTED,
    STCP_STATUS_RESET,
    STCP_STATUS_CLOSED
};
#pragma pack(push)
#pragma pack(1)
typedef struct stcp_packet_header
{
    unsigned short ucmd;
    unsigned short usid;
}SPKTHDR;
#define STCP_PKT_DATA_SIZE (1024 - sizeof (SPKTHDR)- sizeof(short) -  sizeof(unsigned long) - sizeof(unsigned long))
typedef struct stcp_pkt_data
{
    short ackfreq;
    unsigned long urtt;//time.
    unsigned long usnBase;//serial
    char data[STCP_PKT_DATA_SIZE];
}SPKTDATA;

typedef struct stcp_pkt
{
    SPKTHDR hdr;
    union
    {
        SPKTDATA data;
    }body;
}SPKT;
typedef struct stcp_pkt_ext
{
    int pkt_size;
    int data_size;
    int data_offset;
    SPKT pkt;
}SPKTEXT;
#pragma pop()
#endif
