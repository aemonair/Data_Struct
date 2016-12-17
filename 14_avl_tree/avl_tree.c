#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "tools.h"
#include "avl_tree.h"


//创建一个节点
static AVL_node *create_node(void)
{
    AVL_node *result = (AVL_node *)Malloc(sizeof(AVL_node));
    if(result == NULL)
    {
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    bzero(result, sizeof(AVL_node));
    return result;
}
//获取节点结构中的高度变量
static int node_height(AVL_Tree node)
{
    if(node == NULL)
    {
        return -1;
    }
    return node->height;
}
//计算节点的高度
static int avl_node_height(AVL_node *node)
{
    return max(node_height(node->left), node_height(node->right)) + 1;
}

//1.        得到树的高度
int      get_tree_height(AVL_Tree root)    //得到avl树的高度
{
    return node_height(root);
}

//2.        遍历二叉树
void     preorder_avltree(AVL_Tree root)    //2.1前序遍历avl树
{
    if(root != NULL)
    {
        printf("%d ", root->data);
        preorder_avltree(root->left);
        preorder_avltree(root->right);
    }
}

void     inorder_avltree(AVL_Tree root)     //2.2中序遍历avl树
{
    if(root != NULL)
    {
        inorder_avltree(root->left);
        printf("%d ", root->data);
        inorder_avltree(root->right);
    }
}

void     postorder_avltree(AVL_Tree root)   //2.3后序列遍历avl树
{
    if(root != NULL)
    {
        postorder_avltree(root->left);
        postorder_avltree(root->right);
        printf("%d ", root->data);
    }
}
//3.查找数据域为value的节点
//3.1.递归方式查找
AVL_node *find_node(AVL_Tree root, int value)
{
    if(root == NULL || root->data == value)
    {
        return root;
    }
    if(value < root->data)//小于,去左子树
    {
        return find_node(root->left, value);
    }
    else
    {
        return find_node(root->right, value);
    }
}
//3.2.非递归方式查找
AVL_node *find_node_(AVL_Tree root, int value)
{
    AVL_node *p_node = root;
    
    while(p_node != NULL)
    {
        if(p_node->data > value)//如果当前节点的值大于被查找的值，则继续比较当前节点的左孩子
        {
            p_node = p_node->left;
        }
        else if(p_node->data < value)//如果当前节点的值小于被查找的值，则继续比较当前节点的右孩子
        {
            p_node = p_node->right;
        }
        else//当前节点的值符合要求
        {
            return p_node;
        }
    }
    return NULL;
}
//3.3       找到值最大的节点
AVL_node *get_max_node(AVL_Tree root)    //找到值最大的节点
{
    AVL_node *p_node = root;

    while(p_node->right != NULL)//最右节点
    {
        p_node = p_node->right;
    }

    return p_node;
}

//3.4       找到值最小的节点
AVL_node *get_min_node(AVL_Tree root)    //找到值最小的节点
{
    AVL_node *p_node = root;
    
    while(p_node->left != NULL)//最左节点
    {
        p_node = p_node->left;
    }
   
    return p_node;
}

//[单旋]-(左旋)
//              3 node             
//             / \
//            A   5 new_root    5
//               / \           / \
//              B   7         3   7
//                 / \       /\   /\
//                C   D     A B  C  D 
//左旋转：将根节点旋转到（根节点的）右孩子的左孩子位置
//1.new_root 指向根节点(3)的右孩子(5),作为新的根节点;
//2.new_root 的左孩子(B)要作为原根节点node(3)的右孩子(node->right = new_root->left);
//3.new_root 的左孩子指向原node(3);
//4.修改节点高度
static AVL_node *avl_rotate_left(AVL_node *node)
{
    AVL_node *new_root = NULL;
    if(NULL == node)
    {
        return NULL;
    }
    //1.2.3.以此,将根节点旋转到右孩子的左孩子位置,
    new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;

    //4.旋转完后修改当前节点的高度(有顺序要求)
    node->height = avl_node_height(node);
    new_root->height = avl_node_height(new_root);

    return new_root;
}
//[单旋]-(右旋)
//                 5               
//                / \
//               3   A          3    
//              / \            / \
//             2   B          2   5
//            / \            /\   /\
//           D   C          D  C B  A     
//右旋转：将根节点旋转到（根节点的）左孩子的右孩子位置
//1.new_root 指向根节点(5)的左孩子(3),作为新的根节点;
//2.new_root 的右孩子(B)要作为原根节点node(5)的左孩子;
//3.new_root 的右孩子指向原node(5);
//4.修改节点高度
static AVL_node *avl_rotate_right(AVL_node *node)
{
    AVL_node *new_root = NULL;
    if(NULL == node)
    {
        return NULL;
    }
    //1.2.3.以此,将根节点旋转到左孩子的右孩子位置;
    new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;

    //4.旋转完后修改当前节点的高度（右顺序要求）
    node->height = avl_node_height(node);
    new_root->height = avl_node_height(new_root);

    return new_root;
}
//[双旋]-左右旋转(先左后右)
//
//        5                5       
//       / \              / \
//      3   A            4   A         4
//     / \              / \           / \
//    B   4            3   D         3   5
//       / \          / \           /\   /\
//      C   D        B   C         B  C D  A
//1.先对node的左孩子进行左旋;
//2.再对node进行右旋;
static AVL_node *avl_rotate_left_right(AVL_node *node)
{
    node->left = avl_rotate_left(node->left);
    return avl_rotate_right(node);
}
//[双旋]-右左旋转(先右后左)
//
//     3           3
//    / \         / \
//   A   5       A   4                4       
//      / \         / \              / \
//     4   B       D   5            3   5
//    / \             / \          / \ / \
//   D   C           C   B        A  D C  B  
//1.先对node的右孩子进行左旋;
//2.再对node进行左旋;
static AVL_node * avl_rotate_right_left(AVL_node *node)
{
    node->right = avl_rotate_right(node->right);
    return avl_rotate_left(node);
}

//4. 将节点插入到avl树中
AVL_Tree avltree_insert(AVL_Tree root, int data)
{
    int height_diff = 0;

    if(NULL == root) //为空,则创建一个节点作为树
    {
        root = create_node();
        root->data = data;
    }
    else if(data < root->data) //需要插入的值比当前根节点小,向左子树插入
    {
        root->left = avltree_insert(root->left, data);
        height_diff = node_height(root->left) - node_height(root->right);
        //height_different = 左子树-右子树(因为向左插入,左边有可能变高)
        if(height_diff > ONE)//左子树高了
        {
            if(data < root->left->data)//左孩子的左子树,LL
            {
                root = avl_rotate_right(root);
            }
            else//左孩子的右子树,LR
            {
                root = avl_rotate_left_right(root);
            }
        }
    }
    else if(data > root->data) //需要插入的值比当前根节点大,向右子树插入
    {
        root->right = avltree_insert(root->right, data);
        height_diff = node_height(root->right) - node_height(root->left);
        //右高左低
        if(height_diff > ONE)
        {
            if(data > root->right->data)//右孩子的右子树,左旋,RR
            {
                root = avl_rotate_left(root);
            }
            else//右孩子的左子树,RL
            {
                root = avl_rotate_right_left(root);
            }
        }
    }
    else
    {
        //data == root->data,已经存在不进行插入;
        fprintf(stderr, "the tree_node has been exist.\n\n");
    }

    root->height = avl_node_height(root);
    return root;
}

//5.0 删除节点操作
static AVL_Tree delete_node(AVL_Tree root, AVL_node *node)
{
    int        height_diff   = 0   ;
    AVL_node * temp          = NULL;
    AVL_node * p_node        = NULL;
    AVL_node * left_max      = NULL;
    AVL_node * right_min     = NULL;

    if(NULL == root || NULL == node)
    {
        return NULL;
    }

    if(node->data < root->data)//待删除节点在左子树
    {
        root->left = delete_node(root->left, node);//删除操作
        //高度差(需要判断是否大于1即破坏平衡)
        height_diff = node_height(root->right) - node_height(root->left);
        //height_diff > 1则进行相应旋转
        if(height_diff > ONE)
        {
            p_node = root->right;
            if(node_height(p_node->left) > node_height(p_node->right))//RL情况,
            {
                root = avl_rotate_right_left(root);
            }
            else//RR,左旋
            {
                root = avl_rotate_left(root);
            }
        }
    }
    else if(node->data > root->data)//待删除节点在右子树
    {
        root->right = delete_node(root->right, node);
        height_diff = node_height(root->left) - node_height(root->right);
        //破坏了平衡,则进行旋转
        if(height_diff > ONE)
        {
            p_node = root->left;
            //删除了右子树的一个节点,
            //若此时,这棵树不平衡,即看其左子树,
            //若左子树的右子树高于左子树,即,在其左子树上的右子树多出来,即LR
            //否则,左子树的右子树低于左子树,LL,左左,即右旋
            if(node_height(root->right) > node_height(root->left))
            {
                root = avl_rotate_left_right(root);
            }
            else
            {
                root = avl_rotate_right(root);
            }
        }
    }
    else//此root即为需要删除的节点
    {
        //root左右子树都不为空
        //if((root->left != NULL) && (root->right != NULL)) 
        if(root->left && root->right)
        {
            //左子树高于右子树
            //1.找出root左子树中最大值节点
            //2.将该节点点的值赋值给root
            //3.删除该左子树中的那个最大节点
            if(node_height(root->left) > node_height(root->right))
            {
                left_max = get_max_node(root->left);           //1.找最大
                root->data = left_max->data;                   //2.赋值给root
                root->left = delete_node(root->left, left_max);//3.删除最大  
            }
            else//左子树低于右子树
            {
                //1.找出该root右子树中最小节点
                //2.此将最小值赋值给root
                //3.删除该最小节点
                right_min = get_min_node(root->right);           //1.找最小
                root->data = right_min->data;                    //2.赋值给root
                root->right = delete_node(root->right,right_min);//3.删除最小
            }
        }
        else//被删除的节点左右孩子至少一个为空
        {
            temp = root;
            if(root->left != NULL)//左孩子不为空,则指向其左孩子
            {
                root = root->left;
            }
            else              //右孩子不为空,则向下指向其右孩子
            {
                root = root->right;
            }
            free(temp);
        }
    }
    return root;
}
//5.1 调整整个树节点的高度
static int adjust_node_height(AVL_Tree root)
{
    int left_height = 0;
    int right_height = 0;

    if(NULL == root)//为空,返回-1
    {
        return -1;
    }
    else if((NULL == root->left) && (NULL == root->right))//叶子节点,高度为0
    {
        return 0;
    }
    else
    {
        //非叶子节点高度 = 左右子树中最大值 + 1
        left_height = adjust_node_height(root->left);
        right_height = adjust_node_height(root->right);
        return max(left_height, right_height) + 1;
    }
}
//5. AVL树中删除指定数据
AVL_Tree avltree_delete(AVL_Tree root, int data)
{
    AVL_node *node = NULL;

    if((node = find_node(root, data)) != NULL)//找到相应节点
    {
        root = delete_node(root, node);//调用删节点函数
        adjust_node_height(root);
    }
    return root;
}
//6 销毁AVL树
void destroy_avltree(AVL_Tree root)
{
    if(NULL == root)
    {
        return ;
    }

    destroy_avltree(root->left);
    destroy_avltree(root->right);
    free(root);
}
