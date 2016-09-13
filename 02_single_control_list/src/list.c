#include "list.h"

//1.//链表的初始化
List      *init_list(void)                            
{
    List *list = (List *)Malloc(sizeof(List));

    //      | head | tail | count |
    //          \      /      0
    //           \    /
    //            NULL
    bzero(list, sizeof(List));

    return list; 
}

//2.//链表的销毁
void      destroy_list(List **list)                   
{

    //              list
    //             /
    //         list_head  
    //          /
    //      | head | tail | count |
    //          \      \       n + 1
    //             
    //            \           \
    //            node->node2->node3
    if(list == NULL || *list == NULL){
        return ;
    }
   
    //  链表删除步骤：
    //  1.删除链表节点信息;
    while((*list)->count){   //头部删除链表节点
        pop_front(*list);
    }
    //  2.删除链表控制信息.
    free(*list);
    *list = NULL;
}


//3.1/头部插入
Boolean   push_front(List *list, int value)           
{
    List_node *node = NULL;
  
    if(list == NULL){ 
        return FALSE;
    }   

    //创建节点并赋值
    node = create_node();
    node->data = value;

    //   case1:
    //      | head | tail | count |
    //          \      /      1
    //           \    /
    //            node
    if(list->count == ZERO){
        list->tail = node;
    }else{
    //   case2:
    //      | head |              tail | count |
    //          \                 /       n + 1
    //           \               /
    //            node->node2->node3
        node->next = list->head;
    }
    list->head = node;
    list->count++;
    return TRUE;
}

//3.2//尾部插入
Boolean   push_back(List  *list, int value)           
{
    List_node *node = NULL;

    if(list == NULL){
        return FALSE;
    }
  
    node = create_node();
    node->data = value;

    //   case1:
    //      | head | tail | count |
    //          \      /      1
    //           \    /
    //            node
    if(list->count == ZERO){
       list->head = list->tail = node;
    }else{
        //   case2:
        //      | head |              tail | count |
        //          \                 /       n + 1
        //           \               /
        //            node1->node2->node
        list->tail->next = node;
        list->tail = node;
    }
    list->count++;
    return TRUE;
}

//4.1  //头部删除
Boolean   pop_front(List *list)                     
{
    List_node *p_node = NULL;

    if(list == NULL || list->count == ZERO){
        return FALSE;
    }

    //   case1:
    //      | head | tail | count |
    //          \      /      1->0
    //           \    /
    //            node
    
    //   case2:
    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    p_node = list->head;
    if(list->count == ONLY_ONE){
        list->head = list->tail = NULL; 
    }else{
        list->head = list->head->next;
    }
    free(p_node);
    list->count--;
    return TRUE;
}


//4.2    //尾部删除
Boolean   pop_back(List *list)                    
{
    List_node *p_node = NULL;

    if(list == NULL || list->count == ZERO){ 
        return FALSE;
    }
   
    //   case1:
    //      | head | tail | count |
    //          \      /      1->0
    //           \    /
    //            node
    
    //   case2:
    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    p_node = list->head; 
    if(list->count == ONLY_ONE){    
        list->head = list->tail = NULL;
        free(p_node);
    }else{
        //判断倒数第二个？
        //   p_node->next == list->tail
        while(p_node->next != list->tail){
            p_node = p_node->next;
        }
        free(list->tail);
        list->tail = p_node;
        p_node->next = NULL;
    }
    list->count--;
    return TRUE;
}

//5.1//链表的查找
List_node *find_node(List *list, int value)
{
    if(list == NULL)
    {
        return NULL;
    }
    List_node *p = list->head;
    while(p != NULL)
    {
        if(p->data == value)
        {
            printf("found the value: %d\n", value);
            return p;
        }
        p = p->next;
    }
    printf("No found!");
    return NULL;
}

