/*
  queue_packet用于快速的获得和释放一段内存。
  sn是发送的数据标号。
  每个cache是1024字节。使用时向上取整。
  该类不是线程安全的。
*/

#ifndef QUEUE_PACKET_H
#define QUEUE_PACKET_H
#include "stcp_errno.h"
#include "stcp.h"

class queue_packet{
	public:
		queue_packet();
		~queue_packet();
		
		SPKTEXT * queue_alloc(unsigned int sn);
		SPKTEXT * queue_get(unsigned int sn);

		void free_queue(int sn, int count);
		//unsigned char* alloc_queue(int sn, int count);

	private:
		unsigned int m_use_count;//目前使用中的数量
		unsigned int m_freed_sn;//已经使用了的sn
		SPKTEXT * m_queue_matrix;
		unsigned int m_cache_size=1024;
		unsigned int m_cache_count=0x80;//多少个cache可用
		unsigned int m_matrix_mask=0x80;
};

#endif
