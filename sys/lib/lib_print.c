/**
 * file:    lib_print.c
 * author:  wallying@foxmail.com
 * date:    2019-12-19
 **/


#include "lib/lib_print.h"


#define ZERO        (1 << 0)    /* pad with zero */
#define SIGN        (1 << 1)    /* unsigned/signed */
#define PLUS        (1 << 2)    /* show plus */
#define SPACE       (1 << 3)    /* space if plus */
#define LEFT        (1 << 4)    /* left justified */
#define UPPER       (1 << 5)    /* use 'ABCDEF' instead of 'abcdef' */


static char *print_num(char *buf, char *end, int val, unsigned int base, unsigned int flag)
{
    char *ptr = buf;
    char tmp[16];
    int neg = 0;
    int dig = 0;
    int i = 0;

    if ((flag & SIGN) && (val < 0)) {
        neg = 1;
        val = -val;
    }

    do {
        dig = val % base;
        tmp[i++] = ((dig < 10) ? dig + '0' : dig - 10 + ((flag & UPPER) ? 'A' : 'a'));
        val /= base;
    } while (val > 0);

    if (neg) {
        if (ptr < end) {
            *(ptr++) = '-';
        }
    }

    while (i--) {
        if (ptr < end) {
            *(ptr++) = tmp[i];
            continue;
        }
        break;
    }

    return ptr;
}


int print_vsnprintf(char *buf, unsigned int num, const char *fmt, va_list arg)
{
    char *ptr = buf;
    char *end = buf + num;
    const char *str;
    unsigned int flag = 0;

    for (; *fmt; ++fmt) {
        if (*fmt != '%') {
            if (ptr < end) {
                *(ptr++) = *fmt;
                continue;
            }
            break;
        }

        flag = 0;
        fmt++;
        switch (*fmt) {
        case 'c':
            if (ptr < end) {
                *(ptr++) = (char)(va_arg(arg, int));
            }
            break;
        case 's':
            str = va_arg(arg, char *);
            for (; *str != '\0'; ++str) {
                if (ptr < end) {
                    *(ptr++) = *str;
                    continue;
                }
                break;
            }
            break;
        case 'd': /* signed dec */
            flag |= SIGN;
        case 'u': /* unsigned dec */
            ptr = print_num(ptr, end, va_arg(arg, int), 10, flag);
            break;
        case 'X': /* unsigned upper hex */
            flag |= UPPER;
        case 'x': /* unsigned lower hex */
            ptr = print_num(ptr, end, va_arg(arg, int), 16, flag);
            break;
        default:
            if (ptr < end) {
                *(ptr++) = *fmt;
            }
            break;
        }
    }

    if (num > 0) {
        if (ptr < end) {
            *ptr = '\0';
        } else {
            *(--end) = '\0';
        }
    }

    return ptr - buf;
}


int print_sprintf(char *buf, const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    int len = print_vsnprintf(buf, ((unsigned int)(~0)), fmt, arg);
    va_end(arg);
    return len;
}


int print_snprintf(char *buf, unsigned int num, const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    int len = print_vsnprintf(buf, num, fmt, arg);
    va_end(arg);
    return len;
}

