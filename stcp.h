#ifndef __STCP_H
#define __STCP_H
#include <assert.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netinet/in.h>
#include <errno.h>
#include "stcp_errno.h"

enum stcp_class_enum
{
	STCP_SOCKET_ACCEPT,
	STCP_SOCKET_CONNECT,
	STCP_SOCKET_LISTEN,

};

enum stcp_packet_cmd
{
	STCP_CMD_CONNECT,
	STCP_CMD_CONNECT_ACK,
	STCP_CMD_PSH,
	STCP_CMD_ACK,
	STCP_CMD_CLOSE,
	STCP_CMD_CLOSE_ACK,
	STCP_CMD_RESET
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
    unsigned short usid;//对端socket 的index值。发起连接时设置成0
}SPKTHDR;
#define STCP_PKT_DATA_SIZE (1024 - sizeof (SPKTHDR)- sizeof(short) -  sizeof(unsigned long) - sizeof(unsigned long))
typedef struct stcp_pkt_data
{
    short ackfreq;
    unsigned long urtt;//time.
    unsigned long usn_base;//serial
    char data[STCP_PKT_DATA_SIZE];
}SPKTDATA;
typedef struct stcp_pkt_connect{
	short ack;
	unsigned long urtt;
	unsigned long usn_base;
}SPKTCON;
typedef struct stcp_pkt_ack{
	short ack;
	unsigned long urtt;
	unsigned long usn_base;
}SPKTACK;
typedef struct stcp_pkt
{
    SPKTHDR hdr;
    union
    {
        SPKTDATA data;
		SPKTCON con;
		SPKTACK ack;
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
