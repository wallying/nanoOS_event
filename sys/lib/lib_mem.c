/**
 * file:    lib_mem.c
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#include "lib/lib_mem.h"


void *mem_set(void *buf, int val, unsigned int num)
{
    void *ptr = buf;
    while (num--) {
        *(char *)buf++ = (char)val;
    }
    return ptr;
}


void *mem_cpy(void *dst, const void *src, unsigned int num)
{
    void *ptr = dst;
    while (num--) {
        *(char *)dst++ = *(char *)src++;
    }
    return ptr;
}


void *mem_move(void *dst, const void *src, unsigned int num)
{
    char *dp = dst;
    const char *sp = src;
    if (dst <= src) {
        while (num--) {
            *dp++ = *sp++;
        }
    } else {
        dp += num;
        sp = src;
        while (num--) {
            *--dp = *--sp;
        }
    }
    return dst;
}


int mem_cmp(const void *buf1, const void *buf2, unsigned int num)
{
    int ret = 0;
    while (num--) {
        if ((ret = *(char *)buf1++ - * (char *)buf2++) != 0) {
            break;
        }
    }
    return ret;
}


