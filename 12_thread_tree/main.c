#include <stdio.h>
#include "thread_tree.h"

#define _PRINT_TREE_  1

int main(int argc, char **argv)
{
    Bin_tree root0 = NULL;
    Bin_tree root1 = NULL;
    Bin_tree root2 = NULL;
    Bin_tree root3 = NULL;
    Bin_tree root4 = NULL;
    Bin_tree root5 = NULL;
//  char *str = "ABC####";
    char *str0 = "ABC##DE##F##GH#I##J##";
    char *str1 = "ABCE###DF##G##HI##J##";
    char *str2 = "ABCD###E#F##G#HI##J##";
    Boolean equal = FALSE;

    Tree_node *p_node = NULL;

    printf("\n**********************************************************************************\n");
    printf("一.1.创建二叉树\n");

    root0 = create_tree(&str0);    //二叉树的创建
    root1 = create_tree(&str1);    //二叉树的创建
    root2 = create_tree(&str2);    //二叉树的创建

#if _PRINT_TREE_
    printf("     root0:                root1:                 root2:             \n");   
    printf("                  A                   A               A              \n");
    printf("                /   \\               /   \\           /   \\         \n");
    printf("               B     G             B     H         B     G           \n");
    printf("              / \\    / \\          / \\   /         / \\     \\     \n");
    printf("             C   D  H   J        C   D  I        C   E     H         \n");
    printf("                / \\  \\          /   / \\  \\      /    \\    / \\  \n");
    printf("               E   F  I        E   F   G  J    D      F  I   J       \n");            

    printf("\n**********************************************************************************\n");
#endif

    printf("二.遍历二叉树：\n");
    printf("pre order root0 :\n");
    pre_order_print(root0);
    printf("\n");


    printf("mid order root1 :\n");
    mid_order_print(root1);
    printf("\n");


    printf("last order root2 :\n");
    last_order_print(root2);
    printf("\n");

    printf("\n**********************************************************************************\n");
    printf("\n遍历前序线索二叉树:\n");
    root3 = create_pre_thread(root0);

    pre_order_print_thread(root3);
    printf("\n");

    p_node = root3->left_child->left_child->right_child;
    printf("front is : %c  ,",front_in_pre(root3, p_node)->data);
    printf("The node: %c  ,",p_node->data);
    printf("behind is : %c\n",behind_in_pre(root3, p_node)->data);


    printf("\n遍历中序线索二叉树:\n");
    root4 = create_mid_thread(root1);

    mid_order_print_thread(root4);
    printf("\n");

    p_node = root4->left_child->left_child->right_child;
    printf("front is : %c  ,",front_in_mid(root4, p_node)->data);
    printf("The node: %c  ,",p_node->data);
    printf("behind is : %c\n",behind_in_mid(root4, p_node)->data);

    printf("\n遍历后序线索二叉树:\n");
    root5 = create_last_thread(root2);
    
    last_order_print_thread(root5);
    printf("\n");
    
    p_node = root5->left_child->left_child->right_child;
    printf("front is : %c  ,",front_in_last(root5, p_node)->data);
    printf("The node: %c  ,",p_node->data);
    printf("behind is : %c\n",behind_in_last(root5, p_node)->data);

    //destroy_tree(&root);
    destroy_pre(root3);
    destroy_mid(root4);
    destroy_last(root5);
    printf("\n");
    return 0;
}
