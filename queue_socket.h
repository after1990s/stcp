/*
这个类用于分配，保存，查询所有的stcp_socket实例。
提供几种查询方式：
1.按照index
2.按照remoteaddr
*/
#ifndef __QUEUE_SOCKET_H
#define __QUEUE_SOCKET_H
#include "stcp_socket.h"
#include "stcp.h"
#include <mutex>
#include <cstdlib>

#define MAXSIZE_SOCKET (1024)
typedef struct _s_queue_socket
{
	stcp_socket_status status;
	stcp_socket *ss;
}SOCKET_QUEUE, *PSOCKET_QUEUE;
class queue_socket
{
	public:
		int queue_create();
		int queue_query_index(int index);
		int queue_query_by_addr();
		int queue_close();
		int queue_dump();
		int queue_count();

	private:
		queue_socket();
		~queue_socket();
		queue_socket* get_instance();
		void destory_instance();

	private:
		static queue_socket* m_queue_socket_instance;
		static std::mutex m_mutex;
		static SOCKET_QUEUE *m_socket_queue;
};

#endif
