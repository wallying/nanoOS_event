/**
 * file:    lib_mem.c
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#include "lib/lib_mem.h"


void *memset(void *buf, int val, unsigned int cnt)
{
    void *ptr = buf;
    while (cnt--) {
        *(char *)buf++ = (char)val;
    }
    return ptr;
}


void *memcpy(void *dst, const void *src, unsigned int cnt)
{
    void *ptr = dst;
    while (cnt--) {
        *(char *)dst++ = *(char *)src++;
    }
    return ptr;
}


void *memmove(void *dst, const void *src, unsigned int cnt)
{
    char *dp = dst;
    const char *sp = src;
    if (dst <= src) {
        while (cnt--) {
            *dp++ = *sp++;
        }
    } else {
        dp += cnt;
        sp = src;
        while (cnt--) {
            *--dp = *--sp;
        }
    }
    return dst;
}


int memcmp(const void *buf1, const void *buf2, unsigned int cnt)
{
    int ret = 0;
    while (cnt--) {
        if ((ret = *(char *)buf1++ - *(char *)buf2++) != 0) {
            break;
        }
    }
    return ret;
}


