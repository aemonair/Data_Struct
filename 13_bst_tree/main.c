#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"
#include "tools.h"

int main(int argc, char **argv)
{
    BSTree *root = NULL;
    Tree_node * x = NULL;
    int a[]=
    //{1,2,3,4,5,6};
    //int a[]={3, 1, 4};
    {8, 3, 10, 1, 6, 14, 4, 7, 13};
    //{1, 2, 3, 4, 5, 6, 7};
    int length = sizeof(a)/sizeof(a[0]);
    printf("length:%d\n", length);

    root = BSTree_create(a, length);

    //                        8
    //                      /   \
    //                     3    10
    //                    / \     \
    //                   1   6    14
    //                      / \   /
    //                     4   7 13
    //
    printf("%d ", root->data);
    printf("%d ", root->left_child->data);
    printf("%d \n", root->right_child->data);

    if(x = BSTree_search(root, 3))
    {
        printf("search: %d\n", x->data);
    }
    if(x = BSTree_search(root, 4))
    {
        printf("search: %d\n", x->data);
    }
    if(x = BSTree_search(root, 5))
    {
        printf("search: %d\n", x->data);
    }

    printf("max: %d.", BSTree_max(root)->data);
    printf("min: %d.\n", BSTree_min(root)->data);

    printf("parent:%d\n",find_parent(root, BSTree_search(root, 1))->data);
    printf("parent:%d\n",find_parent(root, BSTree_search(root, 3))->data);

    mid_order_print(root);
    printf("\ndelete 8\n");
    BSTree_delete(root, 8);
    mid_order_print(root);
    printf("\ninsert 3\n");
    BSTree_insert1(&root, 3);
    printf("%d ", root->left_child->left_child->data);
    printf("max: %d.", BSTree_max(root)->data);
    printf("min: %d.\n", BSTree_min(root)->data);

    mid_order_print(root);
    printf("\n");
    BSTree_destroy(&root);
    return 0;
}

