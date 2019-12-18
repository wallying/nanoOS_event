/**
 * file:    lib_print.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#ifndef __LIB_PRINT_H__
#define __LIB_PRINT_H__


#include "os_type.h"


typedef char* va_list;


#define _INTSIZEOF(n)   ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

#define va_start(ap,v)  (ap = (va_list)&v + _INTSIZEOF(v))

#define va_arg(ap,type) (*(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)))

#define va_end(ap)      (ap = (va_list)0)


int vsnprintf(char *buf, unsigned int num, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);
int snprintf(char *buf, unsigned int num, const char *fmt, ...);


#endif /* __LIB_PRINT_H__ */

