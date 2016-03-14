#ifndef __STCP_SOCKET_ACCEPT
#define __STCP_SOCKET_ACCEPT
#include "stcp_socket_tcp.h"
class stcp_socket_accept : public stcp_socket_tcp
{
	public:
		stcp_socket_accept(int cls);
		virtual ~stcp_socket_accept();
	public:
		virtual int bind(const struct sockaddr * addr, int addrlen) override;
		virtual int listen(int backlog) override;
		virtual int accept(struct sockaddr * addr, int addrlen) override;
		virtual int connect(struct sockaddr *addr, int addrlen) override;
		virtual int recv(void *buf, int size, int flag) override;
		virtual int send(const void * buf, int size, int flag) override;
		virtual int sendto(const void * buf, int size, int flag);

	public:
		virtual int on_recv() override;
		int on_send(SPKTEXT * pext_pkt);
		virtual int on_timer() override;
		int notify_recv(SPKTEXT *pext_pkt);//已经被其他类收到的数据，需要本类处理
};

#endif
