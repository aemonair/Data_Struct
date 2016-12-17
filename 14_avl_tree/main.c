#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

#define COUNT (10)

int main(int argc, char **argv)
{
    int          i = 0   ;
    int      value = 0   ;
    AVL_Tree  root = NULL;
    AVL_node *find = NULL;

    for(i = 0; i < COUNT; ++i)
    {
        value = rand() % (COUNT*COUNT);
        root = avltree_insert(root, value);
        inorder_avltree(root);
        printf("\n");
        if(i == COUNT/2)
        {
            printf("the tree height is: %d\n", get_tree_height(root));
            printf("the max value in tree: %d,\n", get_max_node(root)->data);
            printf("the min value in tree: %d .\n", get_min_node(root)->data);
        }
    }
    printf("then insert %d in avl_tree :\n", COUNT);
    avltree_insert(root, COUNT);
    inorder_avltree(root);
    printf("\n");
    printf("then the max value in avltree: %d,\n", get_max_node(root)->data);
    printf("then the min value in avltree: %d .\n", get_min_node(root)->data);
    printf("\n");
    if((find = find_node(root, COUNT)))
    {
        printf("we find the %d\n", find->data);
    }
    printf("then we delete %d node:\n", COUNT);
    avltree_delete(root, COUNT);
    inorder_avltree(root);
    printf("\n");
    printf("and then the tree height is:%d\n", get_tree_height(root));
    printf("inorder:");
    inorder_avltree(root);
    printf("\n");
    printf("preorder: ");
    preorder_avltree(root);
    printf("\n");
    printf("postorder: ");
    postorder_avltree(root);
    printf("\n");

    printf("destroy\nthis\ntree\n");
    destroy_avltree(root);
}
