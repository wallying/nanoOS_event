/**
 * file:    lib_queue.h
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#ifndef __LIB_QUEUE_H__
#define __LIB_QUEUE_H__


typedef struct {
    void *buf;
    unsigned int len;   /* item max number */
    unsigned int size;  /* item type size (byte) */
    unsigned int widx;
    unsigned int ridx;
    unsigned char full; /* queue full flag */
} queue_t;


void  queue_init(queue_t *queue, void *buf, unsigned int len, unsigned int size);
void  queue_clear(queue_t *queue);
int   queue_is_empty(const queue_t *queue);
int   queue_is_full(const queue_t *queue);
unsigned int queue_item_len(const queue_t *queue);
unsigned int queue_free_len(const queue_t *queue);
unsigned int queue_write(queue_t *queue, void *buf, unsigned int len);
unsigned int queue_write_rewind(queue_t *queue, void *buf, unsigned int len);
unsigned int queue_push(queue_t *queue, void *buf, unsigned int len);
unsigned int queue_push_rewind(queue_t *queue, void *buf, unsigned int len);
unsigned int queue_read(queue_t *queue, void *buf, unsigned int len);


#endif /* __LIB_QUEUE_H__ */
