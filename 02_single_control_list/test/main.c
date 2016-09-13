#include "list.h"


int main()
{
    int i = 0;
    int num = 0;
    List *list = NULL;
    List *list1 = NULL;
    List *list2 = NULL;
    List_node * node = NULL;
    
    printf("1.init_list:\n");
    list = init_list();
    list1 = init_list();
    list2 = init_list();
    
    printf("3.1 list1 push_front :\n");
    for(i = 0; i < 6; i++)
    {
        push_front(list1, rand()%100);
    }

    show_list(list1);
    

    printf("3.2 list2 push_back:\n");
    for(i = 0; i < 4; i++)
    {
        push_back(list2, rand()%100);
    }
    show_list(list2);


    printf("4.1 list1 pop_front:\n");
    pop_front(list1);
    show_list(list1);

    printf("4.2 list2 pop_back:\n");
    pop_back(list2);
    show_list(list2);
    
    printf("7.1 sort_list1_ascend:\n");                   
    sort_list_ascend(list1);                  
    show_list(list1);
    
    printf("7.2 sort_list2_descend:\n");                   
    sort_list_descend(list2);                  
    show_list(list2);

    printf("12 reverse_list2:\n");
    reverse_list(list2);
    show_list(list2);
    
#if 0
    printf("10. list : merge_two_lists(list1, list2):\n");
    list = merge_two_lists(list1, list2);
    show_list(list);
#endif

#if 1
    printf("11. list : merge_two_lists_recure(list1, list2):\n");
    list = merge_two_lists_recure(list1, list2);
    show_list(list);
#endif
         
    printf("8.1 show_list(list);\n");      
    show_list(list);


    printf("8.2 reverse_show_list(list);\n");
    reverse_show_list(list);
#if 1 
    printf("find_node:\n");
    printf("which one?(value to find)\n"); 
    scanf("%d",&num);
    printf("found num of list is :%d \n",find_node(list, num)->data);
#endif

#if 1
    printf("find_revise_node:\n");     
    printf("which one index ?(reverse)\n"); 
    scanf("%d",&num);
    printf("reverse num of list is :%d \n",find_revise_node(list, num)->data);
#endif
    printf("5.3 find_mid_node(list):\n") ;
    printf("%d \n",find_mid_node(list)->data);

    printf("9. get_list_count:\n"); 
    printf("the count of list is :%d\n", get_list_count(list));

#if 1  
    printf("6.3 delete_one_node:");
    printf("which one?(to delete)\n"); 
    scanf("%d",&num);
    node = create_node();
    node = find_node(list,num);
    delete_one_node(list, node);
    show_list(list);
#endif

#if 1
    printf("6.1 modify_node :\n");
    modify_node(list, 1, 26);
    show_list(list);
#endif

#if 1
    printf("6.2 insert_node: \n");
    insert_node(list, 2, 18);
    show_list(list);
#endif 

#if 1
    printf("16. has_circle:\n");
    //list->head->next->next->next->next->next = list->head->next;

    if(has_circle(list))
    {
        printf("17 find_circle_first_node:\n");
        find_circle_first_node(list);
    }
#endif
    printf("13. list1:list_dump(list)\n");
    list1 = list_dump(list);
    printf("list1: ");
    show_list(list1);
    
    printf("14. is_list_intersect:\n");
    
    if(is_list_intersect(list1, list))
    {
        printf("the common node: %d\n",get_first_common_node(list1, list));
    }

    printf("2. destroy_list:\n");
    destroy_list(&list1);
    destroy_list(&list2);
    destroy_list(&list);
    return 0;
}
