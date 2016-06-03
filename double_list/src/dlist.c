#include "dlist.h"
#include "tools.h"

void print_int(void *data)
{
    printf("%d ",*(int *)data);
}

Dlist_node *create_node(void);
Dlist_node *create_node(void)
{
    Dlist_node *node = (Dlist_node *)Malloc(sizeof(Dlist_node));
    bzero(node, sizeof(Dlist_node));

    return node;
}
//1.双端链表的初始化
Dlist *init_dlist(void)
{
    Dlist *dlist = (Dlist *)Malloc(sizeof(Dlist));
    bzero(dlist, sizeof(Dlist));

    return dlist;
}
//2.双端链表的销毁
void destroy_dlist(Dlist **dlist)//二重指针
{
    if(dlist == NULL || *dlist == NULL)
    {
        return;
    }
/*
    while((*dlist)->head)        //(*)->
    { 
        pop_back(*dlist);
    }
*/
    Dlist_node *p_node = (*dlist)->head;
    while((*dlist)->head != NULL)
    {
        (*dlist)->head = p_node->next;
        if((*dlist)->free != NULL) //函数指针free
        {
            (*dlist)->free(p_node->data);
        }
        free(p_node);
        p_node = (*dlist)->head;
    }
    free(*dlist);
    dlist = NULL;
}
//3.头部插入
    //  case 1:
    //     node
    //       |
    //   head tail 
    //
    //  case 2:
    //    node
    //    //
    //   node1==node2==node3
    //      \         /
    //       head|tail
Boolean push_front(Dlist *dlist, void *data)
{
    if(dlist == NULL || data == NULL)
    {
        return FALSE;
    }
    
    Dlist_node *node = create_node();  //调用链表工具
    node->data = data ;                //创建一个新节点

    if(dlist->count == ZERO)
    {
        dlist->tail = node;
    }
    else
    {
        node->next = dlist->head;
        dlist->head->prev = node;
    }
    dlist->head = node;                //头插
    dlist->count ++;

    return TRUE;
}
//4.尾部插入
    //  case 1:
    //     node
    //       |
    //   head tail 
    //
    //  case 2:
    //                  node
    //                    \\
    //   node1==node2==node3
    //      \         /
    //       head|tail
Boolean push_back(Dlist *dlist, void *data)
{
    if(dlist == NULL || data == NULL)           /*  error:value == NULL  */
    {
        return FALSE;
    }
    Dlist_node *node = create_node();           
    node->data = data ;
    if(dlist->count == ZERO)
    {
        dlist->head = node;
    }
    else
    {
        node->prev = dlist->tail;
        dlist->tail->next = node;
    }
    dlist->tail = node;
    dlist->count ++;

    return TRUE;                               
}

//5.头部删除
    //  case 1:
    //     (node)
    //       |
    //   head tail 
    //
    //  case 2:
    //   (node1)==node2==node3==node4
    //           /              /
    //          head         tail
Boolean pop_front(Dlist *dlist)
{
    if(dlist == NULL || dlist->count == ZERO)
    {
        return FALSE;
    }

    Dlist_node *node = dlist->head;       //头节点

    if(dlist->count == ONLY_ONE)
    {
        dlist->head = dlist->tail = NULL;
    }
    else
    {
  /*   node->next->prev = NULL;
   *   dlist->head = node->next;  //
   */   
       dlist->head = node->next;
       dlist->head->prev = NULL;
    }
/*
    dlist->free(node);            //free函数释放掉之前所指头节点的位置
    node = NULL;
*/
    if(dlist->free != NULL)       //这里我们调用我们自己的free指针函数
    {
        dlist->free(node->data);
    }
    free(node);
    dlist->count-- ;
    
    return TRUE;
}

//6.尾部删除
    //  case 1:
    //     (node)
    //       |
    //   head tail 
    //
    //  case 2:
    //   node1==node2==node3==(node4)
    //       \            \
    //      head         tail
