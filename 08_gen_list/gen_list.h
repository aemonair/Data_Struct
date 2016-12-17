#ifndef _GEN_LIST_H_
#define _GEN_LIST_H

#define  MATCH        (0)
#define  NOT_MATCH    (1)

#include "tools.h"

typedef enum
{
    HEAD = 0, //子表类型（头结点）
    INT,      //整型类型
    CHARACTER,//字符类型
    LIST      //子表类型
}Node_type;

//
typedef struct Gen_node
{
    //1.标志（类型） int, char, list, head
    Node_type n_type;
    //2.实际存储的值
    union {
        int         int_value;
        char       char_value;
        int         head_flag;
        struct Gen_node *head;
    }value;
    //3.next指针
    struct Gen_node     *next;
}Gen_node;

typedef struct Gen_node *Gen_list;

//接口：
//1.广义表的创建
Gen_list init_genlist(char *input_str);
//2.广义表的销毁
void destroy_genlist(Gen_list *gen_list);
//3.广义表元素个数
int get_genlist_count(Gen_list gen_list);
//4.广义表深度
int get_genlist_depth(Gen_list gen_list);
//5.广义表的拷贝
Gen_list copy_genlist(Gen_list gen_list);
//6.显示广义表信息
void show_genlist(Gen_list gen_list);

#endif
