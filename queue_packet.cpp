#include "queue_packet.h"
queue_packet::queue_packet()
{
	m_queue_matrix = new PKTEXT[m_cache_size * m_cache_count];
}

queue_packet::~queue_packet()
{
	delete [] m_queue_matrix;
}

void queue_packet::free_queue(int sn, int count)
{
	assert (count <= m_use_count);
	assert (sn > m_freed_sn);
	if (sn > m_freed_sn || count > m_use_count)
		return;

	int matrix_sub = sn & m_matrix_mask;
	for (int i = 0; i < count; i++)
	{
		if (m_queue_matrix[matrix_sub].pkt_size != 0)
		{
			memset (
					&m_queue_matrix[matrix_sub],
					0,
					sizeof(m_queue_matrix[matrix_sub]));
		}
	}
	m_use_count -= count;
}

SPKTEXT * queue_packet::queue_alloc(unsigned int sn)
{
	int matrix_sub = sn & m_matrix_mask;
	if (m_queue_matrix[matrix_sub].pkt_size == 0)
		return nullptr;
	m_queue_matrix[matrix_sub].pkt_size = sizeof (SPKTEXT);
	m_queue_matrix[matrix_sub].data_offset = 0;
	m_queue_matrix[matrix_sub].data_size = 0;

	m_use_count++;
	return &m_queue_matrix[matrix_sub];
}

SPKTEXT * queue_packet::queue_get(unsigned int sn)
{
	int matrix_sub = sn & m_matrix_mask;
	if (m_queue_matrix[matrix_sub].pkt_size == 0)
		return nullptr;
	return &m_queue_matrix[matrix_sub];
}
