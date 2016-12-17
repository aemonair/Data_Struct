#include "bstree.h"
#include "tools.h"

//创建节点
static Tree_node *create_node(void)
{
    Tree_node *node = (Tree_node *)Malloc(sizeof(Tree_node));
    bzero(node, sizeof(Tree_node));
 
    return node;
}
//1.销毁BST二叉搜索树
void BSTree_destroy(BSTree **root)
{
    if(*root != NULL)
    {
        BSTree_destroy(&(*root)->left_child);   //先处理左孩子
        BSTree_destroy(&(*root)->right_child);  //先处理右孩子
        free(*root);                            //销毁当前节点
        *root = NULL;
    }
}
//2.中序遍历BST二叉搜索树
//根据二叉排序树的性质,中序遍历得到升序序列
void mid_order_print(BSTree *root)
{
    if(root != NULL){
         mid_order_print(root->left_child);
         printf("%d ", root->data);
         mid_order_print(root->right_child);
    }
}

//3.寻找BST二叉搜索树中的最大数
//由于是二叉搜索树,所以,最大值在右孩子的最右边节点
Tree_node *BSTree_max(BSTree *root)
{
    if(NULL == root)
    {
        return NULL;
    }
    if(NULL == root->right_child) //若无右孩子,当前根节点比左子树都大
    {
        return root;
    }
    else
    {
        return BSTree_max(root->right_child);//递归右边查找
    }
}
//4.寻找BST二叉搜索树中的最小数
//最小值在最左节点
Tree_node *BSTree_min(BSTree *root)
{
    if(NULL == root)
    {
        return NULL;
    }
    if(NULL == root->left_child)
    {
        return root;
    }
    else
    {
        return BSTree_min(root->left_child);
    }
}
//5.通过数组创建BST二叉搜索树
//
//
//  Φ  8   8    8       8        8        8          8         8         8
//        /    / \     / \      / \      / \        / \       / \       / \
//       3    3  10   3  10    3  10    3  10      3  10     3  10     3  10
//                   /        / \      / \   \    / \   \   / \   \   / \   \
//                  1        1   6    1   6  14  1   6  14 1   6  14 1   6   14
//                                                  /         / \       / \  /
//                                                 4         4   7     4   7 13  
BSTree *BSTree_create(int *a, int length)
{
    int i = 0;
    BSTree *root = NULL;
    if(NULL == a || length < 0)
    {
        return NULL;
    }
    for(i = 0; i < length; ++i)
    {
        printf("a[%d],%d\n", i, a[i]);
        BSTree_insert1(&root, a[i]);    //依次插入数组中元素
    }
    return root;
}
//6.删除BST中某节点
//   1. 欲删除节点为叶子节点,如1,则释放掉并将其父节点指向其节点的指针置为空;
//   2. 欲删除节点无左孩子有右孩子,如10,则用其右孩子的左右子树替换当前左右子树,并释放;
//   3. 欲删除节点无右孩子有左孩子,如14,则用其左孩子的左右子树替换当前左右子树,并将其释放.
//   4. 欲删除节点左右孩子均不为空,如8,在删去*p之后，为保持其它元素之间的相对位置不变，可按中序遍历保持有序进行调整。
//      比较好的做法是，找到*p的直接前驱（或直接后继）*s，用*s来替换结点*p，然后再删除结点*s。
Boolean BSTree_delete(BSTree *root, int key)
{
    Tree_node *p = NULL;
    Tree_node *q = NULL;
    Tree_node *s = NULL;
    if(NULL == root)
    {
        return FALSE;
    }
    if(NULL == (p = BSTree_search(root, key)))
    {
        return FALSE;
    }

    if(NULL == p->left_child && NULL == p->right_child)//叶子节点
    {
        q = p;
        s = find_parent(root, BSTree_search(root, key));
        if(s->left_child->data == q->data) //父节点指向空
            s->left_child = NULL;
        else
            s->right_child = NULL;
        free(q);
    }
    else if(NULL == p->left_child && p->right_child != NULL) //2无左子树有右子树 如10
    {
        q = p->right_child;
        p->data = p->right_child->data;
        p->left_child = q->left_child;
        p->right_child = q->right_child;
        free(q);
    }
    else if(NULL == p->right_child && p->left_child != NULL) // 3无右孩子有左孩子 如14
    {
        q = p->left_child;
        p->data = p->left_child->data;
        p->left_child = q->left_child;
        p->right_child = q->right_child;
        free(q);
    }
    else //左右子树均不为空 如8
    {
        q = p;
        s = p->left_child;   //左转
        while(s->right_child)//向右走向尽头
        {
            q = s;
            s = s->right_child;
        }
        p->data = s->data;   //s指向被删节点的"前驱"
        if(q != p)
            q->right_child = s->left_child; //重接q的右子树
        else
            q->left_child = s->left_child;  //重接q的左子树
        free(s);
    }
    return TRUE;
}
//7.1.在BST二叉搜索树中插入某节点
Boolean BSTree_insert0(BSTree **root, int data)
{
    Tree_node *p = create_node();
    p->data = data;
    if(NULL == *root)
    {
        *root = p;
        return TRUE;
    }
    //插入当前节点的左孩子
    if((*root)->left_child == NULL && (*root)->data > data)
    {
        (*root)->left_child = p;
        return TRUE;
    }
    //插入当前节点的右孩子
    if((*root)->right_child == NULL && (*root)->data < data)
    {
        (*root)->right_child = p;
        return TRUE;
    }
    if((*root)->data > data)
    {
        BSTree_insert0(&((*root)->left_child), data);
    }
    else if((*root)->data < data)
    {
        BSTree_insert0(&((*root)->right_child), data);
    }
    else
    {
        return FALSE;
    }
}
//7.2.在BST二叉搜索树中插入某节点
//   首先查找,BST中若有此节点,则不进行插入.
Boolean BSTree_insert1(BSTree **root, int data)
{
    if(BSTree_search(*root, data) != NULL)//已存在不插入
    {
        return FALSE;
    }
    if(NULL == *root)  //根为空
    {
        Tree_node *p = create_node();
        p->data = data;
        *root = p;
        return TRUE;
    }
    else if((*root)->data > data) //在左子树
    {
        BSTree_insert1(&(*root)->left_child, data);
        return TRUE;
    }
    else if((*root)->data < data)
    {
        BSTree_insert1(&(*root)->right_child, data);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//8.在BST二叉搜索树中根据值寻找某节点
//递归查找
Tree_node *BSTree_search(BSTree *root, int key)
{
    if(NULL == root)
    {
        return NULL;
    }
    if(root->data < key)
    {
        return BSTree_search(root->right_child, key);
    }
    else if(root->data > key)
    {
        return BSTree_search(root->left_child, key);
    }
    else
    {
        return root;
    }
}

//9.在BST二叉搜索树中寻找某节点的父节点
Tree_node *find_parent(BSTree *root, Tree_node *node)    //找到指定节点的双亲节点
{
    Tree_node *p_node = NULL;

    if(root == NULL || root->left_child == node 
                    || root->right_child == node){
        //root不存在或者root是所要找的双亲节点
        return root;
    }
    p_node = find_parent(root->left_child, node); 
    if(p_node == NULL)
    { 
        p_node = find_parent(root->right_child, node);
    }
    return p_node;
}
