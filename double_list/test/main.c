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

    Dlist *dlist = NULL;
    dlist = init_dlist();
    printf("3.push_front(dlist, &a[i]);\n");
    for(i=0; i< sizeof(a)/sizeof(a[0]);++i)
    {
        push_front(dlist, &a[i]);
    }
    show_dlist(dlist, print_int);
    printf("5.pop_front(dlist);\n");
    pop_front(dlist);

    show_dlist(dlist, print_int);
    printf("4.push_back(dlist, &a[i]);\n");
    for(i=0; i< sizeof(a)/sizeof(a[0]);++i)
    {
        push_back(dlist, &a[i]);
    }
    show_dlist(dlist, print_int);
    printf("6.pop_back(dlist);\n");
    pop_back(dlist);
    show_dlist(dlist, print_int);
    
    printf("7.insert_prev(dlist, dlist->head->next->next, &a[4]);\n");
    insert_prev(dlist, dlist->head->next->next, &a[4]);
    show_dlist(dlist, print_int);

    printf("8.insert_next(dlist, dlist->head->next->next, &a[4]);\n");
    insert_next(dlist, dlist->head->next->next, &a[4]);
    show_dlist(dlist, print_int);

    printf("9.remove_dlist_node(dlist, dlist->head->next->next->next);\n");
    remove_dlist_node(dlist, dlist->head->next->next->next);
    show_dlist(dlist, print_int);
   
    get_front(dlist, &value);
    printf("\n11.get_front:\n");
    print_int(value);

    get_tail(dlist, &value);
    printf("\n12.get_tail:\n");
    print_int(value);

    printf("\n13.get_dlist_count:\n");
    printf("%d \n",get_dlist_count(dlist));
    destroy_dlist(&dlist);
    return 0;
}
