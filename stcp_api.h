#ifndef __STCP_API
#define __STCP_API
#include "stcp.h"
#include "stcp_errno.h"
#include "stcp_startup.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string>

extern "C"
{
    int stcp_startup();
    int stcp_socket(int af, int stream, int proto);
    int stcp_bind(int socket, struct sockaddr *addr, int addrlen);
    int stcp_listen(int socket, int backlog);
    int stcp_accept(int socket, struct sockaddr *addr, int addrlen);
    int stcp_connect(int sockfd, struct sockaddr *addr, int addrlen);
    int stcp_send(int sockfd, const void *buf, size_t len, int flags); int stcp_recv(int sockfd, void *buf, size_t len, int flags);
    int stcp_close(int sockfd);
	void stcp_log(std::string log);

}

#endif
