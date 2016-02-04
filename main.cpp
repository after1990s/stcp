#include "stcp_cache.h"
#include <thread>
void thread_function(void)
{
    stcp_cache cache;
    for (int i=0; i< 20; i++)
    {
        cache.alloc(i);
    }
    for (int i=0; i< 20; i++)
    {
        cache.free(i,1);
    }
}
int main(void)
{

    std::thread t(thread_function);
    t.join();
    return 0;
}