Boolean pop_back(Dlist *dlist)
{
    if(dlist == NULL || dlist->count == ZERO)
    {
        return FALSE;
    }

    Dlist_node *node = dlist->tail;      //node指向尾节点

    if(dlist->count == ONLY_ONE)
    {
        dlist->head = dlist->tail = NULL;
    }
    else
    {
        dlist->tail = node->prev;
        dlist->tail->next = NULL;        //释放尾节点与链表的连接
    }
    
    if(dlist->free != NULL)
    {
        dlist->free(node->data);
    }
    free(node);
    dlist->count -- ;
    
    return TRUE;
}
//7.插入到当前节点前
    //
    //         node
    //        //  \\
    //   node1      node2==node3
    //      \              /
    //       head        tail
Boolean insert_prev(Dlist *dlist, Dlist_node *node, void *value)
{
    if(dlist == NULL || node == NULL )
    {
        return FALSE;
    }

    Dlist_node *p_node = create_node();
    p_node->data = value;                   //生成节点p->node

    if(dlist->count == ONLY_ONE)
    {
        push_front(dlist, value);           //只有一个节点时，头插
        return TRUE;
    }
    else
    {
        //        p_node
        //        //  \\
        //   node1      node
        p_node->next = node;
        p_node->prev = node->prev;
        
        node->prev->next = p_node;
        node->prev = p_node;
        dlist->count++;
    }
    return TRUE;
}
//8.插入到当前节点后
    //
    //         node
    //        //  \\
    //   node1      node2==node3
    //      \              /
    //       head        tail
Boolean insert_next(Dlist *dlist, Dlist_node *node, void *value)
{
    if(dlist == NULL || node == NULL )
    {
        return FALSE;
    }

    Dlist_node *p_node = create_node();
    p_node->data = value;                   //新节点p_node

    if(dlist->count == ONLY_ONE)
    {
        push_back(dlist, value);
        return TRUE;
    }
    else
    {
        //        p_node
        //       //    \\
        //     node     node1
        p_node->next = node->next;    //先把p_node信息挂在链表上
        p_node->prev = node;
        
        node->next->prev = p_node;    //再改变链表上的结构信息
        node->next = p_node;
        dlist->count++;
    }
    return TRUE;
}
//9.删除某个节点
    //  case 1:
    //     (node)
    //       |
    //   head tail 
    //
    //  case 2:
    //   node1==node2==(node3)==node4
    //       \                  /
    //      head             tail
Boolean remove_dlist_node(Dlist *dlist, Dlist_node *node)
{
    if(dlist == NULL || node == NULL)
    {
        return FALSE;
    }
    if(node->next == NULL)
    {
        return pop_back(dlist);    //在尾部，则尾删
    }
    else
    {
        //                  node   p_node
        //   node1==node2==(node3)==node4==node5
        //       \                         /
        //      head                     tail
        Dlist_node *p_node = node->next;
        node->data = p_node->data;
        
        //用node的下一个节点代替node
        
        node->next = p_node->next;
        p_node->next->prev = node;
    
        if(dlist->free != NULL)
        {
            dlist->free(p_node->data);
        }
        free(p_node);
        dlist->count -- ;
    }
    return TRUE;
}
//10.显示双端链表信息
void show_dlist(Dlist *dlist, Print_func print)  //我们的参数是print，是一个函数指针;
{
    Dlist_node *p_node = NULL;

    if(dlist != NULL && dlist->count >0)
    {
        for(p_node = dlist->head; p_node; p_node = p_node->next)
        {
            print(p_node->data);
        }
        printf("\n");
    }
}

//11.得到第一个节点数据域
    //**value是一个二重指针，可以用来保存void *类型的数据指针域
Boolean  get_front(Dlist *dlist, void **value)
{
    if(dlist == NULL || dlist->count == ZERO)
    {
        return FALSE;
    }
    if(value != NULL)
    {     
       *value = dlist->head->data;
    }
    return TRUE;
}
//12.得到最后一个节点数据域
    //与11同理
Boolean  get_tail(Dlist *dlist, void **value)
{
    if(dlist == NULL || dlist->count == ZERO)
    {
        return FALSE;
    }
    if(value != NULL)
    {     
       *value = dlist->tail->data;
    }
    return TRUE;
}
//13.得到链表节点数量
     //链表控制信息中有关于节点个数的变量count
int get_dlist_count(Dlist *dlist)
{
    if(dlist == NULL)
    {
        return -1;
    }
    else
    {
        return dlist->count;
    }
}
