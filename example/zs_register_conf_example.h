#ifndef __ZS_REGISTER_CONF_H__
#define __ZS_REGISTER_CONF_H__


#define ZS_REGISTER_MEM_CUSTOM 0
#if ZS_REGISTER_MEM_CUSTOM==0
    #define ZS_REGISTER_MEM_INCLUDE "stdlib.h"
    #define ZS_REGISTER_MEM_ALLOC   malloc
    #define ZS_REGISTER_MEM_FREE    free
#else
    #define ZS_REGISTER_MEM_INCLUDE "zs_mem.h"
    #define ZS_REGISTER_MEM_ALLOC   zs_mem_alloc
    #define ZS_REGISTER_MEM_ALLOC   zs_mem_free
#endif


#endif /* __ZS_REGISTER_CONF_H__ */
