/**
 * file:    lib_mem.h
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#ifndef __LIB_MEM_H__
#define __LIB_MEM_H__


#include "os_type.h"


void *mem_set(void *buf, int val, unsigned int cnt);
void *mem_cpy(void *dst, const void *src, unsigned int cnt);
void *mem_move(void *dst, const void *src, unsigned int cnt);
int   mem_cmp(const void *buf1, const void *buf2, unsigned int cnt);



#endif /* __LIB_MEM_H__ */
