#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct AVL_node{
    int                data;  //节点数据域
    int              height;  //节点高度
    struct AVL_node  * left;  //左孩子
    struct AVL_node  *right;  //右孩子
}AVL_node;                    //节点

typedef AVL_node *AVL_Tree;   //树

#define  ONE       (1)
#define  max(a, b) ((a) < (b) ? (b) : (a))


//AVL树的接口
//1.        得到树的高度
int         get_tree_height(AVL_Tree root)             ;
//2.        遍历二叉树
//2.1       前序遍历
void        preorder_avltree(AVL_Tree root)            ;
//2.2       中序遍历
void        inorder_avltree(AVL_Tree root)             ;
//2.3       后序遍历
void        postorder_avltree(AVL_Tree root)           ;

//3.        查找数据域为value的节点
//3.1       递归查找
AVL_node *  find_node(AVL_Tree root, int value)        ; 
//3.2       非递归查找
AVL_node *  find_node_(AVL_Tree root, int value)       ; 
//3.3       找到值最大的节点
AVL_node *  get_max_node(AVL_Tree root)                ;
//3.4       找到值最小的节点
AVL_node *  get_min_node(AVL_Tree root)                ;

//4.        将节点插入到avl树中
AVL_Tree    avltree_insert(AVL_Tree root, int data)    ;    
//5.        从avl树中删除指定数值
AVL_Tree    avltree_delete(AVL_Tree root, int data)    ;
//6.        销毁avl树
void        destroy_avltree(AVL_Tree root)             ;
#endif//_AVL_TREE_H_
