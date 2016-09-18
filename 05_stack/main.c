#include <stdio.h>
#include "stack.h"

int main(int argc, char **argv)
{
    int i = 0;
    int a[]={1,2,3,4,5};
    void *value;
    int length =  sizeof(a)/sizeof(a[0]);

    Stack *stack = NULL;
    stack = init_stack();
    for(i=0; i< length;++i)
    {
        push_stack(stack, &a[i]);
    }

    Dlist_node *node =  stack->dlist->head;
    for(i=0; i< length || node ;++i)
    {
        print_int(node->data);
        node = node ->next;
    }
    printf("\n");
    
    get_top_stack(stack, &value);
    printf("Top:");
    print_int(value);

    printf("\n");

    printf("the length:\n");
    printf("%d \n",get_stack_count(stack));

    for(i = 0; i < length ; ++i)
    {
        get_top_stack(stack, &value);
        pop_stack(stack);
        print_int(value);
    }
   
    printf("\n");
    destroy_stack(&stack);

    return 0;
}
