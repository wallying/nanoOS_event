/**
 * file:    lib_str.h
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#ifndef __LIB_STR_H__
#define __LIB_STR_H__


#include "os_type.h"


typedef char* va_list;


#define _INTSIZEOF(n)   ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

#define va_start(ap,v)  (ap = (va_list)&v + _INTSIZEOF(v))

#define va_arg(ap,type) (*(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)))

#define va_end(ap)      (ap = (va_list)0)



char *str_cpy(char *dst, const char *src);
char *str_ncpy(char *dst, const char *src, unsigned int cnt);

char *str_cat(char *dst, const char *src);
char *strncat(char *dst, const char *src, unsigned int cnt);

int str_cmp(const char *str1, const char *str2);
int str_ncmp(const char *str1, const char *str2, unsigned int cnt);

unsigned int str_len(const char *str);
unsigned int str_nlen(const char *str, unsigned int cnt);

char *str_chr(const char *str, int c);
char *str_nchr(const char *str, unsigned int cnt, int c);


int vsnprintf(char *buf, unsigned int cnt, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);
int snprintf(char *buf, unsigned int cnt, const char *fmt, ...);



#endif /* __LIB_STR_H__ */
