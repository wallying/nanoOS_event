/**
 * file:    string.c
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#include "string.h"


void *lib_memset(void *buf, int val, unsigned int cnt)
{
    void *ptr = buf;
    while (cnt--) {
        *(char *)buf++ = (char)val;
    }
    return ptr;
}


void *lib_memcpy(void *dst, const void *src, unsigned int cnt)
{
    void *ptr = dst;
    while (cnt--) {
        *(char *)dst++ = *(char *)src++;
    }
    return ptr;
}


void *lib_memmove(void *dst, const void *src, unsigned int cnt)
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


int lib_memcmp(const void *buf1, const void *buf2, unsigned int cnt)
{
    int ret = 0;
    while (cnt--) {
        if ((ret = *(char *)buf1++ - *(char *)buf2++) != 0) {
            break;
        }
    }
    return ret;
}


/*----------------------------------------------------------------------------*/
char *lib_strcpy(char *dst, const char *src)
{
    char *ptr = dst;
    while ((*dst++ = *src++) != '\0');
    return ptr;
}


char *lib_strncpy(char *dst, const char *src, unsigned int cnt)
{
    char *ptr = dst;
    while (cnt--) {
        if ((*dst++ = *src) != '\0') {
            ++src;
        }
    }
    return ptr;
}


char *lib_strcat(char *dst, const char *src)
{
    char *ptr = dst;
    while (*dst++);
    while ((*dst++ = *src++) != '\0');
    return ptr;
}


char *lib_strncat(char *dst, const char *src, unsigned int cnt)
{
    char *ptr = dst;
    if (cnt) {
        while (*dst++);
        while ((*dst++ = *src++) != '\0' && !--cnt) {
            *dst = '\0';
            break;
        }
    }
    return ptr;
}


int lib_strcmp(const char *str1, const char *str2)
{
    int ret = 0;
    while (1) {
        if ((ret = *str1 - *str2++) != 0 || !*str1++) {
            break;
        }
    }
    return ret;
}


int lib_strncmp(const char *str1, const char *str2, unsigned int cnt)
{
    int ret = 0;
    while (cnt--) {
        if ((ret = *str1 - *str2++) != 0 || !*str1++) {
            break;
        }
    }
    return ret;
}


unsigned int lib_strlen(const char *str)
{
    const char *ptr = str;
    for (; *ptr != '\0'; ++ptr);
    return ptr - str;
}


unsigned int lib_strnlen(const char *str, unsigned int cnt)
{
    const char *ptr = str;
    for (; cnt-- && *ptr != '\0'; ++ptr);
    return ptr - str;
}


char *lib_strchr(const char *str, int c)
{
	for (; *str != (char)c; ++str) {
		if (*str == '\0') {
			return NULL;
		}
	}
	return (char *)str;
}


char *lib_strnchr(const char *str, unsigned int cnt, int c)
{
	while (cnt--) {
		if (*str == (char)c)
			return (char *)str;
		if (*str++ == '\0')
			break;
	}
	return NULL;
}


/*----------------------------------------------------------------------------*/
int lib_vsnprintf(char *buf, unsigned int cnt, const char *fmt, va_list args)
{
    return 0;
}


int lib_sprintf(char *buf, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = lib_vsnprintf(buf, ((unsigned int)(~0)), fmt, args);
    va_end(args);
    return len;
}


int lib_snprintf(char *buf, unsigned int cnt, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = lib_vsnprintf(buf, cnt, fmt, args);
    va_end(args);
    return len;
}

