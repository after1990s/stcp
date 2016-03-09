#ifndef __STCP_SOCKET_H
#define __STCP_SOCKET_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <assert.h>
#include "stcp.h"
#include "stcp_errno.h"
#include "queue_packet.h"
class stcp_socket_base
{
    public:
        stcp_socket_base(int sock_type, int sock_stream, int sock_proto, int cls);
        stcp_socket_base(int sock_type, 
						 int sock_stream,
						 int sock_proto,
						 int cls,
						 int usid);
        virtual ~stcp_socket_base();

	public://apis.
		virtual int bind(const struct sockaddr * addr, int addrlen);
		virtual int listen(int backlog);
		virtual int accept(struct sockaddr * addr, int addrlen);
		virtual int connect(struct sockaddr *addr, int addrlen);
		virtual int recv(void *buf, int size, int flag);
		virtual int send(const void * buf, int size, int flag);
		virtual int close();

		int close_socket_force();
		int close_socket();

	public:
		virtual int on_recv();
		virtual int on_send();
		virtual int on_timer();

		//uid is send from remote.
		//record it to confirm if it correct client.
		void set_usid(int usid)
		{
			m_usid = usid;
		}
		int get_usid() const
		{
			return m_usid;
		}
	public:
		void set_socket_class(int cls);
		int  get_socket_class() const;

	private:
		int m_index;//socket在pool中的index
		int m_class;//socket 类型
		int m_epoll;
		int m_usid;
	protected:
		int m_socket;//udp的socket
		queue_packet m_queue_packet_recv;
		queue_packet m_queue_packet_send;

};
#endif
