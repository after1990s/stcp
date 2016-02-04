#include "stcp_cache.h"

stcp_cache::stcp_cache()
{
    cache_size = 0;
}
stcp_cache::~stcp_cache()
{
}

SPKTEXT * stcp_cache::alloc(int serial)
{
    assert(serial > 0);
    //检查(serial & mask)对应的包是否为空
    int cache_index = serial & STCP_CACHE_MASK;
    if (cache_pool[cache_index].pkt_size != 0)
    {
        //不是，返回错误
        return nullptr;
    }
    //是，增加size，返回成功
    cache_size ++;
    return &cache_pool[cache_index];
}
int stcp_cache::free (int serial, int size)
{
    //assert size >= 0
    assert(size > 0);
    //assert size < cache_size
    assert(size <= cache_size);
    
    for (int i=0; i < size; i++)
    {
        int cache_index = (serial + i) & STCP_CACHE_MASK;
    //检查serial + i & mask 是否为空
        if (cache_pool[cache_index].pkt_size == 0)
            continue;
    //memset (serial+i &mask)
        memset (&cache_pool[cache_index], 0, sizeof (cache_pool[cache_index]));
    //cache_size --;
        cache_size--;
    }
    return ERROR_SUCCESS;
    
}


