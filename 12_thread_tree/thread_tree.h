#ifndef _THREAD_TREE_H_
#define _THREAD_TREE_H_

#include "tools.h"

#define ONE    ( 1 )
#define THREAD ( 1 )
#define LINK   ( 0 )
#define END    ('#')

typedef struct Tree_node Tree_node;

struct Tree_node{
    char              data;                                                 //数据区域
    int          left_flag;
    int         right_flag;
    Tree_node * left_child;    
    Tree_node *right_child;
};                 

typedef Tree_node *Bin_tree;                                                //二叉树的根节点


Tree_node *find_parent(Bin_tree root, Tree_node *node);
Tree_node *get_parent(Bin_tree root, Tree_node *kid);
//二叉树的接口
Bin_tree create_tree(char **str);                                           //一.1.创建二叉树
void pre_order_print(Bin_tree root);                                        //三.1.前序递归遍历
void mid_order_print(Bin_tree root);                                        //三.2.中序递归遍历
void last_order_print(Bin_tree root);                                       //三.3.后序递归遍历

//线索二叉树的接口

//一.先序线索二叉树

//一.1 先序线索化
void pre_thread(Bin_tree tree);
//一.2 创建先序线索二叉树
Bin_tree create_pre_thread(Bin_tree tree);
//一.3 先序线索二叉树中节点的前驱
Bin_tree front_in_pre(Bin_tree root, Tree_node *p_node);
//一.4 先序线索二叉树中节点的后继
Bin_tree behind_in_pre(Bin_tree root, Tree_node *p_node);
//一.5 遍历输出先序线索二叉树
void pre_order_print_thread(Bin_tree root);
//一.6 销毁先序线索二叉树
void destroy_pre(Bin_tree root);

//二.中序线索二叉树
//二.1 中序线索化
void mid_thread(Bin_tree tree);
//二.2 创建中序线索二叉树
Bin_tree create_mid_thread(Bin_tree tree);
//二.3 中序线索二叉树中节点的前驱
Bin_tree front_in_mid(Bin_tree root, Tree_node *p_node);
//二.4 中序线索二叉树中节点的后继
Bin_tree behind_in_mid(Bin_tree root, Tree_node *p_node);
//二.5 遍历输出中序线索二叉树
void mid_order_print_thread(Bin_tree root);         
//二.6 销毁中序线索二叉树
void destroy_mid(Bin_tree root);

//三.后序线索二叉树
//三.1 后序线索化
void last_thread(Bin_tree tree);
//三.2 创建后序线索二叉树
Bin_tree create_last_thread(Bin_tree tree);
//三.3 后序线索二叉树中节点的前驱
Bin_tree front_in_last(Bin_tree root, Tree_node *p_node);
//三.4 后序线索二叉树中节点的后继
Bin_tree behind_in_last(Bin_tree root, Tree_node *p_node);
//三.5 遍历输出后序线索二叉树
void last_order_print_thread(Bin_tree root);
//三.6 销毁后序线索二叉树
void destroy_last(Bin_tree root);
                      
#endif //_THREAD_TREE_H_
