#include "slist.h"

List_node *create_node(void)
{
    //申请节点，并且对节点初始化（置为0）
    List_node *node = (List_node *)Malloc(sizeof(List_node));
    bzero(node, sizeof(List_node));

    return node;
}
//////////////////////////////////////////////////////////////////////////////////////
//接口实现
//////////////////////////////////////////////////////////////////////////////////////

List_head init_list(void)                                           //1. 链表的初始化
{
    List_head head = NULL;

    head = create_node();

    return head;
}

void      destroy_list(List_head *head)                             //2. 链表的销毁
{
    List_node *p = NULL;
    List_node *q = NULL;

    if(head == NULL || *head == NULL){
        return ;
    } 
   
    //从链表头节点开始，依次对节点进行删除
    p = *head;
    while(p != NULL){
        q = p;
        p = p->next;
        free(q); 
    }

    *head = NULL;
    printf("over!\n");
}

Boolean   push_front(List_head head, int value)                      //3.1 头部添加
{
    List_node *node = NULL;

    if(head == NULL){    //判断链表是否存在
        return FALSE;
    }

    //生成链表节点并且赋初值
    node = create_node();
    node->data = value;

    node->next = head->next;
    head->next = node;

    head->data++;  
    return TRUE;
}

Boolean   push_back(List_head head, int value)                      //3.2 尾部添加（效率低，从头找到尾才能添加）
{
    List_node *p_node = NULL;

    if(head == NULL){    //参数检测
        return FALSE;
    }  

    //查找尾部节点的位置
    p_node = head;
    while(p_node->next != NULL){
        p_node = p_node->next;
    }

    //把新生成的节点追加到链表末尾
    p_node->next = create_node();
    p_node->next->data = value;
    
    head->data++;
    return TRUE;    
}

Boolean   pop_front(List_head head)                                  //4.1 头部删除
{
    List_node *p_node = NULL;

    if(head == NULL || head->next == NULL){
        //链表不存在或者没有有效节点
        return FALSE;
    }

    p_node = head->next;
    head->next = p_node->next;
    free(p_node);
   
    head->data--;
    return TRUE;
}

Boolean   pop_back(List_head head)                                   //4.2 尾部删除（效率低）
{
    List_node *p_node = NULL;

    //参数检测
    if(head == NULL || head->next == NULL){
        return FALSE;
    }

    //从头结点开始查找倒数第二个节点
    p_node = head;

    while(p_node->next->next != NULL){
        p_node = p_node->next;
    }
    //删除最后一个节点，把倒数第二个置为最后一个节点
    free(p_node->next);
    p_node->next = NULL;
  
    head->data--;
    return TRUE;
}




Boolean   find_node(List_head head, int value, List_node **node)    //5. 链表的查找
{
    List_node *p_node = NULL;

    if(head == NULL){
        return FALSE;
    }

    //从第一个有效节点开始查找值为value的节点
    p_node = head->next;
    while(p_node != NULL)
    {
        if(p_node->data == value)
        {    //找到value所在节点
            if(node != NULL)
            {
                *node = p_node;
            }
            return TRUE;
        }
        p_node = p_node->next;
    }
    return FALSE;
}

void      modify_node(List_node *node, int value)                    //6.1 链表节点的修改
{
    node->data = value;
}

Boolean   insert_node(List_head head, int index, int value)   //6.2 链表节点的插入
{
    List_node *node = NULL;
    List_node *p_node = NULL;
    int count = index;

    if(head == NULL || index < 0 || index > head->data){
       //链表不存在并且下标不符合规则
       return FALSE;
    }

    //创建新的节点
    node = create_node();
    node->data = value;

    //寻找插入的位置
    p_node = head;
    while(count--){   //找到被插入节点的前一个节点
       p_node = p_node->next;
    }

    //插入新的节点
    node->next = p_node->next;
    p_node->next = node;
    head->data++;
    return TRUE;
}

void      sort_list_ascend(List_head head)                           //7.1 链表升序
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;

    if(head == NULL || head->data < 2){
        return ;
    }

    for(p_node = head->next; p_node->next ; p_node = p_node->next){ 
        for(q_node = p_node->next; q_node; q_node = q_node->next){
            if(p_node->data > q_node->data){
                swap(p_node, q_node, (unsigned long)(&((List_node *)0)->next));
            }
        }
    }
}

void      sort_list_descend(List_head head)                          //7.2 链表降序
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;

    if(head == NULL || head->data < 2){
        return ;
    }

    for(p_node = head->next; p_node->next ; p_node = p_node->next){ 
        for(q_node = p_node->next; q_node; q_node = q_node->next){
            if(p_node->data < q_node->data){
                swap(p_node, q_node, sizeof(List_node) - sizeof(List_node *));
            }
        }
    }
}

void      show_list(List_head head)                                 //8.1 显示链表信息
{
    List_node *p_node = NULL;

    if(head == NULL){
        return ;
    }
    printf("The List is: \n");

    for(p_node = head->next; p_node != NULL; p_node = p_node->next){
        printf("%d  ", p_node->data);
    }
    printf("\n");
}

int       get_list_length(List_head head)    //8.2 链表的长度
{
    if(head == NULL){
        return -1;
    }
    return head->data;
}
