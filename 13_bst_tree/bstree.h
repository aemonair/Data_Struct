#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_
#include "tools.h"

typedef struct Tree_node Tree_node;

struct Tree_node
{
    int                data;
    Tree_node *  left_child;
    Tree_node * right_child;
};

typedef Tree_node BSTree;


//1.销毁BST二叉搜索树
void BSTree_destroy(BSTree **root);
//2.中序遍历BST二叉搜索树
void mid_order_print(BSTree *root);    
//3.寻找BST二叉搜索树中的最大数
Tree_node *BSTree_max(BSTree *root);
//4.寻找BST二叉搜索树中的最小数
Tree_node *BSTree_min(BSTree *root);
//5.通过数组创建BST二叉搜索树
BSTree *BSTree_create(int *a, int length);
//6.删除BST中某节点
Boolean BSTree_delete(BSTree *root, int p);
//7.1.在BST二叉搜索树中插入某节点
Boolean BSTree_insert0(BSTree **root, int p);
//7.2.在BST二叉搜索树中插入某节点
Boolean BSTree_insert1(BSTree **root, int p);
//8.在BST二叉搜索树中根据值寻找某节点
Tree_node *BSTree_search(BSTree *root, int p);
//9.在BST二叉搜索树中寻找某节点的父节点
Tree_node *find_parent(BSTree *root, Tree_node *node);   

#endif//_BINARY_SEARCH_TREE_H_
