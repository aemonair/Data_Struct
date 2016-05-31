#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <strings.h> 
#include <string.h>

//链表节点信息：
//
//   1.数据域
//   2.指针域

#define TRUE     (1)
#define FALSE    (0)
#define ZERO     (0)
#define ONLY_ONE (1)
#define TWO      (2)
#define get_data_size()    ((unsigned long)&(((List_node *)0)->next))

struct List_node;    //声明一个类型

//链表控制信息
typedef struct List
{
    struct List_node *head;    //指向链表头部
    struct List_node *tail;    //指向链表尾部
    int              count;    //链表节点数量
}List;

//链表节点信息
typedef struct List_node
{
    int               data;    //数据域
    struct List_node *next;    //指针域
}List_node;

typedef unsigned char Boolean;

//  lua
//  C语言接口与实现   lcc
static void *Malloc(size_t size);
static List_node *create_node(void); 
static void swap(void *a, void *b, int length);
static void Rev_show_list(List_node *node);


/********链表的接口********/

List      *init_list(void)                                 ;    //1.  链表的初始化
void      destroy_list(List **list)                        ;    //2.  链表的销毁
Boolean   push_front(List *list, int value)                ;    //3.1 头部插入
Boolean   push_back(List  *list, int value)                ;    //3.2 尾部插入
Boolean   pop_front(List *list)                            ;    //4.1 头部删除
Boolean   pop_back(List *list)                             ;    //4.2 尾部删除
List_node *find_node(List *list, int value)                ;    //5.1 链表的查找
List_node *find_revise_node(List *list, int num)           ;    //5.2 找到链表的倒数第num个节点
List_node *find_mid_node(List *list)                       ;    //5.3 找到链表的中间节点
void      modify_node(List *list, int index, int value)    ;    //6.1 链表节点的修改
Boolean   insert_node(List *list, int index, int value)    ;    //6.2 链表节点的插入(下标)
void      delete_one_node(List *list, List_node *node)     ;    //6.3 在O（1）的时间复杂度删除节点
void      sort_list_ascend(List *list)                     ;    //7.1 升序
void      sort_list_descend(List *list)                    ;    //7.2 降序排列
void      show_list(List *list)                            ;    //8.1 显示链表信息
void      reverse_show_list(List *list)                    ;    //8.2 逆序输出链表信息
int       get_list_count(List *list)                       ;    //9.  得到链表节点数量
List      *merge_two_lists(List *list1, List *list2)       ;    //10. 合并两个有序链表
List      *merge_two_lists_recure(List *list1, List *list2);    //11. 合并两个有序链表（递归）
List      *reverse_list(List *list)                        ;    //12. 逆置一个链表
List      *list_dump(List *list)                           ;    //13. 链表的拷贝
Boolean   is_list_intersect(List *list1, List *list2)      ;    //14. 判断链表是否有交点
List_node *get_first_common_node(List *list1, List *list2) ;    //15. 得到第一个交点
Boolean   has_circle(List *list)                           ;    //16. 判断一个链表是否有环
List_node *find_circle_first_node(List *list)              ;    //17. 找到带环链表的环入口节点



static void swap(void *a, void *b, int length)
{
    void *temp = Malloc(length);
    memcpy(temp, a, length);
    memcpy(a, b, length);
    memcpy(b, temp, length);
    
    free(temp);
}

static List_node *create_node(void)    //创建链表节点
{
    List_node *node = (List_node *)Malloc(sizeof(List_node));
    bzero(node, sizeof(List_node));

    return node;
}

static void *Malloc(size_t size)
{
    void *result = malloc(size);
    if(result == NULL){
        fprintf(stderr, "the memory is full\n");
        exit(1);
    }
    return result;
}

static void Rev_show_list(List_node *node)
{
   //要打印当前节点，先打印其后续节点
   if(node != NULL){
       Rev_show_list(node->next);
       printf("%d ", node->data);    
   }
}

#endif
