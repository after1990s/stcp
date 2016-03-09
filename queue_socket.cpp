#include "queue_socket.h"
queue_socket queue_socket::m_instance;
queue_socket::queue_socket()
{
	m_count = 0;
	int size = sizeof(SOCKET_QUEUE) * MAXSIZE_SOCKET;
	m_psocket_queue = (SOCKET_QUEUE*)malloc(size);
	bzero(m_psocket_queue, size);
}
queue_socket::~queue_socket()
{
	free(m_psocket_queue);
}

int queue_socket::socket_create(int cls)
{
	switch(cls)
	{
		case stcp_class_enum::STCP_SOCKET_ACCEPT:
			m_psocket_queue[m_count].ss = reinterpret_cast<stcp_socket_base*>(new stcp_socket_accept(cls));
			break;
		case stcp_class_enum::STCP_SOCKET_CONNECT:
			m_psocket_queue[m_count].ss = reinterpret_cast<stcp_socket_base*>(new stcp_socket_connect(cls));
			break;;
		case stcp_class_enum::STCP_SOCKET_LISTEN:
			m_psocket_queue[m_count].ss = reinterpret_cast<stcp_socket_base*>(new stcp_socket_listen(cls));
			break;
		default:
			assert(false);
			return -1;
	}
	m_psocket_queue[m_count].status = stcp_socket_status::STCP_STATUS_NULL;
	m_count++;
	return m_count - 1; 
}

int queue_socket::socket_create(int cls, int usid)
{
	switch(cls)
	{
		case stcp_class_enum::STCP_SOCKET_ACCEPT:
			m_psocket_queue[m_count].ss = reinterpret_cast<stcp_socket_base*>(new stcp_socket_accept(cls));
			break;
		case stcp_class_enum::STCP_SOCKET_CONNECT:
			m_psocket_queue[m_count].ss = reinterpret_cast<stcp_socket_base*>(new stcp_socket_connect(cls));
			break;;
		case stcp_class_enum::STCP_SOCKET_LISTEN:
			m_psocket_queue[m_count].ss = reinterpret_cast<stcp_socket_base*>(new stcp_socket_listen(cls));
			break;
		default:
			assert(false);
			return -1;
	}
	m_psocket_queue[m_count].ss->set_usid(usid);
	m_psocket_queue[m_count].status = stcp_socket_status::STCP_STATUS_NULL;
	m_count++;
	
	return m_count-1;
}
stcp_socket_base * queue_socket::queue_query_by_index(int index)
{
	if (m_count <= index)
	{
		assert(false);
		return nullptr;
	}
	return m_psocket_queue[index].ss;

}

int queue_socket::socket_close(int index)
{
	m_mutex.lock();
	if (m_psocket_queue[m_count].status != stcp_socket_status::STCP_STATUS_CLOSED)
	{
		m_psocket_queue[m_count].ss->close_socket_force();
		m_psocket_queue[m_count].status =  stcp_socket_status::STCP_STATUS_CLOSED;
	}
	delete m_psocket_queue[m_count].ss;
	memset(&m_psocket_queue[m_count], 0, sizeof(m_psocket_queue[m_count]));
	m_mutex.unlock();
	return ERROR_SUCCESS;

}

int queue_socket::socket_count() const
{
	return m_count;
}