//5.2//找到链表的倒数第num个节点
List_node *find_revise_node(List *list, int num)   
{
    List_node *move = NULL;
    int move_count = 0;
    //     10   23   5   15    50    67   45   32  
    if(list == NULL || num <= 0 || num > list->count){
        return NULL;
    }    

    move = list->head;
    //移动的步长
    move_count = list->count - num;

    while(move_count--){
        move = move->next;
    }

    return move;
}
//5.3//找到链表的中间节点
List_node *find_mid_node(List *list)    
{
    // 1. 快慢指针：
    //
    // f  每次移动2步， s 每次移动1步
    //     10   23  5  15  50  67  45  32  82
    //
    // 2. 8 / 2 = 4
    List_node *move = NULL;
    int move_count = 0;

    if(list == NULL){
        return NULL;
    }

    move = list->head;
    move_count = list->count >> 1;

    //   0000 1010   10
    //       10 >> 1
    //   0000 0101   5
    while(move_count--){
        move = move->next;
    }

    return move;
}
//6.1//链表节点的修改
void modify_node(List *list, int index, int value)
{
    int count = index;
    List_node *p = list->head;
    if(list == NULL || index >= list->count || index < 0)
    {
        return ;
    }
    while(count--)
    {
        p = p->next;
    }
    p->data = value;
}
//6.2链表节点的插入
Boolean insert_node(List *list,int index, int value)
{
    if(list == NULL || index > list->count || index < 0)
    {
        return FALSE;
    }
    if(index == list->count)
    {
        return push_back(list, value);
    }
    if(index == 0)
    {
        return push_front(list, value);
    }
    int count =  index -1;
    List_node *p_node = list->head;
    List_node *node = create_node();
    node->data = value;

    while(count--)
    {
        p_node = p_node->next;
    }

    node->next = p_node->next;
    p_node->next = node;

    list->count++;
    return TRUE;
}

//6.3 //在O（1）的时间复杂度删除节点
void      delete_one_node(List *list, List_node *node)   
{
    if(node == list->tail)
    {
        pop_back(list);
        return ;
    }
    List_node *p = node->next;

    node->data = node->next->data;
    node->next = node->next->next;
    free(p);
    list->count--;
}

//7.1//升序排列
void      sort_list_ascend(List *list)                
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    unsigned long data_size = 0;

    if(list == NULL || list->count < TWO){
        return ;
    }
 // List_node *p = list->head;

 // p->next = NULL;

 // ((unsigned long)&(((List_node *)0)->next))

 // sizeof(List_node) - sizeof(List_node *);
 
   
    // int               data;  // 0   1   2   3
    //                          // 4   5   6   7
    // struct List_Node *next;  // 8   9  10  11
    //                            12  13  14  15
    //

    data_size = get_data_size();    //求得数据区域得大小
    for(p_node = list->head; p_node->next; p_node = p_node->next){
        for(q_node = p_node->next; q_node ; q_node = q_node->next){
            if(p_node->data > q_node->data){ 
                swap(p_node, q_node, data_size);                
            }
        }
    }
}


//7.2//降序排列
void      sort_list_descend(List *list)               
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    unsigned long data_size = 0;

    if(list == NULL || list->count < TWO){
        return ;
    }
 // List_node *p = list->head;

 // p->next = NULL;

 // ((unsigned long)&(((List_node *)0)->next))

 // sizeof(List_node) - sizeof(List_node *);
 
   
    // int               data;  // 0   1   2   3
    //                          // 4   5   6   7
    // struct List_Node *next;  // 8   9  10  11
    //                            12  13  14  15
    //

    data_size = get_data_size();    //求得数据区域得大小
    for(p_node = list->head; p_node->next; p_node = p_node->next){
        for(q_node = p_node->next; q_node ; q_node = q_node->next){
            if(p_node->data < q_node->data){ 
                swap(p_node, q_node, data_size);                
            }
        }
    }
}

//8.1//8.1显示链表信息
void      show_list(List *list)                       
{
    List_node *p_node = NULL;

    if(list != NULL && list->count != ZERO){ 
        for(p_node = list->head; p_node; p_node = p_node->next){ 
            printf("%d ", p_node->data);
        }
        printf("\n");
    }
}
//8.2//逆序输出链表信息
void      reverse_show_list(List *list)    
{
    if(list == NULL || list->count == ZERO){
        return ;
    }  
    Rev_show_list(list->head);
    printf("\n");
}



//9//得到链表节点数量
int       get_list_count(List *list)                  
{
    if(list == NULL){ 
        return -1;
    }
    return list->count;
}

//   char *str1 = (char *)malloc(20);
//   strcpy(str1, "hello,world");
//
//   char *str2 = str1;
//   free(str1);
//
//   *str2  = 'c';

///10/合并两个有序链表
List      *merge_two_lists(List *list1, List *list2)    
{
    List *result = NULL;
    List_node *list1_move = NULL;   
    List_node *list2_move = NULL;   
#if 0
    if(list1 == NULL){
        return result = copy_list_by_ctl(list2);
    }else if(list2 == NULL){
        return result = copy_list_by_ctl(list1);
    }
#endif
    if(list1 == NULL || list2 == NULL){
        return result;
    }

    result = init_list();   //结果链表得初始化

    list1_move = list1->head;
    list2_move = list2->head;

    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    //
    //
    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    //


    //如果两个链表都没有遍历完，进行比较
    while(list1_move != NULL && list2_move != NULL){
        if(list1_move->data <= list2_move->data){
            push_back(result, list1_move->data);
            list1_move = list1_move->next;
        }else{
            push_back(result, list2_move->data);
            list2_move = list2_move->next;
        }
    }

    //当两个链表中任何一个遍历结束，则把另外一个进行尾部添加
    while(list2_move != NULL){
        push_back(result, list2_move->data);
        list2_move = list2_move->next;
    }

    while(list1_move != NULL){
        push_back(result, list1_move->data);
        list1_move = list1_move->next;
    }

    return result;
}


