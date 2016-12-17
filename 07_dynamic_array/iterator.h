#ifndef _ITERATOR_H_
#define _ITERATOR_H_

typedef struct Iterator
{
    void   *ptr;
    int   index;
    int    size;
}Iterator;

typedef Iterator iter;
/*
 *正向迭代器
 * container(list、array、stack)容器
 */

#define FOREACH(iter, container) \
    for(container->iter_head(&(iter), container); \
    (iter).ptr; \
    container->iter_next(&(iter), container))

#define foreach FOREACH

#define FOREACH_REVERSE(iter, container) \
    for(container->iter_tail(&(iter), container); \
    (iter).ptr; \
    container->iter_prev(&(iter), container))

#define foreach_reverse FOREACH_REVERSE

#endif
