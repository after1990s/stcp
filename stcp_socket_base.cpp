#include "stcp_socket.h"
stcp_socket_base::stcp_socket_base(int sock_type, int sock_stream, int sock_proto)
{
    assert(sock_type==AF_INET);
    assert(sock_stream==SOCK_STREAM);
    assert(sock_proto==IPPROTO_UDP);

}

