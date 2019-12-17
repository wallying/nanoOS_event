/**
 * file:    lib_queue.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#ifndef __LIB_QUEUE_H__
#define __LIB_QUEUE_H__


#define LIB_QUEUE(name, size, cnt) \
        unsigned char name##_buf[size*cnt] = {0x00}; \
        queue_t name##_queue = {name##_buf,size,cnt,0,0,0}; \
        queue_t *name = &name##_queue


typedef struct {
    void *buf;
    unsigned int size;  /* item type size (byte) */
    unsigned int num;   /* item max number */
    unsigned int cnt;   /* item number count */
    unsigned int widx;
    unsigned int ridx;
} queue_t;


void  queue_init(queue_t *queue, void *buf, unsigned int size, unsigned int num);
void  queue_clear(queue_t *queue);
int   queue_is_empty(const queue_t *queue);
int   queue_is_full(const queue_t *queue);
unsigned int queue_used_cnt(const queue_t *queue);
unsigned int queue_free_cnt(const queue_t *queue);
unsigned int queue_write(queue_t *queue, void *buf, unsigned int num);
unsigned int queue_write_rewind(queue_t *queue, void *buf, unsigned int num);
unsigned int queue_push(queue_t *queue, void *buf, unsigned int num);
unsigned int queue_push_rewind(queue_t *queue, void *buf, unsigned int num);
unsigned int queue_read(queue_t *queue, void *buf, unsigned int num);


#endif /* __LIB_QUEUE_H__ */
