/*
这个类用于分配，保存，查询的stcp_socket实例。
提供几种查询方式：
1.按照index
2.按照remoteaddr
3.按照usid
*/
#ifndef __QUEUE_SOCKET_H
#define __QUEUE_SOCKET_H
#include "stcp_socket_base.h"
#include "stcp_socket_connect.h" 
#include "stcp_socket_accept.h" 
#include "stcp_socket_listen.h" 
#include "stcp.h"
#include "stcp_errno.h"
#include <mutex>
#include <atomic>
#include <cstdlib>

#define MAXSIZE_SOCKET (1024)
typedef struct _s_queue_socket
{
	stcp_socket_status status;
	stcp_socket_base *ss;
}SOCKET_QUEUE, *PSOCKET_QUEUE;
class queue_socket
{
	public:
		int socket_create(int cls);
		int socket_create(int cls, int usid);
		stcp_socket_base * queue_query_by_index(int index);
		stcp_socket_base * queue_query_by_addr();
		//stcp_socket_base * queue_query_by_usid(int usid);
		int socket_close(int index);
		int socket_dump();
		int socket_count() const;
		static queue_socket m_instance;

	private:
		SOCKET_QUEUE *m_psocket_queue;
		std::atomic<int> m_count;
		std::mutex m_mutex;

	public:
		queue_socket();
		~queue_socket();
};

#endif
