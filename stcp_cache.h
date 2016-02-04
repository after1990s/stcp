/*
stcp_cache保存发送的包，当所有的包都已经被对端确认，就可以丢弃包。
如果某个包未被确认则需要重新发送。
*/
#ifndef __STCP_CACHE_H
#define __STCP_CACHE_H
#include "stcp.h"
#define STCP_CACHE_MAXSIZE 0X80
#define STCP_CACHE_MASK (0X80 - 1)
class stcp_cache{
    public:
        stcp_cache();
        ~stcp_cache();

       SPKTEXT *alloc(int serial);
       int free(int serial, int size);
    private:
       SPKTEXT cache_pool[STCP_CACHE_MAXSIZE];
       int cache_size;

};
#endif
