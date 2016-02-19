#ifndef __STCP_SOCKET_TCP_H
#define __STCP_SOCKET_TCP_H
#include "stcp_socket_base.h"
class stcp_socket_tcp: stcp_socket_base
{
	public:
		stcp_socket_tcp ();
		virtual int bind(const struct sockaddr * addr, int addrlen) override;
		virtual int listen(int backlog) override;
		virtual int accept(struct sockaddr * addr, int addrlen) override;
		virtual int connect(struct sockaddr *addr, int addrlen) override;
		virtual int recv(void *buf, int size, int flag) override;
		virtual int send(const void * buf, int size, int flag) override;

	public:
		virtual int on_recv() override;
		virtual int on_timer() override;

	private:
		unsigned int m_passed_sn;//已经确认的sn
		unsigned int m_current_sn;//
		unsigned int m_avaiable_sn;//允许传输的最大sn
		
		unsigned int m_rtl;

};
#endif