//11//合并两个有序链表（递归）
List      *merge_two_lists_recure(List *list1, List *list2)    
{
    List *node = NULL;
    List *l  = init_list();
    List *l1 = list1;
    List *l2 = list2;

    if(l1->count == 0)
    {
        return list2;
    }
    if(l2->count == 0)
    {
        return list1;
    }

    if(l1->head->data < l2->head->data)
    {
        l->head = l1->head;
        l1->head = l1->head->next;
        l1->count --;
        node = merge_two_lists_recure(l1, l2);
    }
    else
    {
        l->head = l2->head;
        l2->head = l2->head->next;
        l2->count--;
        node = merge_two_lists_recure(l1, l2);
    }
    l->head->next = node->head;
    l->count = node->count +1;
    return l;
}








//12//逆置一个链表
List      *reverse_list(List *list)    
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    List_node *m_node = NULL;


    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    if(list == NULL || list->count < TWO){
        return list;
    } 
    //两个节点
    if(list->count == TWO){
        list->tail->next = list->head;
        list->head->next = NULL;
    }else{    //三个节点
        p_node = list->head;
        q_node = p_node->next;
        m_node = q_node->next;
        p_node->next = NULL;
        do{
            q_node->next = p_node;   //让中间指针的next指向前一个
            p_node = q_node;    //指针整体向后搬移
            q_node = m_node;
            m_node = m_node->next;
        }while(m_node != NULL);
        q_node->next = p_node;
    }
    //交换头尾指针
    swap(&(list->head), &(list->tail), sizeof(List_node *));
    return list;
}
//13//链表的拷贝
List      *list_dump(List *list)    
{
    List * new_list = init_list();
    List_node * node = list->head;
    for(node = list->head; node; node = node->next)
    {
        push_back(new_list, node->data);
    }
    return new_list;
}

//14//判断链表是否有交点
Boolean   is_list_intersect(List *list1, List *list2)    
{
    if(list1 == NULL || list2 == NULL){
        return FALSE;
    }
//    
    if( list1->tail == list2->tail)
    {
        printf("intersect\n");
        return TRUE;
    }
    else
    {
        printf("nothing\n");
        return FALSE;
    }
}


//15//得到第一个交点
List_node *get_first_common_node(List *list1, List *list2)    
{
    int list1_len = 0;
    int list2_len = 0;
    int distance = 0;
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    

    if(!is_list_intersect(list1, list2)){    //判断两个链表是否有交点
        return NULL;
    }
   
    list1_len = list1->count;
    list2_len = list2->count;

    p_node = list1->head;
    q_node = list2->head;

    //判断较长链表并首先进行移动
    if(list1_len >= list2_len){
        distance = list1_len - list2_len;
        while(distance--){ 
            p_node = p_node->next;
        }
    }else{
        distance = list2_len - list1_len;
        while(distance--){
            q_node = q_node->next;
        }
    }

    //依次对对应节点进行判断是否相等，如果相等则是第一个相交节点
    while(p_node != q_node){
        p_node = p_node->next;
        q_node = q_node->next;
    }
   
    return p_node;
}

//16//判断一个链表是否有环
Boolean has_circle(List *list)                                
{
    List_node *p = list->head;
    List_node *q = list->head;
    while(p != NULL && q != NULL && q->next !=NULL)
    {
        p = p->next;
        q = q->next->next;
        if(p == q)
        {
            printf("we found circle!\n");
            return TRUE;
        }
    }
    printf("no circle!\n");
    return FALSE;
}
//17//找到带环链表的环入口节点
List_node *find_circle_first_node(List *list)                  
{
    List_node * entry = NULL;
    if(!has_circle(list))
    {
        return NULL;
    }
    List_node *p = list->head;
    List_node *q = list->head;
    while(p != NULL && q != NULL && q->next !=NULL)
    {
        p = p->next;
        q = q->next->next;
        if(p == q)
        {
            break;
        }
    }
    q = list->head;
    while(q != p)
    {
        p =p->next;
        q =q->next;
    }
    printf("we found the node is %d\n", q->data);
    return q;
}
