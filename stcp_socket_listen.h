#ifndef __STCP_SOCKET_LISTEN
#define __STCP_SOCKET_LISTEN
#include "stcp_socket_base.h"
class stcp_socket_listen : stcp_socket_base
{
	public:
		stcp_socket_listen(int cls);

		int bind(const struct sockaddr * addr, int addrlen) override;
		int listen(int backlog) override;
        int accept(struct sockaddr * addr, int addrlen) override;
        int connect(struct sockaddr *addr, int addrlen) override;
	    int recv(void *buf, int size, int flag) override;
	    int send(const void * buf, int size, int flag) override;
									 
	private:
		struct sockaddr m_bind_addr;
	    
};
#endif
