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
		memcpy ((void*)&m_bind_addr, (void*)addr, addrlen);
	}

	return ret;
}
int stcp_socket_listen::listen(int backlog)
{
	return ERROR_SUCCESS;//::listen(m_socket, backlog);
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
	unsigned int src_addr_len = sizeof(pkt_ext->remote_addr);
	while (true)
	{
		memset (pkt, 0, sizeof(SPKT));
		int recv_num = ::recvfrom(m_socket, pkt, sizeof(SPKT), 0,
				(struct sockaddr*)&pkt_ext->remote_addr,
				&src_addr_len);
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
			stcp_socket_accept * socket_accepted=
				reinterpret_cast<stcp_socket_accept*>(
					queue_socket::m_instance.queue_query_by_index(
					pkt->hdr.usid
					));
	//		assert (socket_connected->get_socket_class() 
	//				== stcp_class_enum::
			if (socket_accepted != nullptr)
			{
				socket_accepted->notify_recv(pkt_ext);
			}
			else
			{
				sendback_reset((struct sockaddr*)&pkt_ext->remote_addr);
			}
		}
	}
}

void stcp_socket_listen::connect_accepted_notify(int accepteid)
{
	//回送发送成功，这个包无需确认，不需要从packetqueue中申请。
	SPKTEXT pkt = {0};

	pkt.pkt.hdr.ucmd = STCP_CMD_CONNECT_ACK;
	pkt.pkt.hdr.usid = accepteid;
	stcp_socket_accept *acpt = reinterpret_cast<stcp_socket_accept*>(
			queue_socket::m_instance.queue_query_by_index(accepteid));
	acpt->on_send(&pkt);
}
int stcp_socket_listen::on_timer() 
{
	stcp_socket_base::on_timer();
	return 0;
}

void stcp_socket_listen::sendback_reset(struct sockaddr * src_addr)
{
	SPKT pkt = {0};
	pkt.hdr.ucmd = STCP_CMD_RESET;
	pkt.hdr.usid = 0;
	::sendto(m_socket, &pkt, sizeof(SPKT), 0, src_addr, sizeof(struct sockaddr));
}
