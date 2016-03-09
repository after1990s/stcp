/*
Author: after1990s
Date: Mar 23 2016
Describe: stcp_socket_listen bind and listen on a UDP socket.
*/


#ifndef __STCP_SOCKET_LISTEN
#define __STCP_SOCKET_LISTEN
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <stack>
#include "stcp_socket_base.h"
#include "queue_socket.h"
class stcp_socket_listen : public stcp_socket_base
{
	public:
		stcp_socket_listen(int cls);

		//APIs for user call
		int bind(const struct sockaddr * addr, int addrlen) override;
		int listen(int backlog) override;
        int accept(struct sockaddr * addr, int addrlen) override;

	public:
		int on_recv() override;
		int on_timer() override;
									 
	private:
		//回送连接成功,并设置accptedid的状态，对端ip地址等信息
		void connect_accepted_notify(int accpteid);
		
		//回送reset
		void sendback_reset(struct sockaddr * src_addr);
		//this two apis did not use in stcp_socket_listen
		int connect(struct sockaddr *addr, int addrlen) override;
	    int recv(void *buf, int size, int flag) override;
	    int send(const void * buf, int size, int flag) override;

		


	private:
		struct sockaddr m_bind_addr;
	    std::stack<int> m_accepted_stk;
};
#endif
