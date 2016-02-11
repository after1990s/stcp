#ifndef __STCP_SOCKET_H
#define __STCP_SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <assert.h>
class stcp_socket_base
{
    public:
        stcp_socket_base(int sock_type, int sock_stream, int sock_proto);
        ~stcp_socket_base();

		int close_socket_force();
		int close_socket();

	private:
		int m_index;//socket在pool中的index
		int m_socket;//udp的socket

};
#endif
