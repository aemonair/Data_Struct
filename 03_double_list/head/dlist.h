#ifndef _DLIST_H_
#define _DLIST_H_

#define TRUE      (1)
#define FALSE     (0)
#define ZERO      (0)
#define ONLY_ONE  (1)
typedef unsigned char Boolean ;
typedef void (*Print_func)(void *value);

void print_int(void *data);

//双端链表节点信息
typedef struct Dlist_node{
    struct Dlist_node *prev;    //指向前一个节点
    struct Dlist_node *next;    //指向后一个节点
    void              *data;    //数据(指针)
}Dlist_node;

//通用链表控制信息
typedef struct Dlist{
    struct Dlist_node *head;   //指向头结点
    struct Dlist_node *tail;
    int               count;

    //这是一个指向某个需要被释放的数据域的函数指针
    void (*free)(void *ptr);
    //比较节点数据域
    Boolean (*match)(void *value1, void *value2);
    //拷贝节点数据域
    void *(*copy_node)(void *value);
}Dlist;

//1.双端链表的初始化
    Dlist *init_dlist(void);
//2.双端链表的销毁
    void destroy_dlist(Dlist **dlist);//二重指针
//3.头部插入
    Boolean push_front(Dlist *dlist, void *data);
//4.尾部插入
    Boolean push_back(Dlist *dlist, void *data);
//5.头部删除
    Boolean pop_front(Dlist *dlist);
//6.尾部删除
    Boolean pop_back(Dlist *dlist);
//7.插入到当前节点前
    Boolean insert_prev(Dlist *dlist, Dlist_node *node, void *value); 
//8.插入到当前节点后
    Boolean insert_next(Dlist *dlist, Dlist_node *node, void *value); 
//9.删除某个节点
    Boolean remove_dlist_node(Dlist *dlist, Dlist_node *node);
//10.显示双端链表信息
    void show_dlist(Dlist *dlist, Print_func print);
//11.得到第一个节点数据域
    Boolean  get_front(Dlist *dlist, void **value);
//12.得到最后一个节点数据域
    Boolean  get_tail(Dlist *dlist, void **value);
//13.得到链表节点数量
    int get_dlist_count(Dlist *dlist);

#endif
