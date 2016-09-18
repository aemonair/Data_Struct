#ifndef _DLIST_H_
#define _DLIST_H_

#include "iterator.h"

#define TRUE      (1)
#define FALSE     (0)
#define ZERO      (0)
#define ONLY_ONE  (1)
typedef unsigned char Boolean ;
typedef void (*Print_func)(void *value);

void print_int(void *data);

typedef struct Dlist_node{
    struct Dlist_node *prev;
    struct Dlist_node *next;    //指向后一个节点
    void              *data;
}Dlist_node;

typedef struct Dlist Dlist;
//通用链表控制信息
typedef struct Dlist
{
    struct Dlist_node *head;   //指向头结点
    struct Dlist_node *tail;
    int               count;

    //这是一个指向某个需要被释放的数据域的函数指针
    void (*free)(void *ptr);
    //比较节点数据域
    Boolean (*match)(void *value1, void *value2);
    //拷贝节点数据域
    void *(*copy_node)(void *value);
    
    //指向链表头部
    void *(*iter_head)(Iterator *iter, Dlist *dlist);
    //指向链表尾部
    void *(*iter_tail)(Iterator *iter, Dlist *dlist);
    //指向前一个元素位置
    void *(*iter_prev)(Iterator *iter, Dlist *dlist);
    //指向后一个元素位置
    void *(*iter_next)(Iterator *iter, Dlist *dlist);
}Dlist;

//双端链表的初始化
    Dlist *init_dlist(void);
//双端链表的销毁
    void destroy_dlist(Dlist **dlist);//二重指针
//头部插入
    Boolean push_front(Dlist *dlist, void *data);
//尾部插入
    Boolean push_back(Dlist *dlist, void *data);
//头部删除
    Boolean pop_front(Dlist *dlist);
//尾部删除
    Boolean pop_back(Dlist *dlist);
//插入到当前节点前
    Boolean insert_prev(Dlist *dlist, Dlist_node *node, void *value); 
//插入到当前节点后
    Boolean insert_next(Dlist *dlist, Dlist_node *node, void *value); 
//删除某个节点
    Boolean remove_dlist_node(Dlist *dlist, Dlist_node *node);
//显示双端链表信息
    void show_dlist(Dlist *dlist, Print_func print);
//得到第一个节点数据域
    Boolean  get_front(Dlist *dlist, void **value);
//得到最后一个节点数据域
    Boolean  get_tail(Dlist *dlist, void **value);
//得到链表节点数量
    int get_dlist_count(Dlist *dlist);
//得到第几个节点
    Dlist_node *find_node(Dlist *dlist, int index);
#endif
