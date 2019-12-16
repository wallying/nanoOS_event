/**
 * file:    libutil.h
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#ifndef __LIBUTIL_H__
#define __LIBUTIL_H__


#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef BIT
#define BIT(n)          (0x01 << (n))
#endif

#ifndef MIN
#define MIN(x, y)       (((x) < (y)) ? (x) : (y))
#endif

#ifndef MAX
#define MAX(x, y)       (((x) > (y)) ? (x) : (y))
#endif

#ifndef ABS
#define ABS(x)          (((x) > 0) ? (x) : (-(x)))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)   (sizeof(a) / sizeof((a)[0]))
#endif


#ifndef LO_UINT8
#define LO_UINT8(x)         ((uint8)(((x) >> 0) & 0x0F))
#endif
#ifndef HI_UINT8
#define HI_UINT8(x)         ((uint8)(((x) >> 4) & 0x0F))
#endif
#ifndef BUILD_UINT8
#define BUILD_UINT8(loByte, hiByte) \
                    ((uint8)((((uint8)(loByte) & 0x0F) << 0) + \
                             (((uint8)(hiByte) & 0x0F) << 4)))
#endif


#ifndef LO_UINT16
#define LO_UINT16(x)        ((uint8)(((x) >> 0) & 0xFF))
#endif
#ifndef HI_UINT16
#define HI_UINT16(x)        ((uint8)(((x) >> 8) & 0xFF))
#endif
#ifndef BUILD_UINT16
#define BUILD_UINT16(byte0, byte1) \
                    ((uint16)((((uint16)(byte0) & 0xFF) << 0) + \
                              (((uint16)(byte1) & 0xFF) << 8)))
#endif


#ifndef BYTE0_UINT32
#define BYTE0_UINT32(x)     ((uint8)(((x) >>  0) & 0xFF))
#endif
#ifndef BYTE1_UINT32
#define BYTE1_UINT32(x)     ((uint8)(((x) >>  8) & 0xFF))
#endif
#ifndef BYTE2_UINT32
#define BYTE2_UINT32(x)     ((uint8)(((x) >> 16) & 0xFF))
#endif
#ifndef BYTE3_UINT32
#define BYTE3_UINT32(x)     ((uint8)(((x) >> 24) & 0xFF))
#endif
#ifndef BUILD_UINT32
#define BUILD_UINT32(byte0, byte1, byte2, byte3) \
                    ((uint32)((((uint32)(byte0) & 0xFF) <<  0) + \
                              (((uint32)(byte1) & 0xFF) <<  8) + \
                              (((uint32)(byte2) & 0xFF) << 16) + \
                              (((uint32)(byte3) & 0xFF) << 24)))
#endif


#endif /* __LIBUTIL_H__ */
