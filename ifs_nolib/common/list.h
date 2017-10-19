/*************************************************************************
	> File Name: list.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月19日 星期四 16时03分54秒
 ************************************************************************/

#ifndef _LIST_H
#define _LIST_H

struct slist_t {
    struct slist_t *next;
};

struct dlist_t {
    struct dlist_t *pre;
    struct dlist_t *next;
};

#define SLIST_HEAD_INIT(name)   { &(name) }
#define SLIST_HEAD(name) \
        struct slist_t name = SLIST_HEAD_INIT(name)

static inline void INIT_SLIST_HEAD(struct slist_t *head)
{
    head->next = head;
}

static inline int slist_empty(struct slist_t *head)
{
    return (head->next == head);
}

static inline void slist_append(struct slist_t *head, struct slist_t *new)
{
    struct slist_t *next = head;
    while (next->next != next)
        next = next->next;

    next->next = new;
    new->next = new;
}

static inline int slist_del(struct slist_t **head, struct slist_t *node)
{
    if (slist_empty(*head)) {
        return -1;
    }

    if (*head == node) {
        *head = node->next;
        return 0;
    }

    while ((*head)->next != *head) {
        if ((*head)->next == node) {
            (*head)->next = node->next;
            return 0;
        }
        *head = (*head)->next;
    }

    return -1;
}

static inline void slist_del_next(struct slist_t *head)
{
    struct slist_t *next = head->next;

    if (next->next != next) {
        head->next = next->next;
    } else {
        head->next = head;
    }
}

#endif
