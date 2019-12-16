/**
 * file:    lib_mem.h
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#ifndef __LIB_MEM_H__
#define __LIB_MEM_H__


#include "os_type.h"


void *memset(void *buf, int val, unsigned int cnt);
void *memcpy(void *dst, const void *src, unsigned int cnt);
void *memmove(void *dst, const void *src, unsigned int cnt);
int   memcmp(const void *buf1, const void *buf2, unsigned int cnt);



#endif /* __LIB_MEM_H__ */
