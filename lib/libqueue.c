/**
 * file:    libqueue.c
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#include "libqueue.h"


#define LIBQ_DEBUG_EN (0)


//���г�ʼ�������ö��е��ڴ��׵�ַ�Լ����еĴ�С��
void queue_init(queue_t *queue, void *buf, uint16 len, uint16 size)
{
    if (queue == NULL) {
        return;
    }

    queue->buf = buf;
    queue->len = len;
    queue->size = size;
    queue->widx = 0;
    queue->ridx = 0;
    queue->full = 0x00;
}


void queue_clear(queue_t *queue)
{
    if (queue == NULL) {
        return;
    }

    queue->widx = 0;
    queue->ridx = 0;
    queue->full = 0x00;
}


uint8 queue_is_empty(const queue_t *queue)
{
    if (queue == NULL) {
        return 0x00;
    }

    if ((queue->widx == queue->ridx) && (queue->full == 0x00)) {
        return 0x01;
    }

    return 0x00;

//    return (queue->ridx == queue->widx) ? 0x01 : 0x00;
}


uint8 queue_is_full(const queue_t *queue)
{
    if (queue == NULL) {
        return 0x00;
    }

    return queue->full;

//	return (queue->ridx == (queue->widx + 1) % queue->len) ? 0x01 : 0x00;
}


//��ȡ����Ԫ�ظ�����
uint16 queue_item_len(const queue_t *queue)
{
    if (queue == NULL) {
        return 0x00;
    }

    if (queue->full) {
        return queue->len;
    } else {
        return (queue->widx + queue->len - queue->ridx) % queue->len;
    }

//	return (queue->widx + queue->len - queue->ridx) % queue->len;
}


//��ȡ����ʣ��ռ䡣
uint16 queue_free_len(const queue_t *queue)
{
    if (queue == NULL) {
        return 0x00;
    }

    if ((queue->widx == queue->ridx) && (queue->full == 0x00)) {
        return queue->len;
    } else {
        return (queue->ridx + queue->len - queue->widx) % queue->len;
    }

//	return (queue->ridx + queue->len - 1 - queue->widx) % queue->len;
}


#if (LIBQ_DEBUG_EN)
static void mem_set(uint8 *dst, uint8 val, uint16 len)
{
    while (len--) {
        *dst++ = val;
    }
}
#endif
static void mem_cpy(uint8 *dst, uint8 *src, uint16 len)
{
    while (len--) {
        *dst++ = *src++;
    }
}


//��queue��βд��len�����������ʵ��д��������������
uint16 queue_write(queue_t *queue, void *buf, uint16 len)
{
    if ((queue == NULL) || (buf == NULL) || (len == 0)) {
        return 0x00;
    }

    uint16 cnt = 0;

    for (cnt = 0; cnt < len; cnt++) {
		/* circle queue is full */
        if (queue->full) {
		//if (queue->ridx == (queue->widx + 1) % queue->len) {
            break;
        } else {
            mem_cpy((uint8 *)queue->buf + queue->widx * queue->size,
                    (uint8 *)buf + cnt * queue->size,
                    queue->size);
            queue->widx = (queue->widx + 1) % queue->len;

            if (queue->ridx == queue->widx) {
                queue->full = 0x01;
            }
        }
    }

    return cnt;
}


//��queue��βrewindд��len�����������ʵ��д��������������
uint16 queue_write_rewind(queue_t *queue, void *buf, uint16 len)
{
    if ((queue == NULL) || (buf == NULL) || (len == 0)) {
        return 0x00;
    }

    uint16 cnt = 0;

    for (cnt = 0; cnt < len; cnt++) {
		/* circle queue is full */
        if (queue->full) {
		//if (queue->ridx == (queue->widx + 1) % queue->len) {
#if (LIBQ_DEBUG_EN)
            mem_set((uint8 *)queue->buf + queue->ridx * queue->size,
                    0x00,
                    queue->size);
#endif
            queue->ridx = (queue->ridx + 1) % queue->len;
        }
        mem_cpy((uint8 *)queue->buf + queue->widx * queue->size,
                (uint8 *)buf + cnt * queue->size,
                queue->size);
        queue->widx = (queue->widx + 1) % queue->len;

        if (queue->ridx == queue->widx) {
            queue->full = 0x01;
        }
    }

    return cnt;
}


//��queue����д��len�����������ʵ��д��������������
uint16 queue_push(queue_t *queue, void *buf, uint16 len)
{
    if ((queue == NULL) || (buf == NULL) || (len == 0)) {
        return 0x00;
    }

    uint16 cnt = 0;

    for (cnt = 0; cnt < len; cnt++) {
		/* circle queue is full */
        if (queue->full) {
		//if (queue->ridx == (queue->widx + 1) % queue->len) {
            break;
        } else {
            queue->ridx = (queue->ridx + queue->len - 1) % queue->len;
            mem_cpy((uint8 *)queue->buf + queue->ridx * queue->size,
                    (uint8 *)buf + cnt * queue->size,
                    queue->size);
            if (queue->ridx == queue->widx) {
                queue->full = 0x01;
            }
        }
    }

    return cnt;
}



//��queue����rewindд��len�����������ʵ��д��������������
uint16 queue_push_rewind(queue_t *queue, void *buf, uint16 len)
{
    if ((queue == NULL) || (buf == NULL) || (len == 0)) {
        return 0x00;
    }

    uint16 cnt = 0;

    for (cnt = 0; cnt < len; cnt++) {
		/* circle queue is full */
        if (queue->full) {
		//if (queue->ridx == (queue->widx + 1) % queue->len) {
            break;
        } else {
            queue->ridx = (queue->ridx + queue->len - 1) % queue->len;
            mem_cpy((uint8 *)queue->buf + queue->ridx * queue->size,
                    (uint8 *)buf + cnt * queue->size,
                    queue->size);
            if (queue->ridx == queue->widx) {
                queue->full = 0x01;
            }
        }
    }

    return cnt;
}


//��queue��(����)��ȡlen�������buf�С�����ʵ�ʶ�ȡ�������������
uint16 queue_read(queue_t *queue, void *buf, uint16 len)
{
    if ((queue == NULL) || (buf == NULL) || (len == 0)) {
        return 0x00;
    }

    uint16 cnt = 0;

    for (cnt = 0; cnt < len; cnt++) {
        /* circle queue is empty */
        if ((queue->ridx == queue->widx) && (queue->full == 0x00)) {
		//if (queue->ridx == queue->widx) {
            break;
        } else {
            mem_cpy((uint8 *)buf + cnt * queue->size,
                    (uint8 *)queue->buf + queue->ridx * queue->size,
                    queue->size);
#if (LIBQ_DEBUG_EN)
            mem_set((uint8 *)queue->buf + queue->ridx * queue->size,
                    0x00,
                    queue->size);
#endif
            queue->ridx = (queue->ridx + 1) % queue->len;
            queue->full = 0x00;
        }
    }

    return cnt;
}


