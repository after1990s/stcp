#ifndef __STCP_SOCKET_H
#define __STCP_SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <assert.h>
#include "stcp.h"
class stcp_socket_base
{
    public:
        stcp_socket_base(int sock_type, int sock_stream, int sock_proto, int cls);
        ~stcp_socket_base();

	public://apis.
		virtual int bind(const struct sockaddr * addr, int addrlen);
		virtual int listen(int backlog);
		virtual int accept(struct sockaddr * addr, int addrlen);
		virtual int connect(struct sockaddr *addr, int addrlen);
		virtual int recv(void *buf, int size, int flag);
		virtual int send(const void * buf, int size, int flag);

		int close_socket_force();
		int close_socket();

	public:
		virtual int on_recv();
		virtual int on_send();
		virtual int on_timer();


		void set_socket_class(int cls);
		int  get_socket_class();
	private:
		int m_index;//socket在pool中的index
		int m_class;//socket 类型
		int m_epoll;

	protected:
		int m_socket;//udp的socket

};
#endif
