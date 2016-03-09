#include "stcp_socket_listen.h"
stcp_socket_listen::stcp_socket_listen(int cls)\
		: stcp_socket_base(AF_INET, SOCK_STREAM, IPPROTO_UDP, cls)
{

}

int stcp_socket_listen::bind(const struct sockaddr * addr, int addrlen) 
{
	int ret = ::bind(m_socket, addr, addrlen);
	if (ret == 0)
	{
		memcpy (&m_bind_addr, addr, addrlen);
	}
	return ret;
}
int stcp_socket_listen::listen(int backlog)
{
	return ::listen(m_socket, backlog);
}
int stcp_socket_listen::accept(struct sockaddr * addr, int addrlen) 
{

	//receive a connect packet;

	return ERROR_NOT_SUPPORT;
}
int stcp_socket_listen::connect(struct sockaddr *addr, int addrlen) 
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_listen::recv(void *buf, int size, int flag)
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_listen::send(const void *buf, int size, int flag)
{
	return ERROR_NOT_SUPPORT;
}
int stcp_socket_listen::on_recv() 
{
	stcp_socket_base::on_recv();
	SPKTEXT * pkt_ext = m_queue_packet_recv.queue_alloc(0);
	SPKT * pkt = &(pkt_ext->pkt);
	struct sockaddr_in src_addr = {0};
	int src_addr_len = sizeof(src_addr);
	while (true)
	{
		memset (&src_addr, 0, sizeof(src_addr));
		memset (pkt, 0, sizeof(SPKT));
		int recv_num = ::recvfrom(m_socket, pkt, sizeof(SPKT), 0,
				(struct sockaddr*)&src_addr,
				(socklen_t*)&src_addr_len);
		if (recv_num <= 0)
		{
			break;
		}
		if (pkt->hdr.ucmd == STCP_CMD_CONNECT)
		{
			int accepted = queue_socket::m_instance.socket_create(
					stcp_class_enum::STCP_SOCKET_ACCEPT, 
					pkt->hdr.usid);
			m_accepted_stk.push(accepted);
			connect_accepted_notify(accepted);
			continue;
		}
		else // (pkt->hdr.ucmd != STCP_CMD_CONNECT)
		{
			stcp_socket_accept * socket_connected= 
				reinterpret_cast<stcp_socket_accept*>(
					queue_socket::m_instance.queue_query_by_index(
					pkt->hdr.usid
					));
	//		assert (socket_connected->get_socket_class() 
	//				== stcp_class_enum::
			if (socket_connected != nullptr)
			{
				socket_connected->on_recv(pkt);
			}
			else
			{
				sendback_reset((struct sockaddr*)&src_addr);
			}
		}
	}
}

void stcp_socket_listen::connect_accepted_notify(int accepteid)
{
	//回送发送成功，这个包无需确认，不需要从packetqueue中申请。
	SPKT pkt = {0};
	pkt.hdr.ucmd = STCP_CMD_CONNECT_ACK;
	pkt.hdr.usid = accepteid;
	stcp_socket_accept *acpt = reinterpret_cast<stcp_socket_accept*>(
			queue_socket::m_instance.queue_query_index(accepteid));
	acpt->close();
}
int stcp_socket_listen::on_timer() 
{
	stcp_socket_base::on_timer();
	return 0;
}

