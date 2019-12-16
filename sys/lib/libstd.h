/**
 * file:    libstd.h
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#ifndef __LIBSTD_H__
#define __LIBSTD_H__


#include "libtype.h"


typedef char* va_list;


#define _INTSIZEOF(n)   ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

#define va_start(ap,v)  (ap = (va_list)&v + _INTSIZEOF(v))

#define va_arg(ap,type) (*(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)))

#define va_end(ap)      (ap = (va_list)0)



void *lib_memset(void *buf, int val, unsigned int cnt);
void *lib_memcpy(void *dst, const void *src, unsigned int cnt);
void *lib_memmove(void *dst, const void *src, unsigned int cnt);
int   lib_memcmp(const void *buf1, const void *buf2, unsigned int cnt);


char *lib_strcpy(char *dst, const char *src);
char *lib_strncpy(char *dst, const char *src, unsigned int cnt);

char *lib_strcat(char *dst, const char *src);
char *lib_strncat(char *dst, const char *src, unsigned int cnt);

int lib_strcmp(const char *str1, const char *str2);
int lib_strncmp(const char *str1, const char *str2, unsigned int cnt);

unsigned int lib_strlen(const char *str);
unsigned int lib_strnlen(const char *str, unsigned int cnt);

char *lib_strchr(const char *str, int c);
char *lib_strnchr(const char *str, unsigned int cnt, int c);


int lib_vsnprintf(char *buf, unsigned int cnt, const char *fmt, va_list args);
int lib_sprintf(char *buf, const char *fmt, ...);
int lib_snprintf(char *buf, unsigned int cnt, const char *fmt, ...);



#endif /* __LIBSTD_H__ */
