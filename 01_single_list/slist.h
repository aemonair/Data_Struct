/* list.h */
/*
 * 带头节点的链表
 * */
#ifndef _SLIST_H_
#define _SLIST_H_

#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TRUE     (1)
#define FALSE    (0)

typedef unsigned char Boolean;

//定义链表节点类型
typedef struct List_node{
    int               data;    //数据域  //4
    struct List_node *next;    //指针域  //32位：4 //64位：8
}List_node;


typedef List_node   *List_head;   

List_node *create_node(void);
//链表的接口
//  常见接口：
//     1.初始化
//     2.销毁
//     3.增加
//     4.删除
//     5.查找
//     6.修改
//     7.排序
//     8.显示
List_head init_list(void)                                        ;   //1. 链表的初始化
void      destroy_list(List_head *head)                          ;   //2. 链表的销毁
Boolean   push_front(List_head head, int value)                  ;   //3.1 头部添加
Boolean   push_back(List_head head, int value)                   ;   //3.2 尾部添加（效率低，从头找到尾才能添加）
Boolean   pop_front(List_head head)                              ;   //4.1 头部删除
Boolean   pop_back(List_head head)                               ;   //4.2 尾部删除（效率低）
Boolean   find_node(List_head head, int value, List_node **node) ;   //5. 链表的查找
void      modify_node(List_node *node, int value)                ;   //6.1 链表节点的修改
Boolean   insert_node(List_head head, int index, int value)      ;   //6.2 链表节点的插入(下标)
void      sort_list_ascend(List_head head)                       ;    //7.1 链表升序
void      sort_list_descend(List_head head)                      ;    //7.2 链表降序
void      show_list(List_head head)                              ;    //8.1 显示链表信息
int       get_list_length(List_head head)                        ;    //8.2 链表的长度

#endif //_SLIST_H_
