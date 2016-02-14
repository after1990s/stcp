#include "stcp_api.h"
void stcp_log(std::string log)
{
	std::cout << log << std::endl;
}

int stcp_startup()
{
    return ERROR_SUCCESS;
}
int stcp_socket(int af, int stream, int proto, int cls)
{
	assert(af == AF_INET);
	assert(stream == SOCK_STREAM);
	assert(proto == IPPROTO_UDP);
	assert(cls == stcp_class_enum::STCP_SOCKET_CONNECT || 
			cls == stcp_class_enum::STCP_SOCKET_LISTEN);
	int res = queue_socket::m_instance.socket_create(cls);
	if (res < 0)
	{
		stcp_log("queue_socket::socket_create faild");
		assert(false);
	}
	return res;
}
int stcp_bind(int socket, struct sockaddr *addr, int addrlen)
{
	int errnum = 0;
	stcp_socket_base * stcp = 
		queue_socket::m_instance.queue_query_index(socket);
	assert (stcp != nullptr);
	if (stcp == nullptr)
	{
		return ERROR_INVALID_SOCKET;
	}
	assert(stcp->get_socket_class() == \
			stcp_class_enum::STCP_SOCKET_LISTEN);
	if ((errnum = stcp->bind(addr, addrlen)) != ERROR_SUCCESS)
	{
		return errnum;	
	}
	return errnum;
}
int stcp_listen(int socket, int backlog)
{
	int errnum = 0;
	stcp_socket_base * stcp = 
		queue_socket::m_instance.queue_query_index(socket);
	assert (stcp != nullptr);
	if (stcp == nullptr)
	{
		return ERROR_INVALID_SOCKET;
	}
	assert(stcp->get_socket_class() == \
			stcp_class_enum::STCP_SOCKET_LISTEN);
	if (stcp->get_socket_class() != stcp_class_enum::STCP_SOCKET_LISTEN)
	{
		stcp_log("unexpcted socket type");
		return ERROR_INVALID_SOCKET;
	}
	return stcp->listen(backlog);
}
int stcp_accept(int socket, struct sockaddr *addr, int addrlen)
{
	int errnum = 0;
	stcp_socket_base * stcp = 
		queue_socket::m_instance.queue_query_index(socket);
	assert(stcp != nullptr);
	if (stcp == nullptr)
	{
		return ERROR_INVALID_SOCKET;
	}
	assert (stcp->get_socket_class() ==
			stcp_class_enum::STCP_SOCKET_LISTEN);
	if (stcp->get_socket_class() != 
			stcp_class_enum::STCP_SOCKET_LISTEN)
	{
		stcp_log("stcp_accept: unexpcted socket type");
		return ERROR_INVALID_SOCKET;
	}
	return stcp->accept(addr, addrlen);
}
int stcp_connect(int sockfd, struct sockaddr *addr, int addrlen)
{
	stcp_socket_base * stcp = 
		queue_socket::m_instance.queue_query_index(sockfd);
	assert (stcp != nullptr);
	if (stcp==nullptr)
	{
		return ERROR_INVALID_SOCKET;
	}
	assert(stcp->get_socket_class() == 
			stcp_class_enum::STCP_SOCKET_CONNECT);
	if (stcp->get_socket_class() != 
			stcp_class_enum::STCP_SOCKET_CONNECT)
	{
		stcp_log("stcp_connect: invalide socket");
		return ERROR_INVALID_SOCKET;
	}
	return stcp->accept(addr, addrlen);
}
int stcp_send(int sockfd, const void *buf, size_t len, int flags)
{
	stcp_socket_base * stcp = 
		queue_socket::m_instance.queue_query_index(sockfd);
	assert (stcp != nullptr);
	if (stcp==nullptr)
	{
		return ERROR_INVALID_SOCKET;
	}
	assert(stcp->get_socket_class() == 
			stcp_class_enum::STCP_SOCKET_CONNECT);
    return ERROR_SUCCESS;
}
int stcp_recv(int sockfd, void *buf, size_t len, int flags)
{
	stcp_socket_base * stcp = 
		queue_socket::m_instance.queue_query_index(sockfd);
	assert (stcp != nullptr);
	if (stcp==nullptr)
	{
		return ERROR_INVALID_SOCKET;
	}
	assert(stcp->get_socket_class() == 
			stcp_class_enum::STCP_SOCKET_CONNECT ||
		    stcp->get_socket_class() ==
			stcp_class_enum::STCP_SOCKET_ACCEPT);
	if (stcp->get_socket_class() != 
			stcp_class_enum::STCP_SOCKET_CONNECT &&
			stcp->get_socket_class() !=
			stcp_class_enum::STCP_SOCKET_ACCEPT)
	{
		stcp_log("stcp_recv: invalide socket");
		return ERROR_INVALID_SOCKET;
	}
    return stcp->recv(buf, len, flags);
}
int stcp_close(int sockfd)
{
	stcp_socket_base * stcp = 
		queue_socket::m_instance.queue_query_index(sockfd);
	assert (stcp != nullptr);
	if (stcp==nullptr)
	{
		return ERROR_INVALID_SOCKET;
	}
    return stcp->close();
}
