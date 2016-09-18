#include <stdio.h>
#include "dlist.h"
/*
void print_int(void *value);
void print_int(void *value)
{
    printf("%d ",*(int *)value);
 }
*/
int main(int argc, char **argv)
{
    int i = 0;
    int a[]={1,2,3,4,5};
    void *value;
    Iterator iter = {0};

    Dlist *dlist = NULL;
    dlist = init_dlist();
    for(i=0; i< sizeof(a)/sizeof(a[0]);++i)
    {
        push_front(dlist, &a[i]);
    }
    show_dlist(dlist, print_int);
    pop_front(dlist);


    printf("---------foreach：\n");
    foreach(iter, dlist)
    {
        print_int(iter.ptr);
    }
    printf("\n");
    show_dlist(dlist, print_int);
    for(i=0; i< sizeof(a)/sizeof(a[0]);++i)
    {
        push_back(dlist, &a[i]);
    }
    show_dlist(dlist, print_int);
    pop_back(dlist);
    show_dlist(dlist, print_int);
    
    insert_prev(dlist, dlist->head->next->next, &a[4]);
    show_dlist(dlist, print_int);

    insert_next(dlist, dlist->head->next->next, &a[4]);
    show_dlist(dlist, print_int);

    remove_dlist_node(dlist, dlist->head->next->next->next);
    show_dlist(dlist, print_int);
   
    get_front(dlist, &value);
    printf("\nfront:\n");
    print_int(value);

    get_tail(dlist, &value);
    printf("\ntail:\n");
    print_int(value);

    printf("the length:\n");
    printf("%d \n",get_dlist_count(dlist));

    foreach(iter, dlist)
    {
        print_int(iter.ptr);
    }
    printf("\n");
 
    destroy_dlist(&dlist);
    return 0;
}
