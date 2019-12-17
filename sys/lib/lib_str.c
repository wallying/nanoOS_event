/**
 * file:    lib_str.c
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#include "lib/lib_str.h"


char *str_cpy(char *dst, const char *src)
{
    char *ptr = dst;
    while ((*dst++ = *src++) != '\0');
    return ptr;
}


char *str_ncpy(char *dst, const char *src, unsigned int cnt)
{
    char *ptr = dst;
    while (cnt--) {
        if ((*dst++ = *src) != '\0') {
            ++src;
        }
    }
    return ptr;
}


char *str_cat(char *dst, const char *src)
{
    char *ptr = dst;
    while (*dst++);
    while ((*dst++ = *src++) != '\0');
    return ptr;
}


char *strncat(char *dst, const char *src, unsigned int cnt)
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


int str_cmp(const char *str1, const char *str2)
{
    int ret = 0;
    while (1) {
        if ((ret = *str1 - *str2++) != 0 || !*str1++) {
            break;
        }
    }
    return ret;
}


int str_ncmp(const char *str1, const char *str2, unsigned int cnt)
{
    int ret = 0;
    while (cnt--) {
        if ((ret = *str1 - *str2++) != 0 || !*str1++) {
            break;
        }
    }
    return ret;
}


unsigned int str_len(const char *str)
{
    const char *ptr = str;
    for (; *ptr != '\0'; ++ptr);
    return ptr - str;
}


unsigned int str_nlen(const char *str, unsigned int cnt)
{
    const char *ptr = str;
    for (; cnt-- && *ptr != '\0'; ++ptr);
    return ptr - str;
}


char *str_chr(const char *str, int c)
{
	for (; *str != (char)c; ++str) {
		if (*str == '\0') {
			return NULL;
		}
	}
	return (char *)str;
}


char *str_nchr(const char *str, unsigned int cnt, int c)
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
int vsnprintf(char *buf, unsigned int cnt, const char *fmt, va_list args)
{
    return 0;
}


int sprintf(char *buf, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buf, ((unsigned int)(~0)), fmt, args);
    va_end(args);
    return len;
}


int snprintf(char *buf, unsigned int cnt, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buf, cnt, fmt, args);
    va_end(args);
    return len;
}

