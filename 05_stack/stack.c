#include <stdio.h>
#include "stack.h"
#include "tools.h"
#include "dlist.h"

//接口实现哦
//
//1.初始化
Stack *init_stack(void)
{
    Stack *stack = (Stack *)Malloc(sizeof(Stack));
    //初始化链表
    stack->dlist = init_dlist();

    return stack;
}
//2.销毁
void destroy_stack(Stack **stack)
{
    if(stack == NULL || *stack == NULL)
    {
        return ;
    }
//    destroy_dlist(stack->dlist);
    destroy_dlist(&((*stack)->dlist));
    free(*stack);
    *stack = NULL;
}
//3.入栈
Boolean push_stack(Stack *stack, void *value)
{
    if(stack == NULL || value == NULL)
    {
        return FALSE;
    }
    
    return push_back(stack->dlist, value);
}
//4.出栈
Boolean pop_stack(Stack *stack)
{
    if(stack == NULL )
    {
        return FALSE;
    }
    
    return pop_back(stack->dlist);

}
//5.得到栈顶元素
Boolean get_top_stack(Stack *stack, void **value)
{
/*
    if(stack == NULL || value == NULL)
    {
        return FALSE;
    }
    else
    {
        return get_tail(stack->dlist, value);
    }
*/
    if(stack == NULL || is_stack_empty(stack))
    {
        return FALSE;
    }
    if(value != NULL)
    {
        get_tail(stack->dlist, value);
    }
}
//6.判断栈是否为空
Boolean is_stack_empty(Stack *stack)
{
//    return (get_dlist_count(stack->dlist) >= ZERO);
//
    return get_stack_count(stack) == ZERO;
}
//7.得到栈的元素个数
int get_stack_count(Stack *stack)
{
    if(stack == NULL)
    {
        return -1;
    }
    return get_dlist_count(stack->dlist);
}
