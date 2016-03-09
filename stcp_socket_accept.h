#ifndef __STCP_SOCKET_ACCEPT
#define __STCP_SOCKET_ACCEPT
#include "stcp_socket_tcp.h"
class stcp_socket_accept : public stcp_socket_tcp
{
	public:
		stcp_socket_accept(int cls);
	public:
		int notify_recv(SPKT *pkt);//已经被其他类收到的数据，需要本类处理
};

#endif
