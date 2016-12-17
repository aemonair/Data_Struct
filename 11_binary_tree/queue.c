#include <stdio.h>
#include "queue.h"
#include "tools.h"

//1.初始化
Queue *init_queue(void)
{
    Queue *queue = (Queue *)Malloc(sizeof(Queue));
    queue->dlist = init_dlist();

    return queue;
}
//2.销毁
void destroy_queue(Queue **queue)
{
    if(queue == NULL || *queue == NULL)
    {
        return;
    }
    destroy_dlist( &((*queue)->dlist) );
    free(*queue);
    *queue = NULL;
}
//3.入队
void in_queue(Queue *queue, void *value)/*入队返回值：空*/
{
    if(queue == NULL || value == NULL)
    {  
        return ;
    }
    push_back(queue->dlist, value);
}
//4.出队
Boolean out_queue(Queue *queue)
{
    if(queue == NULL || is_queue_empty(queue))
    {
        return FALSE;
    }
    return pop_front(queue->dlist);
}
//5.得到队首元素
Boolean get_front_queue(Queue *queue, void **value)
{
    if(queue == NULL || is_queue_empty(queue))
    {
        return FALSE;
    }
    if(value != NULL){
        return get_front(queue->dlist, value);
    }
}
//6.判断队列是否为空
Boolean is_queue_empty(Queue *queue)
{
    return get_queue_count(queue) == ZERO;
}
//7.得到队列元素个数
int get_queue_count(Queue *queue)
{
    if(queue == NULL)
    {
        return -1;
    }
    return get_dlist_count(queue->dlist);
}
