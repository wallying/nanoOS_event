/**
 * file:    os_def.h
 * author:  wallying@foxmail.com
 * date:    2019-12-18
 **/


#ifndef __OS_DEF_H__
#define __OS_DEF_H__


#include "os_type.h"


#ifndef BIT
#define BIT(n)          (0x01 << (n))
#endif

#ifndef ABS
#define ABS(x)          (((x) > 0) ? (x) : (-(x)))
#endif

#ifndef MIN
#define MIN(x, y)       (((x) < (y)) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x, y)       (((x) > (y)) ? (x) : (y))
#endif



#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)   (sizeof(a) / sizeof((a)[0]))
#endif


#ifndef ALIGN
#define ALIGN(x, a)  	(((x) + ((a) - 1)) & ~((a) - 1))
#endif

#ifndef LO_U8
#define LO_U8(x)		((os_u8)(((x) >> 0) & 0x0F))
#endif
#ifndef HI_U8
#define HI_U8(x)   		((os_u8)(((x) >> 4) & 0x0F))
#endif
#ifndef MAKE_U8
#define MAKE_U8(loByte, hiByte) \
                    ((os_u8)((((os_u8)(loByte) & 0x0F) << 0) + \
                             (((os_u8)(hiByte) & 0x0F) << 4)))
#endif


#ifndef LO_U16
#define LO_U16(x)        ((os_u8)(((x) >> 0) & 0xFF))
#endif
#ifndef HI_U16
#define HI_U16(x)        ((os_u8)(((x) >> 8) & 0xFF))
#endif
#ifndef MAKE_U16
#define MAKE_U16(l, h) \
                    ((uint16)((((os_u16)(l) & 0xFF) << 0) + \
                              (((os_u16)(h) & 0xFF) << 8)))
#endif


#ifndef B0_U32
#define B0_U32(x)     ((os_u8)(((x) >>  0) & 0xFF))
#endif
#ifndef B1_U32
#define B1_U32(x)     ((os_u8)(((x) >>  8) & 0xFF))
#endif
#ifndef B2_U32
#define B2_U32(x)     ((os_u8)(((x) >> 16) & 0xFF))
#endif
#ifndef B3_U32
#define B3_U32(x)     ((os_u8)(((x) >> 24) & 0xFF))
#endif
#ifndef MAKE_U32
#define MAKE_U32(a, b, c, d) \
                    ((os_u32)((((os_u32)(a) & 0xFF) <<  0) + \
                              (((os_u32)(b) & 0xFF) <<  8) + \
                              (((os_u32)(c) & 0xFF) << 16) + \
                              (((os_u32)(d) & 0xFF) << 24)))
#endif


#endif /* __OS_DEF_H__ */
