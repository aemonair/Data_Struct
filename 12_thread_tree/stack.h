#ifndef _STACK_H_
#define _STACK_H_

#include "dlist.h"

typedef struct Stack
{
    Dlist *dlist;
}Stack;

//接口哦
//
//1.初始化
Stack *init_stack(void);
//2.销毁
void destroy_stack(Stack **stack);
//3.入栈
Boolean push_stack(Stack *stack, void *value);
//4.出栈
Boolean pop_stack(Stack *stack);
//5.得到栈顶元素
Boolean get_top_stack(Stack *stack, void **value);
//6.判断栈是否为空
Boolean is_stack_empty(Stack *stack);
//7.得到栈的元素个数
int get_stack_count(Stack *stack);
//
#endif
