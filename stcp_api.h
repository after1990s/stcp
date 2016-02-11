#ifndef __STCP_API
#define __STCP_API
#include "stcp_errno.h"
#include "stcp_startup.h"
#include <sys/types.h>
#include <sys/socket.h>

extern "C"
{
    int stcp_startup();
    int stcp_socket(int af, int stream, int proto);
    int stcp_bind(int socket, struct sockaddr *addr, int addrlen);
    int stcp_listen(int socket, int backlog);
    int stcp_accept(int socket, struct sockaddr *addr, int addrlen);
    int stcp_connect(int sockfd, const struct sockaddr *addr, int addrlen);
    int stcp_send(int sockfd, const void *buf, size_t len, int flags); int stcp_recv(int sockfd, void *buf, size_t len, int flags);
    int stcp_close(int sockfd);
	void stcp_log(char* log);

}

#endif
