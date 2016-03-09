#include "stcp_startup.h"
//stcp_startup stcp_startup::m_instance;
//kstd::mutex stcp_startup::m_mutex;
stcp_startup::stcp_startup()
{
	m_epoll = epoll_create(1);
	for (int i = 0; i < 3; i++)
	{
		std::thread t(worker_thread);
		t.detach();
	}
	std::thread t0(timer_thread);
	t0.detach();
}
stcp_startup::~stcp_startup()
{
	close(m_epoll);
}
/*stcp_startup::get_instance()
{
}
*/
stcp_socket_base* stcp_startup::get_socket(int index)
{
	stcp_socket_base *so = m_socket_queue.queue_query_index(index);
	if (so==NULL)
	{
		assert(false);
		stcp_log("stcp_startup::get_socket");
	}
	return so;
}
int stcp_startup::make_socket(stcp_class_enum cls)
{
	return m_socket_queue.queue_create(cls);
}
void stcp_startup::timer_thread()
{
	stcp_block_signals();
	struct timespec t_interval = {0};
	t_interval.tv_nsec = 15 * 10000000;
	while (true)
	{
		nanosleep(&t_interval, NULL);
		int count = m_instance.m_socket_queue.socket_count();
		for (int i = 0; i < count; i++)
		{
		stcp_socket_base * s_socket_base = 
			m_instance.m_socket_queue.queue_query_index(i);
		switch (s_socket_base->get_socket_class())
		{
			case stcp_class_enum::STCP_SOCKET_ACCEPT:
				reinterpret_cast<stcp_socket_accept*>(s_socket_base)->on_timer();
				break;
			case stcp_class_enum::STCP_SOCKET_CONNECT:
				reinterpret_cast<stcp_socket_connect*>(s_socket_base)->on_timer();
				break;
			case stcp_class_enum::STCP_SOCKET_LISTEN:
				reinterpret_cast<stcp_socket_listen*>(s_socket_base)->on_timer();
				break;
			default:
				assert(false);
		}
		}
	}
}
void stcp_startup::worker_thread()
{
	stcp_block_signals();
	struct epoll_event ep_evt = {0};
	for ( ; ; )
	{
		memset(&ep_evt, 0, sizeof(ep_evt));
		
		int rtn = epoll_wait(m_instance.m_epoll, &ep_evt, 100, -1);
		if (rtn == -1)
		{
			stcp_log("epoll_wait failed:");
			stcp_log(strerror(errno));
			continue;
		}
		stcp_socket_base * s_socket_base = 
			reinterpret_cast<stcp_socket_base*>(ep_evt.data.ptr);
		switch (s_socket_base->get_socket_class())
		{
			case stcp_class_enum::STCP_SOCKET_ACCEPT:
				reinterpret_cast<stcp_socket_accept*>(s_socket_base)->on_recv();
				break;
			case stcp_class_enum::STCP_SOCKET_CONNECT:
				reinterpret_cast<stcp_socket_connect*>(s_socket_base)->on_recv();
				break;
			case stcp_class_enum::STCP_SOCKET_LISTEN:
				reinterpret_cast<stcp_socket_listen*>(s_socket_base)->on_recv();
				break;
		}
	}

}
void stcp_block_signals()
{
	sigset_t old = {0};
	sigset_t now = {0};
	sigfillset(&now);
	int rtn = sigprocmask(SIG_BLOCK, &now, &old);
	if (rtn !=0)
	{
		stcp_log("sigprocmask failed:");
		stcp_log(strerror(errno))
	}
}
