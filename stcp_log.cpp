#include "stcp_log.h"
stcp_log stcp_log::m_instance;
const char digits[] = "9876543210123456789";
const char * zero = digits + 9;
const char digitsHex[] = "0123456789ABCDEF";
//convert in to string

template <typename T>
size_t convert(char buf[], T value)
{
	T i = value;
	char *p = buf;
	do
	{
		int lsd = static_cast<int>(i % 10);
		i /= 10;
		*p++ = zero[lsd];
	}while(i!=0);
	if (value < 0)
	{
		*p++ = '0';
	}
	*p = '\0';
	std::reverse(buf, p);
	return p-buf;
}


size_t convertHex(char buf[], uintptr_t value)
{
	uintptr_t i = value;
	char *p = buf;
	do {
		int lsd = static_cast<int>(i%16);
		i /= 16;
		*p++ = digitsHex[lsd];

	}while(i!=0);
	*p ='\0';
	std::reverse(buf, p);
	return p-buf;
}

template<typename T>
void stcp_log::format_int(T v)
{
	m_mutex.lock();
	int now_size = m_pbuffer_cur->size();
	m_pbuffer_cur->resize(now_size+20);//need 20 blank save maxmum negetive number
	size_t len = convert(m_pbuffer_cur->data() + now_size, v);
	m_pbuffer_cur->resize(now_size + len );
	m_mutex.unlock();
}
stcp_log& stcp_log::operator<<(short v)
{
	*this<< static_cast<int>(v);
	return * this;
}
stcp_log& stcp_log::operator<<(unsigned short v)
{
	*this<< static_cast<int>(v);
	return * this;
}
stcp_log& stcp_log::operator<<(int v)
{
	format_int(v);
	return * this;
}
stcp_log& stcp_log::operator<<(unsigned int v )
{
	*this<< static_cast<int>(v);
	return * this;
}

stcp_log& stcp_log::operator<<(long v)
{
	*this<< static_cast<int>(v);
	return * this;
}
stcp_log& stcp_log::operator<<(unsigned long v)
{
	*this<< static_cast<int>(v);
	return * this;
}
stcp_log& stcp_log::operator<<(long long v)
{
	*this<< static_cast<int>(v);
	return * this;
}
stcp_log& stcp_log::operator<<(unsigned long long v)
{
	*this<< static_cast<int>(v);
	return * this;
}
stcp_log& stcp_log::operator<<(const void* p)
{
	m_mutex.lock();
	uintptr_t v = reinterpret_cast<uintptr_t> (p);
	char * buf = m_pbuffer_cur->data() + m_pbuffer_cur->size();
	buf [0] = '0';
	buf [1] = 'x';
	size_t len = convertHex(buf+2, v);
	m_pbuffer_cur->resize( m_pbuffer_cur->size() + len + 2);
	m_mutex.unlock();
	return * this;
}
stcp_log& stcp_log::operator<<(double v)
{
	*this<< static_cast<int>(v);
	return * this;
}

void stcp_log::flush()
{
	m_mutex.lock();
	LOG_BUF * flush_buf = m_pbuffer_cur;
	m_pbuffer_cur == &m_buffer_0 ?
			m_pbuffer_cur = &m_buffer_1:
			m_pbuffer_cur = &m_buffer_0;
	m_mutex.unlock();
	for (const auto i: *flush_buf)
		std::cout << i;
	flush_buf->resize(0);
	flush_buf->resize(1);
}
