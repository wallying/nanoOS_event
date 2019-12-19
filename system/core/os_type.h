/**
 * file:    os_type.h
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#ifndef __OS_TYPE_H__
#define __OS_TYPE_H__


#ifndef NULL
#define NULL ((void *)0)
#endif

typedef signed char os_s8;
typedef unsigned char os_u8;

typedef signed short os_s16;
typedef unsigned short os_u16;

#if 1
typedef signed int os_s32;
typedef unsigned int os_u32;
#else
typedef signed long os_s32;
typedef unsigned long os_u32;
#endif

typedef signed long long os_s64;
typedef unsigned long long os_u64;


#endif /* __OS_TYPE_H__ */

