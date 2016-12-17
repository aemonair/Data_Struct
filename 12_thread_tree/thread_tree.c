#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <math.h>
#include "thread_tree.h"
#include "tools.h"
#include "queue.h"
#include "stack.h"

//二叉树的接口
static int max(int a, int b);
static Tree_node *create_node(void);
static int get_index(char *string, char value);
static void destroy(Bin_tree root);
static Tree_node *find_common(Bin_tree root,
                              Tree_node *node1, Tree_node *node2);

static int max(int a, int b)
{ 
    return b > a ? b : a;
}
static Tree_node *create_node(void)
{
    Tree_node *node = (Tree_node *)Malloc(sizeof(Tree_node));
    bzero(node, sizeof(Tree_node));
 
    return node;
}
static int get_index(char *string, char value)
{
    // abcdefg
    //
    //     e
    char *local = strchr(string, value);
    return local == NULL ? -1 : (local - string) / sizeof(char);
}

Tree_node *find_parent(Bin_tree root,
                       Tree_node *kid)    //找到指定节点的双亲节点
{
    Tree_node *temp = root;
    if(temp->left_child == kid)
    {
        return temp;
    }
    else
    {
        temp = temp->left_child;
        while(temp->left_child != kid && temp->right_child != kid)
        {
            if(temp->left_flag == LINK)
            {
                temp = temp->left_child;
            }
            else
            {
                temp = temp->right_child;
            }
        }
    }
    return temp;
}

Tree_node *get_parent(Bin_tree root, Tree_node *kid)
{
    if(root == NULL || kid == NULL)
    {
        printf("can't find.\n");
        return NULL;
    }
    Tree_node *temp = root;
    if(temp->left_child == kid)
    {
        return temp;
    }
    else
    {
        temp = temp->left_child;
        while(temp->left_child != kid && temp->right_child != kid)
        {
            if(temp->right_flag == LINK)
            {
                temp = temp->right_child;
            }
            else
            {
                temp = temp->left_child;
            }
        }
    }
    return temp;
}
//创建二叉树

//二叉树的接口

//一.创建二叉树
Bin_tree create_tree(char **str)
{
    Bin_tree root = NULL;

    if(str != NULL && *str != NULL && **str != END){
        root = create_node();  
        root->data = **str;
        root->left_flag = LINK;
        root->right_flag = LINK;
   
        //处理完当前节点，然后递归地创建其左右孩子
        //++*str;
        (*str)++;
        root->left_child = create_tree(str);
        //++*str;
        (*str)++;
        root->right_child = create_tree(str);
    }

    return root;
}


//三.1.前序递归遍历
//void pre_order_print(Bin_tree root);                                  
void pre_order_print(Bin_tree root)    //前序递归遍历
{
    if(root != NULL){
         printf("%c ", root->data);
         pre_order_print(root->left_child);
         pre_order_print(root->right_child);
    }
}

//三.2.中序递归遍历
//void mid_order_print(Bin_tree root);                                       
void mid_order_print(Bin_tree root)    //中序递归遍历
{
    if(root != NULL){
         mid_order_print(root->left_child);
         printf("%c ", root->data);
         mid_order_print(root->right_child);
    }

}
//三.3.后序递归遍历
//void last_order_print(Bin_tree root);                                       
void last_order_print(Bin_tree root)    //后序递归遍历
{
    if(root != NULL){
         last_order_print(root->left_child);
         last_order_print(root->right_child);
         printf("%c ", root->data);
    }

}

Tree_node *pre = NULL;      //全局变量

