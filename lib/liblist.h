/**
 * file:    liblist.h
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#ifndef __LIBLIST_H__
#define __LIBLIST_H__


#ifndef NULL
#define NULL ((void *)0)
#endif


typedef void *list_t;


void  list_init(list_t *list);
void  list_copy(list_t *dest, const list_t *src);
void *list_head(const list_t *list);
void *list_tail(const list_t *list);
void *list_srch(const list_t *list, const void *node);
void *list_prev(const list_t *list, const void *node);
void *list_next(const list_t *list, const void *node);
void  list_insert_head(list_t *list, void *node);
void  list_insert_tail(list_t *list, void *node);
void  list_insert_prev(list_t *list, void *pos, void *node);
void  list_insert_next(list_t *list, void *pos, void *node);
void  list_remove(list_t *list, void *node);
void  list_remove_prev(list_t *list, void *node);
void  list_remove_next(list_t *list, void *node);
void *list_remove_head(list_t *list);
void *list_remove_tail(list_t *list);
int   list_length(const list_t *list);


#endif /* __LIBLIST_H__ */
