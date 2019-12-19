/**
 * file:    lib_ascii.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#ifndef __LIB_ASCII_H__
#define __LIB_ASCII_H__


#include "os_type.h"



#define ascii_isdigit(c) \
        (((c) >= '0') && ((c) <= '9'))

#define ascii_isodigit(c) \
        (((c) >= '0') && ((c) <= '7'))

#define ascii_isxdigit(c) \
        (((c) >= '0') && ((c) <= '9')) || \
        ((c) >= 'A') && ((c) <= 'F')) || \
        ((c) >= 'a') && ((c) <= 'f')))


#define ascii_islower(c) \
        (((c) >= 'a') && ((c) <= 'z'))

#define ascii_isupper(c) \
        (((c) >= 'A') && ((c) <= 'Z'))

#define ascii_isalpha(c) \
        (ascii_islower(c) || ascii_isupper(c))

#define ascii_isalnum(c) \
        (ascii_isalpha(c) || ascii_isdigit(c))


#define ascii_isspace(c) \
        (((c) == ' ') || ((c) == '\r') || \
        ((c) == '\n' ) || ((c) == '\f') || \
        ((c) == '\t') || ((c) == '\v'))

#define ascii_isprint(c) \
        (((c) >= ' ') && ((c) <= '~'))


#define ascii_tolower(c) \
        (ascii_isupper(c)?((c)+('a'-'A')):(c))

#define ascii_toupper(c) \
        (ascii_islower(c)?((c)-('a'-'A')):(c))


#endif /* __LIB_ASCII_H__ */

