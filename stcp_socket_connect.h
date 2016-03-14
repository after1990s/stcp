#ifndef __STCP_SOCKET_CONNECT_H
#define __STCP_SOCKET_CONNECT_H
#include "stcp_socket_tcp.h"
class stcp_socket_connect : public stcp_socket_tcp
{
	public: 
		stcp_socket_connect(int cls);
		virtual ~stcp_socket_connect();
	public:

};

#endif
