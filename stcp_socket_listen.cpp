#include "stcp_socket_listen.h"
stcp_socket_listen::stcp_socket_listen(int cls): stcp_socket_base(AF_INET, SOCK_STREAM, IPPROTO_UDP, cls)
{

}
int stcp_socket_listen::recv(#void *buf, int size, int flag)
{
	return ERROR_NOT_SUPPORT;
}

