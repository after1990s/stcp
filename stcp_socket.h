#ifndef __STCP_SOCKET_H
#define __STCP_SOCKET_H
#include <sys/socket.h>
#include <assert.h>
class stcp_socket
{
    public:
        stcp_socket(int sock_type, int sock_stream, int sock_proto);
        ~stcp_socket();


}
#endif
