#include "queue_socket.h"
queue_socket* queue_socket::m_queue_socket_instance = nullptr;
std::mutex queue_socket::m_mutex;
SOCKET_QUEUE* queue_socket::m_socket_queue = nullptr;

queue_socket::queue_socket()
{
	int size = sizeof(SOCKET_QUEUE) * MAXSIZE_SOCKET;
	m_socket_queue = (SOCKET_QUEUE*)malloc(size);
	bzero(m_socket_queue, size);
}
queue_socket::~queue_socket()
{
	free(m_socket_queue);
}
queue_socket * queue_socket::get_instance()
{
	if (m_queue_socket_instance==nullptr)
	{
		m_mutex.lock();
		m_queue_socket_instance = new queue_socket();
		m_mutex.unlock();
	}
	return m_queue_socket_instance;
}
void queue_socket::destory_instance()
{
	if (m_queue_socket_instance==nullptr)
		return;
	m_mutex.lock();
	delete m_queue_socket_instance;
	m_mutex.unlock();
}

int queue_create()
{

}
