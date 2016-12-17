#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "tools.h"

#define END ('#')
#define ONE (1)

typedef struct Tree_node Tree_node;

struct Tree_node{
    char              data;                                                 //数据区域
    Tree_node * left_child;    
    Tree_node *right_child;
};                 

typedef Tree_node *Bin_tree;                                                //二叉树的根节点


//二叉树的接口
//一.创建二叉树
Bin_tree create_tree(char **str);                                           //一.1.创建二叉树
Bin_tree create_tree_by_pre_mid(char *pre_str, char *mid_str, int length);  //一.2.通过前序和中序创建二叉树
Bin_tree create_tree_by_mid_last(char *mid_str, char *last_str, int length);//一.3.通过中序和后序创建二叉树  

//二.销毁二叉树
void destroy_tree(Bin_tree *root);                                          //二.1.销毁二叉树
void destroy_tree_nr(Bin_tree *root);                                       //二.2.非递归销毁二叉树

//三.遍历二叉树
//        A      |      A
//       / \     |     / \
//      B   C    |    C   B
//     / \   \   |   /   / \
//    D   E   F  |  F   E   D
//
//    先序（根、左、右）  A  B  D  E  C  F
//    中序（左、根、右）  D  B  E  A  C  F
//    后序（左、右、根）  D  E  B  F  C  A
//    层序 （1----h）     A  B  C  D  E  F
void pre_order_print(Bin_tree root);                                        //三.1.前序递归遍历
void mid_order_print(Bin_tree root);                                        //三.2.中序递归遍历
void last_order_print(Bin_tree root);                                       //三.3.后序递归遍历

void pre_order_print_nr(Bin_tree root);                                     //三.4.前序非递归遍历
void mid_order_print_nr(Bin_tree root);                                     //三.5.中序非递归遍历
void last_order_print_nr(Bin_tree root);                                    //三.6.后序非递归遍历

void level_order_print(Bin_tree root);                                      //三.7.层序遍历


//四.二叉树的变量
void swap_left_right(Bin_tree root);                                        //四.1.得到二叉树的镜像
int get_binarytree_height(Bin_tree root);                                   //四.2.得到二叉树的高度
int get_largest_dir_count(Bin_tree root);                                   //四.3.得到二叉树的最大路径
int get_binarytree_node_count(Bin_tree root);                               //四.4.得到二叉树的节点个数
int get_binarytree_leaf_count(Bin_tree root);                               //四.5.得到二叉树的叶子节点个数
int get_binarytree_level_count(Bin_tree root, int level);                   //四.6.得到指定层级的节点个数
Bin_tree copy_binary_tree(Bin_tree root);                                   //四.7.二叉树的拷贝

//五.二叉树的性质
Boolean is_full_binary_tree(Bin_tree root);                                 //五.1.判断是否是满二叉树
Boolean is_complete_binary_tree(Bin_tree root);                             //五.2.判断是否是完全二叉树
Boolean is_balance_binary_tree(Bin_tree root);                              //五.3.判断是否是平衡二叉树
Boolean is_include_tree(Bin_tree root1,
                        Bin_tree root2);                                    //五.4.判断二叉树是否包含
Boolean is_binarytree_equal(Bin_tree root1,
                            Bin_tree root2);                                //五.5.判断二叉树是否相等




//六.二叉树的查找
Tree_node *find_value(Bin_tree root, char value);                           //六.1.找到指定值所在的节点
Tree_node *find_parent(Bin_tree root,
                       Tree_node *node);                                    //六.2.找到指定节点的双亲节点
Tree_node *find_common_node(Bin_tree root, Tree_node *node1,
                            Tree_node *node2 );                             //六.3.找到两个节点的最近公共节点
                      
#endif
