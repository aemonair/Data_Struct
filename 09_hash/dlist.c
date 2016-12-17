#include "dlist.h"
#include "tools.h"

void print_int(void *data)
{
    printf("%d ",*(int *)data);
}


static void *dlist_iter_head(Iterator *iter, Dlist *dlist);
static void *dlist_iter_tail(Iterator *iter, Dlist *dlist);
static void *dlist_iter_prev(Iterator *iter, Dlist *dlist);
static void *dlist_iter_next(Iterator *iter, Dlist *dlist);

static void *dlist_iter_head(Iterator *iter, Dlist *dlist)
{
    if(iter == NULL || dlist == NULL)
    {
        return NULL;
    }
    iter->index = 0;
    iter->size = dlist->count;

    if(dlist->head->data == NULL || dlist->count == ZERO)
    {
        iter->ptr = NULL;
    }
    else
    {
        iter->ptr = dlist->head->data;
    }
    return iter->ptr;
}
static void *dlist_iter_tail(Iterator *iter, Dlist *dlist)
{
    if(iter == NULL || dlist == NULL)
    {
        return NULL;
    }
    iter->index = dlist->count - 1;
    iter->size = dlist->count;

    if(dlist->tail->data == NULL || dlist->count == ZERO)
    {
        iter->ptr = NULL;
    }
    else
    {
        iter->ptr = dlist->tail->data;
    }
    return iter->ptr;
}
static void *dlist_iter_prev(Iterator *iter, Dlist *dlist)
{
    if(iter == NULL || dlist == NULL)
    {
        return NULL;
    }
    iter->index  --;
    iter->size = dlist->count;

    if(iter->index <= ZERO)
    {
        iter->ptr = NULL;
    }
    else
    {
        iter->ptr = find_node(dlist, iter->index)->data;
    }
    return iter->ptr;
}
static void *dlist_iter_next(Iterator *iter, Dlist *dlist)
{
    if(iter == NULL || dlist == NULL)
    {
        return NULL;
    }
    iter->index ++;
    iter->size = dlist->count;

    if(iter->index >= iter->size)
    {
        iter->ptr = NULL;
    }
    else
    {
        iter->ptr = find_node(dlist, iter->index)->data;
    }
    return iter->ptr;
}
Dlist_node *create_node(void);
Dlist_node *create_node(void)
{
    Dlist_node *node = (Dlist_node *)Malloc(sizeof(Dlist_node));
    bzero(node, sizeof(Dlist_node));

    return node;
}
//双端链表的初始化
Dlist *init_dlist(void)
{
    Dlist *dlist = (Dlist *)Malloc(sizeof(Dlist));
    bzero(dlist, sizeof(Dlist));

    dlist->iter_head = dlist_iter_head;
    dlist->iter_tail = dlist_iter_tail;
    dlist->iter_prev = dlist_iter_prev;
    dlist->iter_next = dlist_iter_next;
    return dlist;
}
//双端链表的销毁
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
    Dlist_node *p_node = NULL;
    p_node = (*dlist)->head;
    while((*dlist)->head != NULL)
    {
        (*dlist)->head = p_node->next;
        if((*dlist)->free != NULL)
        {
            (*dlist)->free(p_node->data);
        }
        free(p_node);
        p_node = (*dlist)->head;
    }
    free(*dlist);
    *dlist = NULL;
}
//头部插入
Boolean push_front(Dlist *dlist, void *data)
{
    Dlist_node *node = create_node();
    node->data = data ;

    if(dlist == NULL || data == NULL)
    {
        return FALSE;
    }
    if(dlist->count == ZERO)
    {
        dlist->tail = node;
    }
    else{
        node->next = dlist->head;
        dlist->head->prev = node;
    }
    dlist->head = node;
    dlist->count ++;

    return TRUE;
}
//尾部插入
Boolean push_back(Dlist *dlist, void *data)
{
    if(dlist == NULL || data == NULL)          /*error:value == NULL*/
    {
        return FALSE;
    }
    Dlist_node *node = create_node();           /*error*/
    node->data = data ;
    if(dlist->count == ZERO)
    {
        dlist->head = node;
    }
    else{
        node->prev = dlist->tail;
        dlist->tail->next = node;
    }
    dlist->tail = node;
    dlist->count ++;

    return TRUE;                               /*my_error*/
}
//头部删除
Boolean pop_front(Dlist *dlist)
{
    if(dlist == NULL || dlist->count == ZERO)
    {
        return FALSE;
    }

    Dlist_node *node = dlist->head;

    if(dlist->count == ONLY_ONE)
    {
        dlist->head = dlist->tail = NULL;
    }
    else
    {
  /*   node->next->prev = NULL;
   *   dlist->head = node->next;
   */   dlist->head = node->next;
        dlist->head->prev = NULL;
    }
/*
    dlist->free(node);
    node = NULL;
*/
    if(dlist->free != NULL)
    {
        dlist->free(node->data);
    }
    free(node);
    dlist->count -- ;
    
    return TRUE;
}
//尾部删除
Boolean pop_back(Dlist *dlist)
{
    if(dlist == NULL || dlist->count == ZERO)
    {
        return FALSE;
    }

    Dlist_node *node = dlist->tail;

    if(dlist->count == ONLY_ONE)
    {
        dlist->head = dlist->tail = NULL;
    }
    else
    {
        dlist->tail = node->prev;
        dlist->tail->next = NULL;
    }
    
    if(dlist->free != NULL)
    {
        dlist->free(node->data);
    }
    free(node);
    dlist->count -- ;
    
    return TRUE;
}
//插入到当前节点前
Boolean insert_prev(Dlist *dlist, Dlist_node *node, void *value)
{
    Dlist_node *p_node = create_node();
    p_node->data = value;

    if(dlist == NULL || node == NULL )
    {
        return FALSE;
    }
    if(dlist->count == ONLY_ONE)
    {
        push_front(dlist, value);
        return TRUE;
    }
    else
    {
        p_node->next = node;
        p_node->prev = node->prev;
        
        node->prev->next = p_node;
        node->prev = p_node;
        dlist->count++;
    }
    return TRUE;
}
//插入到当前节点后
Boolean insert_next(Dlist *dlist, Dlist_node *node, void *value)
{
    Dlist_node *p_node = create_node();
    p_node->data = value;

    if(dlist == NULL || node == NULL )
    {
        return FALSE;
    }
    if(dlist->count == ONLY_ONE)
    {
        push_back(dlist, value);
        return TRUE;
    }
    else
    {
        p_node->next = node->next;
        p_node->prev = node;
        
        node->next->prev = p_node;
        node->next = p_node;
        dlist->count++;
    }
    return TRUE;
}
//删除某个节点
Boolean remove_dlist_node(Dlist *dlist, Dlist_node *node)
{
    if(dlist == NULL || node == NULL)
    {
        return FALSE;
    }
    if(node->next == NULL)
    {
        return pop_back(dlist);
    }
    else
    {
        Dlist_node *p_node = node->next;
        node->data = p_node->data;

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
//显示双端链表信息
void show_dlist(Dlist *dlist, Print_func print)
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

//得到第一个节点数据域
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
//得到最后一个节点数据域
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
//得到链表节点数量
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

//得到第几个节点
Dlist_node *find_node(Dlist *dlist, int index)
{
    int i = 0;
    Dlist_node *p_node = NULL;

    if(dlist == NULL || index > dlist->count || index < 0)
    {
        return NULL;
    }
    p_node = dlist->head;
    while(i++ < index)
    {
        p_node = p_node->next;
    }
    return p_node;
}
