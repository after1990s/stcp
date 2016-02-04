#include "stcp_api.h"
int stcp_startup()
{
    return ERROR_SUCCESS;
}
int stcp_socket(int af, int stream, int proto)
{
    return ERROR_SUCCESS;
}
int stcp_bind(int socket, struct sockaddr *addr, int addrlen)
{
    return ERROR_SUCCESS;
}
int stcp_listen(int socket, int backlog)
{
    return ERROR_SUCCESS;
}
int accept(int socket, struct sockaddr *addr, int addrlen)
{
    return ERROR_SUCCESS;
}
int stcp_connect(int sockfd, const struct sockaddr *addr, int addrlen)
{
    return ERROR_SUCCESS;
}
int stcp_send(int sockfd, const void *buf, size_t len, int flags)
{
    return ERROR_SUCCESS;
}
int stcp_recv(int sockfd, void *buf, size_t len, int flags)
{
    return ERROR_SUCCESS;
}
int stcp_close(int sockfd)
{
    return ERROR_SUCCESS;
}