//一.1 先序线索化
//先对根节点进行线索化,再对左右孩子进行线索化.
void pre_thread(Bin_tree tree)
{
    if(tree != NULL)
    {
        if(!tree->left_child)
        {
            tree->left_child = pre;
            tree->left_flag = THREAD;
        }
        else
        {
            tree->left_flag = LINK;
        }
        if(pre->right_child == NULL)
        {
            pre->right_child = tree;
            pre->right_flag = THREAD;
        }
        else
        {
            pre->right_flag = LINK;
        }
        pre = tree;
        if(tree->left_flag == LINK)
            pre_thread(tree->left_child);
        if(tree->right_flag == LINK)
            pre_thread(tree->right_child);
    }
}
//一.2 创建先序线索二叉树
Bin_tree create_pre_thread(Bin_tree tree)
{
    Bin_tree root = NULL;
    root = create_node();                      //创建头节点root
    root->left_flag = LINK;
    root->right_flag = THREAD;
    if(tree == NULL)                           //二叉树为空
    {
        root->left_child = root;
    }
    else
    {
        pre = root;
        root->left_child = tree;               //root的左孩子指向tree
        pre_thread(tree);                      //线索化二叉树tree
        pre->right_child = root;               //遍历完后最后一个pre指向root
        pre->right_flag = THREAD;
        root->right_child = pre;
    }
    return root;
}
//在前序线索二叉树中找到节点p_node的前一个节点
//
//            A
//          /   \
//         B     G
//        / \   /  \
//       C   D H   J 
//          / \ \
//         E   F I 
//    在前序线索二叉树中,遍历顺序为"根左右",
//    对上面这个二叉树转化为前序线索二叉树之后,前序遍历为 A B C D E F G H I J 
//    对节点而言,先根A然后左子树B,B作为根,左子树C,右子树D,D作为根节点,左子树E,右子树F...
//    某一节点的前一个节点,
//    1.作为左子树,前一个节点即是其父节点.
//    2.作为右子树,因为是"根左右"的顺序,于是,其前一个节点为兄弟的最右节点.
//
//一.3 先序线索二叉树中节点的前驱
Bin_tree front_in_pre(Bin_tree root, Tree_node *p_node)
{
    Tree_node *front = NULL;
    Tree_node *parent = NULL;
    front = p_node->left_child;              //先指向p_node左孩子
    if(p_node->left_flag == LINK)
    {
        parent = find_parent(root, p_node);  //查找p_node的父节点
        if(parent->left_child == p_node)     //情况1. 作为左节点
        {
            front = parent;
        }
        else                                 //情况2.
        {
            front = parent->left_child;      //查找左子树的最右节点
            while(front->right_flag == LINK)
            {
                front = front->right_child;
            }
        }
    }
    return front;
}
//在前序线索二叉树中找到节点p_node的后一个节点
//
//            A
//          /   \
//         B     G
//        / \   /  \
//       C   D H   J 
//          / \ \
//         E   F I 
//    在前序线索二叉树中,遍历顺序为"根左右",
//    对上面这个二叉树转化为前序线索二叉树之后,前序遍历为 A B C D E F G H I J 
//    对节点而言,先根A然后左子树B,B作为根,左子树C,右子树D,D作为根节点,左子树E,右子树F...
//    某一节点的后一个节点,
//    1.如果有左孩子,按照根左右的顺序,找当前节点的左节点.
//    2.如果有后继(left_flag == 1),则其right_child其后继.
//    
//
//一.4 先序线索二叉树中节点的后继
Bin_tree behind_in_pre(Bin_tree root, Tree_node *p_node)
{
    Tree_node *behind = NULL;
    behind = p_node->left_child;

    if(p_node->left_flag == LINK)          //p_node有左孩子
    {
        behind = p_node->left_child;
    }
    else                                   //有线索后继
    {
        behind = p_node->right_child;
    }
    return behind;
}
//一.5 遍历输出先序线索二叉树
//根左右的顺序
//先输出根节点,然后找其左孩子,若没有左孩子,根据后继寻找下一个节点
void pre_order_print_thread(Bin_tree root)
{                                           //root为前序线索二叉树的头节点
    Tree_node *p_node = NULL;
    p_node = root->left_child;              //p_node指向根节点tree
    while(p_node != root)                   //当p_node不等于指向头节点的指针root时
    {
        printf("%3c", p_node->data);        //输出前序序列的一个根节点数据
        if(p_node->left_flag == LINK)       //前序序列中根节点的左孩子
        {
            p_node = p_node ->left_child;
        }
        else
        {                                   
            p_node = p_node->right_child;   //根据后继线索找到后继节点
        }
    }
}   
//一.6 销毁先序线索二叉树
//与遍历顺序相同,保存当前节点,得到下一个时释放当前资源
void destroy_pre(Bin_tree root)    
{
    if(NULL == root)
    {
        return;
    }
    Tree_node *p_node = root->left_child;
    Tree_node *pre = p_node;

    while(p_node != root)
    {
        pre = p_node;                          //保存当前根节点
        if(p_node->left_flag == LINK)          //找其左子树
        {
            p_node = p_node->left_child;
        }
        else                                   //寻找其后继
        {
            p_node = p_node->right_child;
        }
        free(pre);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//二.中序线索二叉树
//二.1 中序线索化
//按"左根右"的顺寻进行
void mid_thread(Bin_tree tree)                //对二叉树进行中序线索化
{
    if(tree != NULL)
    {
        mid_thread(tree->left_child);        //先对tree的左子树线索化
        //到此,tree节点的左子树不存在或已线索化,接下来对tree线索化
        if(tree->left_child == NULL)         //tree的左孩子不存在则进行前驱线索
        {
            tree->left_child = pre;          //建立当前节点tree的前驱线索
            tree->left_flag = THREAD;
        }
        else
        {
            tree->left_flag = LINK;          //置tree的left_child指针为指向左孩子标志
        }
        if(pre->right_child == NULL)         //pre的右孩子不存在则进行后继线索
        {
            pre->right_child = tree;         //建立节点pre的后继线索
            pre->right_flag = THREAD;
        }
        else
        {
            pre->right_flag = LINK;          //置p的right_child指针为指向右孩子标志
        }
        pre = tree;                          //pre移至tree节点
        mid_thread(tree->right_child);       //对tree的右子树线索化
    }
}

//二.2 创建中序线索二叉树
//创建一个root根节点,对tree进行中序线索化
Bin_tree create_mid_thread(Bin_tree tree)  
{
    Bin_tree root = NULL;
    root = create_node();                   //创建头节点
    root->left_flag = LINK;
    root->right_flag = THREAD;
    if(tree == NULL)                        //二叉树为空
    {
        root->left_child = root;
    }
    else
    {
        root->left_child = tree;            //root的left_child指针指向二叉树根节点tree
        pre = root;
        mid_thread(tree);                   //对二叉树tree进行中序线索化
        pre->right_child = root;            //最后处理,加入指向头节点的线索
        pre->right_flag = THREAD;
        root->right_child = pre;            //头节点的right_child指针线索化为指向最后一个节点
    }
    return root;                            //返回线索化后指向二叉树的头节点的指针root
}
//在中序线索二叉树中查找某节点的前一个节点
//按"左根右"的顺序而言,
//若p_node的left_flag为1,则p_node的left_child即为其前驱节点
//若p_node的left_flag为0,则p_node有左子树,前驱则在其左子树的最右孩子节点
//                   
//          A        
//        /   \
//       B     G     
//      / \    / \
//     C   D  H   J  
//        / \  \
//       E   F  I        
//
// 中序: C B E D F A H I G J 
//二.3 中序线索二叉树中节点的前驱
Bin_tree front_in_mid(Bin_tree root, Tree_node *p_node)
{
    Tree_node *front = NULL;
    front = p_node->left_child;
    if(p_node->left_flag == LINK)
    {
        while(front->right_flag == LINK)      //查找最右孩子
        {
            front = front->right_child;
        }
    }
    return front;
}
//中序线索二叉树中查找某节点后继节点
//按"左根右"的顺序而言,
//若p_node的right_flag为1,则p_node的right_child即为其后继节点
//若p_node的right_flag为0,则p_node有右子树,前驱则在其右子树的最左孩子节点
//二.4 中序线索二叉树中节点的后继
Bin_tree behind_in_mid(Bin_tree root, Tree_node *p_node)
{
    Tree_node *behind = NULL;
    behind = p_node->right_child;
    if(p_node->right_flag == LINK)
    {
        while(behind->left_flag == LINK)
        {
            behind = behind->left_child;
        }
    }
    return behind;
}
//中序遍历中序线索二叉树
//          A        
//        /   \
//       B     G     
//      / \    / \
//     C   D  H   J  
//        / \  \
//       E   F  I        
//
// 中序: C B E D F A H I G J 
//二.5 遍历输出中序线索二叉树
void mid_order_print_thread(Bin_tree root)             
{                                      //root为中序线索二叉树的头节点
    Tree_node *p = NULL;
    p = root->left_child;              //p指向根节点
    while(p != root)                   //当p不等于指向头节点的指针root时
    {
        while(p->left_flag == LINK)    //寻找中序序列中的第一个节点
        {
            p = p ->left_child;        //最左孩子
        }
        printf("%3c", p->data);        //输出中序序列的第一个节点数据
        while(p->right_flag == THREAD && p->right_child != root)
        {                              //后续线索存在且后续线索不为头节点时
            p = p->right_child;        //根据后继线索找到后继节点
            printf("%3c", p->data);    //输出后继节点信息
        }
        p = p->right_child;            //无后继线索则p指向右孩子节点
    }
}   
//二.6 销毁中序线索二叉树
//以遍历的顺序依次销毁释放资源
void destroy_mid(Bin_tree root)
{
    Tree_node *p_node = NULL;
    Tree_node *pre_node = NULL;                  //用pre_node保存上一个节点
    p_node = root->left_child;
    while(p_node != root)
    {
        while(p_node->left_flag == LINK)
        {
            p_node = p_node->left_child;         //最左孩子
        }
        pre_node = p_node;                       //保存当前节点
        while(p_node->right_flag == THREAD && p_node->right_child != root)
        {
            p_node = p_node->right_child;        //p_node指向新的后继节点后,释放上一个节点
            free(pre_node);
            pre_node = p_node;
        }
        p_node = p_node->right_child;
        free(pre_node);
    }
}
//三.后序线索二叉树
//三.1 后序线索化
//按照"左右根"的顺序进行
void last_thread(Bin_tree tree)
{
    if(tree != NULL)
    {
        last_thread(tree->left_child);
        last_thread(tree->right_child);
        if(tree->left_child == NULL)
        {
            tree->left_child = pre;
            tree->left_flag = THREAD;
        }
        if(pre->right_child == NULL)
        {
            pre->right_child = tree;
            pre->right_flag = THREAD;
        }
        pre = tree;
    }
}
//三.2 创建后序线索二叉树
//创建新节点root指向原来的tree
Bin_tree create_last_thread(Bin_tree tree)
{
    Bin_tree root = NULL;
    root = create_node();                     //新节点root
    root->right_flag = LINK;
    root->right_child = root;
    if(tree == NULL)                          //无二叉树时
    {
        root->left_child = root;
    }
    else
    {
        pre = root;
        root->left_child = tree;              //root指向tree
        root->left_flag = LINK;
        last_thread(tree);                    //后序线索化tree
        root->right_child = pre;
    }
    return root;
}
//在后序线索二叉树中寻找某节点的前驱节点
//由于是后序遍历,以"左右根"的顺序遍历,所以,
//某节点若为根,其right_flag为0,即有右孩子则其right_child即为其前驱.
//否则,找其左孩子.
//三.3 后序线索二叉树中节点的前驱
Bin_tree front_in_last(Bin_tree root, Tree_node *p_node)
{
    Tree_node *front = NULL;
    if(p_node->right_flag == LINK)
    {
        front = p_node->right_child;
    }
    else
    {
        front = p_node->left_child;
    }
    return front;
}
//在后序线索二叉树中寻找某节点的后继节点
//
//          A        
//        /   \
//       B     G     
//      / \    / \
//     C   D  H   J  
//        / \  \
//       E   F  I     
//
// C E F D B I H J G A 
// (左右根)
// 1. 若right_flag == 1, 即为线索,则其right_child即为后继;
// 2. 找到当前节点的父节点,若当前节点为其父节点的右孩子,即此父节点为其后继
// 3. 上图中的B,其后继节点为I,即其兄弟节点左子树里的最深节点
//三.4 后序线索二叉树中节点的后继
Bin_tree behind_in_last(Bin_tree root, Tree_node *p_node)
{
    Tree_node *behind = NULL;
    Tree_node *parent = NULL;
    if(p_node->right_flag == THREAD)      //1. 后继
    {
        behind = p_node->right_child;
    }
    else
    {
        parent = find_parent(root, p_node);
        if(parent->right_child == p_node)
        {
            behind = parent;              //2. 父节点为其后继
        }
        else                              //3. 跨越子树的后继节点
        {
            behind = parent->right_child;
            while(behind->left_flag == LINK || behind->right_flag == LINK)
            {
                if(behind->left_flag == LINK)
                {
                    behind = behind->left_child;
                }
                else
                {
                    behind = behind->right_child;
                }
            }
        }
    }
    return behind;
}
//输出后序线索二叉树
//按"左右根"的顺序,自底向上输出
//          A        
//        /   \
//       B     G     
//      / \    / \
//     C   D  H   J  
//        / \  \
//       E   F  I     
//
// C E F D B I H J G A 
// (左右根)
//                                  取得C,输出C,找到C的父节点B,
// C不是B的右孩子,向下查找,到D,     再到E,输出E,找到E的父节点D,
// E不是D的右孩子,向下查找,         取得F,输出F,找到F的父节点D,
// F为D的右孩子,                    取得D,输出D,找到D的父节点B,
// D为B的右孩子,                    取得B,输出B,找到B的父节点A,
// B不是A的右孩子,向下查找,到G,到H, 取得I,输出I,找到I的父节点H,
// I为H的右孩子,                    取得H,输出H,找到H的父节点G,
// H不是G的右孩子,                  取得J,输出J,找到J的父节点G,
// J为G的右孩子,                    取得G,输出G,找到G的父节点A,
// G为A的右孩子,                    取得A,输出A;  
//三.5 遍历输出后序线索二叉树
void last_order_print_thread(Bin_tree root)
{
    Tree_node *temp = root->left_child;
    Tree_node *parent = NULL;
    while(TRUE)
    {
        while(temp->left_flag == LINK)
        {
            temp = temp->left_child;
        }
        if(temp->right_flag == LINK)
        {
            temp = temp->right_child;
        }
        else
        {
            break;                        //1.找到左子树中最深的节点
        }
    }
    while(temp != root)
    {
        printf("%3c", temp->data);        //2. 输出节点信息 
        parent = get_parent(root, temp);  //3. 获取父节点
        if(parent == root)
        {
            temp = root;                  //完毕
        }
        else if(parent->right_flag == THREAD || temp == parent->right_child)
        {
            temp = parent;                //当前节点为父节点的右孩子
        }
        else
        {
            while(parent->right_flag == LINK)
            {
                parent = parent->right_child;
                while(parent->left_flag == LINK)
                {
                    parent = parent->left_child;
                }
            }
            temp = parent;
        }
    }
}
//三.6 销毁后序线索二叉树
//通过遍历的顺序,依次保存上一个并销毁
void destroy_last(Bin_tree root)
{
    Tree_node *temp = root->left_child;
    Tree_node *parent = NULL;
    while(TRUE)
    {
        while(temp->left_flag == LINK)
        {
            temp = temp->left_child;
        }
        if(temp->right_flag == LINK)
        {
            temp = temp->right_child;
        }
        else
            break;                           //找到最左节点
    }
    while(temp != root)
    {
        parent = get_parent(root, temp);
        if(parent == root)
        {
            free(temp);
            temp = root;
        }
        else if(parent->right_flag == THREAD || temp == parent->right_child)
        {
            free(temp);
            temp = parent;
        }
        else
        {
            while(parent->right_flag == LINK)
            {
                parent = parent->right_child;
                while(parent->left_child == LINK)
                {
                    parent = parent->left_child;
                }
            }
            free(temp);
            temp = parent;
        }
    }
}
