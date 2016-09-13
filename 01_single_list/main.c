#include "slist.h"

#define seed (5)

//主函数-各个函数的测试
int main(int argc, char ** argv)
{
    int i = 0;
    List_head head = NULL;
    head = init_list();
    List_node *node = create_node();
 
    printf("\n头部插入:\n"); 
    for(i = 0 ; i < seed ; i++ )
    {
        push_front(head,rand()%100);
    }
    show_list(head);                   
    
    printf("\n尾部插入:\n"); 
    for(i = 0 ; i < seed ; i++ )
    {
        push_back(head,rand()%100);
    }
    show_list(head);                   

    printf("\n头部删除:\n"); 
    pop_front(head);
    show_list(head);                 
  
    printf("\n尾部删除:\n"); 
    pop_back(head);
    show_list(head);                 
   
    printf("\n插入节点:\n"); 
    insert_node(head, 3, 100);
    show_list(head);                 
    
    find_node(head, 77,&node);

    printf("\n升序排序:\n");
    sort_list_ascend(head);
    show_list(head);                 

    printf("\n降序排序:\n");
    sort_list_descend(head);
    show_list(head); 
               
    printf("\n修改节点数据：\n");
    node = head->next->next; 
    modify_node(node, 777);
    show_list(head); 
    
    printf("\nthe length of this list :%d\n",get_list_length(head));
    
    destroy_list(&head);
    return 0;
}
