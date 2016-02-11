#ifndef _STCP_STARTUP__
#define _STCP_STARTUP__
#include <sys/socket.h>
#include <mutex>
#include "stcp_errno.h"
#include "stcp_log.h"
#include "queue_socket.h"
#include "stcp.h"

class stcp_startup{
    public:
		stcp_socket_base * get_socket(int index);
		//返回socket序号
		int make_socket(stcp_class_enum cls);
		//
		int remove_socket(int index);

		stcp_startup();
		~stcp_startup();
	public:
		//编译器保证单例的线程安全
		static stcp_startup m_instance;
		
	private:
		static std::mutex m_mutex;
		queue_socket m_socket_queue;
    
};
#endif
