#include "stcp_startup.h"
//stcp_startup stcp_startup::m_instance;
//kstd::mutex stcp_startup::m_mutex;
stcp_startup::stcp_startup()
{
}
stcp_startup::~stcp_startup()
{

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
