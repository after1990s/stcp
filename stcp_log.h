#ifndef __STCP_LOG_H
#define __STCP_LOG_H
#include <mutex>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <pthread.h>
#include <sys/types.h>

#define LOG_INNER   __FILE__<<","<<__LINE__<<" tid:"<<pthread_self()<<" "
#define LOG_INFO    stcp_log::m_instance<<"INFO  "<<LOG_INNER
#define LOG_DEBUG   stcp_log::m_instance<<"DEBUG "<<LOG_INNER
#define LOG_FLUSH   stcp_log::m_instance.flush
class stcp_log
{
public:
	using LOG_BUF = std::vector<char>;
	using self = stcp_log;

	static stcp_log m_instance;
	void flush();

	self& operator<<(short);
	self& operator<<(unsigned short);
	self& operator<<(int);
	self& operator<<(unsigned int);
	self& operator<<(long);
	self& operator<<(unsigned long);
	self& operator<<(long long);
	self& operator<<(unsigned long long);
	self& operator<<(const void*);
	self& operator<<(double);

	self& operator<<(float v)
	{
		*this << static_cast<double>(v);
		return *this;
	}
	self& operator<<(char v)
	{
		m_mutex.lock();
		m_pbuffer_cur->insert(
				m_pbuffer_cur->end(),
				v);
		m_mutex.unlock();
		return *this;
	}
	self& operator<<(const char* str)
	{
		m_mutex.lock();
		m_pbuffer_cur->insert(
				m_pbuffer_cur->end(),
				str,
				str + strnlen(str, 1024)
		);
		m_mutex.unlock();
		return *this;
	}
	self& operator<<(const unsigned char* str)
	{
		return operator<<(reinterpret_cast<const char*>(str));
	}
	self& operator<<(std::string& v)
	{
		m_mutex.lock();
		m_pbuffer_cur->insert(
				m_pbuffer_cur->end(),
				v.begin(),
				v.end()
		);
		m_mutex.unlock();
		return *this;
	}

private:
	std::mutex m_mutex;
	LOG_BUF m_buffer_0;
	LOG_BUF m_buffer_1;
	LOG_BUF * m_pbuffer_cur;

	template<typename T>
	void format_int(T);


private:
	stcp_log(){
		m_pbuffer_cur = &m_buffer_0;
		m_buffer_0.resize(1);
		m_buffer_1.resize(1);};
	~stcp_log(){};
};
#endif
