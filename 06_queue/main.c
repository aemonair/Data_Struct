#include <stdio.h>
#include "queue.h"

int main(int argc, char **argv)
{
    int i = 0;
    int a[]={1,2,3,4,5};
    int *value = NULL;
    int length =  sizeof(a)/sizeof(a[0]);

    Queue *queue = NULL;
    queue = init_queue();
    for(i=0; i< length;++i)
    {
        in_queue(queue, &a[i]);
    }

    Dlist_node *node =  queue->dlist->head;
    for(i=0; i< length ;++i)
    {
        print_int(node->data);
        node = node ->next;
    }
    printf("\n");
   
    printf("Top:");
    get_front_queue(queue, (void **)&value);
    printf("%d ",*value);
    printf("\n");

    printf("the length:\n");
    printf("%d \n",get_queue_count(queue));

    for(i = 0; i < length ; ++i)
    {
        get_front_queue(queue,(void **)&value);
        out_queue(queue);
        printf("%d ",*value);
    }
    printf("\n");
   
    destroy_queue(&queue);
    return 0;
}
