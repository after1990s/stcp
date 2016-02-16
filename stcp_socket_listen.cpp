#include "stcp_socket_listen.h"
stcp_socket_listen::stcp_socket_listen(int cls): stcp_socket_base(AF_INET, SOCK_STREAM, IPPROTO_UDP, cls)
{

}

int stcp_socket_listen::bind(const struct sockaddr * addr, int addrlen) 
{
	int ret = ::bind(m_socket, addr, addrlen);
	if (ret == 0)
	{
		memset (&m_bind_addr, addr, addrlen);
	}
	return ret;
}
int stcp_socket_listen::listen(int backlog)
{
	return ::listen(backlog);
}
int stcp_socket_listen::accept(struct sockaddr * addr, int addrlen) 
{

	//recv a connect pkt;

	return ERROR_NOT_SUPPORT;
}
int stcp_socket_listen::connect(struct sockaddr *addr, int addrlen) 
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_listen::recv(void *buf, int size, int flag)
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_listen::send(const void *buf, int size, int flag)
{
	return ERROR_NOT_SUPPORT;
}
