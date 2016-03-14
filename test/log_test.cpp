#include "../stcp_log.h"
#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
void t0()
{
	struct timespec wtime = {0};
	wtime.tv_nsec = 1200000;
	int i = 0;
	while (true)
	{
		i++;
		LOG_INFO << i << "world" << "hello\n" ;
		nanosleep(&wtime, NULL);
	}
}
int main(void)
{
	std::thread _t(t0);
	_t.detach();
	std::thread _t1(t0);
	_t1.detach();
	struct timespec wtime = {0};
	wtime.tv_sec = 7;
	while(true)
	{
		LOG_FLUSH();
	nanosleep(&wtime, NULL);
	}
	return 0;
}
