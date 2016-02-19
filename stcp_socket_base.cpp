#include "stcp_socket_base.h"
stcp_socket_base::stcp_socket_base(int sock_type,int sock_stream,int sock_proto, int cls): m_class(cls)
{
    assert(sock_type==AF_INET);
    assert(sock_stream==SOCK_STREAM);
    assert(sock_proto==IPPROTO_UDP);

	m_socket = socket(sock_type, sock_stream, sock_proto);
	int b0 = 1;
	setsockopt(m_socket, IPPROTO_IP, IP_DONTFRAG, &b0, sizeof(b0));
}
stcp_socket_base::~stcp_socket_base()
{

}


int stcp_socket_bas::bind(const struct sockaddr * addr,int addrlen)
{
	return ERROR_NOT_SUPPORT;
	
}

int stcp_socket_base::listen(int backlog)
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_base::accept(struct sockaddr * addr,int addrlen)
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_base::connect(struct sockaddr *addr,int addrlen)
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_base::recv(void *buf,int size,int flag)
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_base::send(const void * buf,int size,int flag)
{
	return ERROR_NOT_SUPPORT;
}

int stcp_socket_base::close_socket_force()
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_base::close_socket()
{
	return ERROR_NOT_SUPPORT;
}

void stcp_socket_base::set_socket_class(int cls)
{
	return ERROR_NOT_SUPPORT;
}
int  stcp_socket_base::get_socket_class()
{
	return ERROR_NOT_SUPPORT;
}

