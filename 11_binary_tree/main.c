#include <stdio.h>
#include "binary_tree.h"

int main(int argc, char **argv)
{
    Bin_tree root = NULL;
    Bin_tree root1 = NULL;
    Bin_tree root2 = NULL;
    Bin_tree root3 = NULL;
    Bin_tree root4 = NULL;
    Tree_node *find = NULL;
    char *str = "ABC##DE##F##GH#I##J##";
    char *pre  = "ABCDEFGHIJ";
    char *mid  = "CBEDFAHIGJ";
    char *last = "CEFDBIHJGA";
    ////////1
    char *str1 = "ABCK##L##DE##F##GH##J##";
    char *str4 = "BC##D##";
    Boolean equal = FALSE;


    printf("\n**********************************************************************************\n");
    printf("一.1.创建二叉树\n");

    root = create_tree(&str);    //二叉树的创建
    root1 = create_tree(&str1);
    root2 = create_tree_by_pre_mid(pre, mid, strlen(pre));
    root4 = create_tree(&str4);
    //root1 = create_tree_by_mid_last(mid, last, strlen(pre));

    printf("     root,root2:                root1:          root4:       \n");   
    printf("                  A                   A                      \n");
    printf("                /   \\               /   \\                  \n");
    printf("               B     G             B     G           B       \n");
    printf("              / \\    / \\          / \\   / \\         / \\ \n");
    printf("             C   D  H   J        C   D  H   J      C   D     \n");
    printf("                / \\  \\          /\\  /\\                   \n");
    printf("               E   F  I        K  L E F                      \n");            


    printf("\n**********************************************************************************\n");
    printf("二.遍历二叉树：\n");
    printf("pre order root:\n");
    pre_order_print(root);
    printf("\n");
  
    printf("pre order nr root:\n");
    pre_order_print_nr(root);
    printf("\n");

    printf("mid order root:\n");
    mid_order_print(root);
    printf("\n");

    printf("mid order nr root:\n");
    mid_order_print_nr(root);
    printf("\n");

    printf("last order root:\n");
    last_order_print(root);
    printf("\n");

    printf("last order nr root:\n");
    last_order_print_nr(root);
    printf("\n");

    printf("last order root1:\n");
    last_order_print(root1);
    printf("\n");

    printf("last order nr root1:\n");
    last_order_print_nr(root1);
    printf("\n");

    printf("level order root1:\n");
    level_order_print(root1);
    printf("\n");


    printf("\n**********************************************************************************\n");
    printf("三.二叉树的变量:\n");

    printf("mid order root :\n");
    mid_order_print(root);
    printf("\n");

    printf("mid order coped root2:\n");
    mid_order_print_nr(root2);
    printf("\n");
   
    //得到二叉树高度
    printf("the height of root2:%d\n", get_binarytree_height(root2));
    //得到二叉树节点个数
    printf("the count of root2:%d\n", get_binarytree_node_count(root2));
    //得到二叉树叶子节点个数
    printf("the leaves count of root2:%d\n", get_binarytree_leaf_count(root2));
    //得到二叉树的最大路径
    printf("the largest dir count of root2:%d\n", get_largest_dir_count(root2));
    //得到第n层二叉树的节点个数
    printf("the %d level count is:%d\n", 3, get_binarytree_level_count(root, 3));
    //得到二叉树镜像
    printf("pre order root2:\n");
    pre_order_print_nr(root2);
    swap_left_right(root2);
    printf("\nswap pre order root2:\n");
    pre_order_print_nr(root2);
    printf("\n");
    //二叉树的拷贝 
    root3 = copy_binary_tree(root1);    
    printf("root3 = copy_binary_tree(root1)\n");
    printf("mid order root1 :\n");
    mid_order_print(root1);
    printf("\n");
    printf("mid order root3 :\n");
    mid_order_print(root3);
    printf("\n");

    printf("\n**********************************************************************************\n");
    printf("四.二叉树的性质：\n");
    printf("     root,                    root2:              root1,root3:    root4:            \n");   
    printf("                  A         |       A                  A                            \n");
    printf("                /   \\       |     /   \\              /   \\                       \n");
    printf("               B     G      |    G     B            B     G           B             \n");
    printf("              / \\    / \\    |   / \\    / \\         / \\   / \\         / \\     \n");
    printf("             C   D  H   J   |  J   H  D   C       C   D  H   J      C   D           \n");
    printf("                / \\  \\      |     /  / \\         /\\  /\\                        \n");
    printf("               E   F  I     |    I   F  E       K  L E F                            \n");            

    //判断是否是满二叉树
    if(is_full_binary_tree(root1) == TRUE){
        printf("root1 is full!\n");
    }else{
        printf("root1 is not full!\n");
    }
    //判断是否完全二叉树
    if(is_complete_binary_tree(root1) == TRUE){
        printf("root1 is complete!\n");
    }else{
        printf("root1 is not complete!\n");
    }
    //判断是否平衡二叉树
    if(is_balance_binary_tree(root1) == TRUE){
        printf("root1 is balance!\n");
    }else{
        printf("root1 is not balance!\n");
    }
    //判断二叉树是否包含
    printf("mid order root  :\n");
    mid_order_print(root);
    printf("\n");
    printf("mid order root4 :\n");
    mid_order_print(root4);
    printf("\n");
    if(is_include_tree(root, root4) == TRUE){
        printf("root4 is include root!\n");
    }else{
        printf("root1 is not include!\n");
    }
    //判断二叉树是否相等
    if((equal = is_binarytree_equal(root1, root3)) == TRUE)
    {
        printf("root1 root3 two trees are equal!\n");
    }

    printf("\n**********************************************************************************\n");
    printf("五.二叉树的查找\n");
    //找到值所在节点
    printf("mid order root  :\n");
    mid_order_print(root);
    printf("\n");
    if((find = find_value(root, 'H')) == NULL){
        printf("H is not found!\n");
    }else{
        printf("%c is found!\n", find->data);
    }
 
    Tree_node *find1 = find_value(root, 'B');
    Tree_node *find2 = find_value(root, 'I');
    //找到两个节点的最近公共祖先
    Tree_node *parent = find_common_node(root, find1, find2);
    
    if(parent != NULL){ 
        printf("(%c and %c) parent is:%c\n",
            find1->data, find2->data, parent->data);
    }else{
        printf("not have parent!\n");
    }

    printf("\n**********************************************************************************\n");
    destroy_tree_nr(&root);
    destroy_tree_nr(&root1);
    destroy_tree_nr(&root2);
    destroy_tree_nr(&root3);
    destroy_tree_nr(&root4);
    return 0;
}
