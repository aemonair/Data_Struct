#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "dlist.h"

typedef struct Queue
{
    Dlist *dlist;
}Queue;

//1.初始化
Queue *init_queue(void);
//2.销毁
void destroy_queue(Queue **queue);
//3.入队
void in_queue(Queue *queue, void *value);/*入队返回值：空*/
//4.出队
Boolean out_queue(Queue *queue);
//5.得到队首元素
Boolean get_front_queue(Queue *queue, void **value);
//6.判断队列是否为空
Boolean is_queue_empty(Queue *queue);
//7.得到队列元素个数
int get_queue_count(Queue *queue);
#endif
