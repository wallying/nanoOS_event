/**
 * file:    lib_queue.c
 * author:  wallying@foxmail.com
 * date:    2019-12-17
 **/


#include "lib/lib_mem.h"
#include "lib/lib_queue.h"


#define LIBQ_DBG_EN (0)


void queue_init(queue_t *queue, void *buf, unsigned int size, unsigned int num)
{
    if (queue == NULL) {
        return;
    }

    queue->buf = buf;
    queue->size = size;
    queue->num = num;
    queue->cnt = 0;
    queue->widx = 0;
    queue->ridx = 0;
}


void queue_clear(queue_t *queue)
{
    if (queue == NULL) {
        return;
    }

    queue->cnt = 0;
    queue->widx = 0;
    queue->ridx = 0;
}


int queue_is_empty(const queue_t *queue)
{
    if (queue == NULL) {
        return 0;
    }

    return (queue->cnt == 0) ? 1 : 0;
}


int queue_is_full(const queue_t *queue)
{
    if (queue == NULL) {
        return 0;
    }

    return (queue->cnt == queue->num) ? 1 : 0;
}


unsigned int queue_used_cnt(const queue_t *queue)
{
    if (queue == NULL) {
        return 0;
    }

    return queue->cnt;
}


unsigned int queue_free_cnt(const queue_t *queue)
{
    if (queue == NULL) {
        return 0;
    }

    return (queue->num - queue->cnt);
}


//向queue队尾添加写入num个数据项。返回实际写入的数据项个数。
unsigned int queue_write(queue_t *queue, void *buf, unsigned int num)
{
    if ((queue == NULL) || (buf == NULL) || (num == 0)) {
        return 0x00;
    }

    unsigned int cnt = 0;

    for (cnt = 0; cnt < num; cnt++) {
        if (queue->cnt == queue->num) {
            break;
        } else {
            mem_cpy(queue->buf + queue->widx * queue->size,
                    buf + cnt * queue->size,
                    queue->size);
            queue->widx = (queue->widx + 1) % queue->num;
            queue->cnt++;
        }
    }

    return cnt;
}


//向queue队尾重绕写入num个数据项。返回实际写入的数据项个数。
unsigned int queue_write_rewind(queue_t *queue, void *buf, unsigned int num)
{
    if ((queue == NULL) || (buf == NULL)) {
        return 0x00;
    }

    unsigned int cnt = 0;

    for (cnt = 0; cnt < num; cnt++) {
        if (queue->cnt == queue->num) {
#if (LIBQ_DBG_EN)
            mem_set(queue->buf + queue->ridx * queue->size,
                    0x00,
                    queue->size);
#endif
            queue->ridx = (queue->ridx + 1) % queue->num;
            queue->cnt--;
        }
        mem_cpy(queue->buf + queue->widx * queue->size,
                buf + cnt * queue->size,
                queue->size);
        queue->widx = (queue->widx + 1) % queue->num;
        queue->cnt++;
    }

    return cnt;
}


//向queue队首添加写入num个数据项。返回实际写入的数据项个数。
unsigned int queue_push(queue_t *queue, void *buf, unsigned int num)
{
    if ((queue == NULL) || (buf == NULL)) {
        return 0x00;
    }

    unsigned int cnt = 0;

    for (cnt = 0; cnt < num; cnt++) {
        if (queue->cnt == queue->num) {
            break;
        } else {
            queue->ridx = (queue->ridx + queue->num - 1) % queue->num;
            mem_cpy(queue->buf + queue->ridx * queue->size,
                    buf + cnt * queue->size,
                    queue->size);
            queue->cnt++;
        }
    }

    return cnt;
}



//向queue队首重绕写入num个数据项。返回实际写入的数据项个数。
unsigned int queue_push_rewind(queue_t *queue, void *buf, unsigned int num)
{
    if ((queue == NULL) || (buf == NULL)) {
        return 0x00;
    }

    unsigned int cnt = 0;

    for (cnt = 0; cnt < num; cnt++) {
        if (queue->cnt == queue->num) {
            queue->widx = (queue->widx + queue->num - 1) % queue->num;
#if (LIBQ_DBG_EN)
            mem_set(queue->buf + queue->widx * queue->size,
                    0x00,
                    queue->size);
#endif
            queue->cnt--;
        }
        queue->ridx = (queue->ridx + queue->num - 1) % queue->num;
        mem_cpy(queue->buf + queue->ridx * queue->size,
                buf + cnt * queue->size,
                queue->size);
        queue->cnt++;
    }

    return cnt;
}


//从queue队首读取num个数据项到buf中。返回实际读取到的数据项个数。
unsigned int queue_read(queue_t *queue, void *buf, unsigned int num)
{
    if ((queue == NULL) || (buf == NULL)) {
        return 0x00;
    }

    unsigned int cnt = 0;

    for (cnt = 0; cnt < num; cnt++) {
        if (queue->cnt == 0) {
            break;
        } else {
            mem_cpy(buf + cnt * queue->size,
                    queue->buf + queue->ridx * queue->size,
                    queue->size);
#if (LIBQ_DBG_EN)
            mem_set(queue->buf + queue->ridx * queue->size,
                    0x00,
                    queue->size);
#endif
            queue->ridx = (queue->ridx + 1) % queue->num;
            queue->cnt--;
        }
    }

    return cnt;
}


