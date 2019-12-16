/**
 * file:    liblist.c
 * author:  wallying@foxmail.com
 * date:    2019-12-16
 **/


#include "liblist.h"


/* Base structure of singly linked list node */
struct node_t {
    struct node_t *next;
};


void list_init(list_t *list)
{
    if (list == NULL) {
        return;
    }

    *list = NULL;
}


void list_copy(list_t *dest, const list_t *src)
{
    if ((dest == NULL) || (src == NULL)) {
        return;
    }

    *dest = *src;
}


void *list_head(const list_t *list)
{
    if (list == NULL) {
        return NULL;
    }

    return *list;
}


void *list_tail(const list_t *list)
{
    if (list == NULL) {
        return NULL;
    }

    struct node_t *srch = NULL;

    if (*list != NULL) {
        for (srch = *list; srch->next != NULL; srch = srch->next);
    }

    return srch;
}


/* search for the node item in the list */
void *list_srch(const list_t *list, const void *node)
{
    if ((list == NULL) || (node == NULL)) {
        return NULL;
    }

    struct node_t *srch = NULL;

    for (srch = *list; srch != NULL; srch = srch->next) {
        if (srch == (struct node_t *)node) {
            return srch;
        }
    }

    return NULL;
}


/* search for the prev item of node in the list */
void *list_prev(const list_t *list, const void *node)
{
    if ((list == NULL) || (node == NULL)) {
        return NULL;
    }

    struct node_t *srch = NULL;

    if (*list == node) {
        return NULL;
    } else {
        for (srch = *list; srch->next != NULL; srch = srch->next) {
            if (srch->next == (struct node_t *)node) {
                return srch;
            }
        }
        return NULL;
    }
}


/* search for the next item of node in the list */
void *list_next(const list_t *list, const void *node)
{
    if ((list == NULL) || (node == NULL)) {
        return NULL;
    }

    struct node_t *srch = NULL;

    for (srch = *list; srch != NULL; srch = srch->next) {
        if (srch == (struct node_t *)node) {
            return srch->next;
        }
    }

    return NULL;
}


/* insert node item in the head of the list */
void list_insert_head(list_t *list, void *node)
{
    if ((list == NULL) || (node == NULL)) {
        return;
    }

    list_remove(list, node);

    ((struct node_t *)node)->next = *list;
    *list = node;
}


/* insert node item tail of the list */
void list_insert_tail(list_t *list, void *node)
{
    if ((list == NULL) || (node == NULL)) {
        return;
    }

    struct node_t *srch;

    list_remove(list, node);

    srch = list_tail(list);
    ((struct node_t *)node)->next = NULL;
    if (srch == NULL) {
        *list = node;
    } else {
        srch->next = node;
    }
}



/* insert node item before pos in the list
 * (pos == NULL) ==> list_insert_head()
 */
void list_insert_prev(list_t *list, void *pos, void *node)
{
    if ((list == NULL) || (node == NULL) || (node == pos)) {
        return;
    }

    list_remove(list, node);

    struct node_t *prev = NULL, *srch;

    for (srch = *list; (srch != pos) && (srch != NULL); srch = srch->next) {
        prev = srch;
    }

    if (srch == NULL) {
        ((struct node_t *)node)->next = *list;
        *list = node;
    } else {
        ((struct node_t *)node)->next = ((struct node_t *)prev)->next;
        ((struct node_t *)prev)->next = node;
    }
}


/* insert node item after pos in the list
 * (pos == NULL) ==> list_insert_tail()
 */
void list_insert_next(list_t *list, void *pos, void *node)
{
    if ((list == NULL) || (node == NULL) || (node == pos)) {
        return;
    }

    list_remove(list, node);

    if (list_srch(list, pos) == NULL) {
        list_insert_tail(list, node);
    } else {
        ((struct node_t *)node)->next = ((struct node_t *)pos)->next;
        ((struct node_t *)pos)->next = node;
    }
}


void list_remove(list_t *list, void *node)
{
    if ((list == NULL) || (node == NULL)) {
        return;
    }

    struct node_t *srch = NULL;

    if (*list == node) {
        *list = ((struct node_t *)node)->next;
        ((struct node_t *)node)->next = NULL;
    } else {
        for (srch = *list; srch != NULL; srch = srch->next) {
            if (srch->next == node) {
                srch->next = ((struct node_t *)node)->next;
                ((struct node_t *)node)->next = NULL;
                break;
            }
        }
    }
}


void  list_remove_prev(list_t *list, void *node)
{
    if ((list == NULL) || (node == NULL)) {
        return;
    }


}


void  list_remove_next(list_t *list, void *node)
{
    if ((list == NULL) || (node == NULL)) {
        return;
    }


}


void *list_remove_head(list_t *list)
{
    if (list == NULL) {
        return NULL;
    }

    struct node_t *ret = NULL;

    ret = *list;
    if (*list != NULL) {
        *list = ((struct node_t *)*list)->next;
    }

    return ret;
}


void *list_remove_tail(list_t *list)
{
    if (list == NULL) {
        return NULL;
    }

    struct node_t *n, *ret;
    /* only one node */
    if (((struct node_t *)*list)->next == NULL) {
        n = *list;
        *list = NULL;
        return n;
    }

    /* more than one node */
    for (n = *list; n->next->next != NULL; n = n->next);
    ret = n->next;
    n->next = NULL;
    return ret;
}


int list_length(const list_t *list)
{
    if (list == NULL) {
        return 0;
    }

    int len = 0;
    struct node_t *srch = NULL;

    for (srch = *list; srch != NULL; srch = srch->next) {
        ++len;
    }

    return len;
}

