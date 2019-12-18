/**
 * file:    lib_print.c
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#include "lib/lib_print.h"


int vsnprintf(char *buf, unsigned int num, const char *fmt, va_list args)
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


int snprintf(char *buf, unsigned int num, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buf, num, fmt, args);
    va_end(args);
    return len;
}

