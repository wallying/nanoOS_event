/**
 * file:    queue.h
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#ifndef __QUEUE_H__
#define __QUEUE_H__


#ifndef NULL
#define NULL ((void *)0)
#endif

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int64;
typedef unsigned long long uint64;


typedef struct {
    void *buf;      //队列的起始地址
    uint16 len;     //队列最多可容纳数据项的个数
    uint16 size;    //每一数据项大小(字节)
    uint16 widx;    //队列写位置
    uint16 ridx;    //队列读位置
    uint8 full;     //队列满标志位
} queue_t;


void  queue_init(queue_t *queue, void *buf, uint16 len, uint16 size);
void  queue_clear(queue_t *queue);
uint8 queue_is_empty(const queue_t *queue);
uint8 queue_is_full(const queue_t *queue);
uint16 queue_item_len(const queue_t *queue);
uint16 queue_free_len(const queue_t *queue);
uint16 queue_write(queue_t *queue, void *buf, uint16 len);
uint16 queue_write_rewind(queue_t *queue, void *buf, uint16 len);
uint16 queue_push(queue_t *queue, void *buf, uint16 len);
uint16 queue_push_rewind(queue_t *queue, void *buf, uint16 len);
uint16 queue_read(queue_t *queue, void *buf, uint16 len);


#endif /* __QUEUE_H__ */
