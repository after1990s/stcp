#include "stcp_cache.h"
#include "stcp_socket_base.h"
#include "stcp_socket_listen.h"
#include "stcp_api.h"
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
void thread_cache_test(void)
{
    stcp_cache cache;
    for (int i=0; i< 20; i++)
    {
        cache.alloc(i);
    }
    for (int i=0; i< 20; i++)
    {
        cache.free(i,1);
    }
}

void thread_listen_test(void)
{
	int s_listen =  stcp_socket(AF_INET, 
			SOCK_STREAM, 
			IPPROTO_UDP);
	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8008);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	stcp_bind(s_listen, (struct sockaddr*)&addr, sizeof(addr));
	stcp_listen(s_listen, 30);
	struct sockaddr_in rmt_addr = {0};
	
	while (int s_accept = stcp_accept(s_listen,
				(struct sockaddr*)&rmt_addr, 
				sizeof(rmt_addr)))
	{
		stcp_close(s_listen);
	}
}

int main(void)
{

//    std::thread t(thread_cache_test);
 //   t.join();
	std::thread t1(thread_listen_test);
	t1.join();
    return 0;
}
