/**
 * file:    lib_str.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#ifndef __LIB_STR_H__
#define __LIB_STR_H__


#include "os_type.h"


char *str_cpy(char *dst, const char *src);
char *str_ncpy(char *dst, const char *src, unsigned int cnt);

char *str_cat(char *dst, const char *src);
char *str_ncat(char *dst, const char *src, unsigned int cnt);

int str_cmp(const char *str1, const char *str2);
int str_ncmp(const char *str1, const char *str2, unsigned int cnt);

unsigned int str_len(const char *str);
unsigned int str_nlen(const char *str, unsigned int cnt);

char *str_chr(const char *str, int c);
char *str_nchr(const char *str, unsigned int cnt, int c);


#endif /* __LIB_STR_H__ */

