#include <stdio.h>
#include <strings.h>
#include <ctype.h>

#include "gen_list.h"
#include "tools.h"

//非使用者接口操作函数声明

Boolean is_input_empty(char *string);                         // 1. 判断输入串为空
Boolean is_braket_match(char *string);                        // 2. 检测括号是否匹配

char *delete_blank(char *string);                             // 3. 删除字符串中的空格
void delete_braket(char *src_str, char *des_str, int strlen); // 4. 删除字符串两边的括号
void get_item(char *sub_str, char *item_str);                 // 5. 获取当前条目

Gen_node *create_node(void);                                  // 6. 创建空节点
Gen_node *create_head_node(int head_flag);                    // 7. 创建头节点
Gen_node *create_int_node(int head_flag);                     // 8. 创建int型节点
Gen_node *create_char_node(const char character);             // 9. 创建字符节点
Gen_node *create_list_node(Gen_node *p_list);                 //10. 创建子表节点
Gen_list create_genlist(char *string);                        //11. 通过字符串构造广义表


void show_genlist_value(Gen_list gen_list);                   //12. 显示广义表

//非使用者接口函数实现

// 1. 判断输入串为空
Boolean is_input_empty(char *string)
{
    return strlen(string) == ZERO || strcmp(string, "()") == ZERO;
}

// 2. 检测括号是否匹配
Boolean is_braket_match(char *string)
{
    int flag = MATCH;
    int i = 1;

    if(string[0] != '(')
    {
         return NOT_MATCH;
    } 
    flag ++;

    while(string[i] != '\0')
    {
        if(string[i] == '(')
        {
            flag ++;
        }
        else if(string[i] == ')')
        {
            flag --;
        }
        if(flag == MATCH && string[i+1] != '\0')
        {
            return NOT_MATCH;
        }
        i ++;
    } 
 
    return flag == MATCH ? MATCH : NOT_MATCH ;
}

// 3. 删除字符串中的空格
char *delete_blank(char *string)
{
    int i = 0;
    int j = 0;

    if(string == NULL)
    {
        return string;
    }
    while(string[j] = string[i])
    {
        if(isblank(string[i]))
        {
            i++;
            continue;
        }
        i++;
        j++;
    }
    return string;
}


// 4. 删除字符串两边的括号
void delete_braket(char *src_str, char *des_str, int strlen)
{
    strncpy(des_str, src_str + 1, strlen -2 );
    des_str[strlen -2 ] = '\0';
}

// 5. 获取当前条目
void get_item(char *sub_str, char *item_str)
{
    int i = 0;
    int flag = 0;
    int sub_len = strlen(sub_str);

    while(i < sub_len)
    {
        if(sub_str[i] == '(')
        {
            flag++;
        }
        if(sub_str[i] == ')')
        {
            flag--;
        }
        if(flag == 0 && sub_str[i] == ',')
        {
            break;
        }
        i ++;
    }

    if(i == sub_len) //只有一个元素
    {
        strcpy(item_str, sub_str);
        sub_str[0]= '\0';
    }
    else              //把当前元素复制给item_str, 并在原列表删除所复制的元素
    {
        strncpy(item_str, sub_str, i);
        item_str[i] = '\0';
        strcpy(sub_str, sub_str + i +1);
    }
}


// 6. 创建空节点
Gen_node *create_node(void)
{
    Gen_node *result = (Gen_node *)Malloc(sizeof(Gen_node));
    bzero(result, sizeof(Gen_node));

    return result;
}

// 7. 创建头节点
Gen_node *create_head_node(int head_flag)
{
    Gen_node *node = create_node();
    node->n_type = HEAD;
    node->value.head_flag = head_flag;

    return node;
}

// 8. 创建int型节点
Gen_node *create_int_node(int int_value)
{
    Gen_node *node = create_node();
    node->n_type = INT;
    node->value.int_value = int_value;

    return node;
}
// 9. 创建字符节点
Gen_node *create_char_node(const char character)
{
    Gen_node *node = create_node();
    node->n_type = CHARACTER;
    node->value.char_value = character;

    return node;
}
//10. 创建子表节点
Gen_node *create_list_node(Gen_node *p_list)
{
    Gen_node *node = create_node();
    node->n_type = LIST;
    node->value.head = p_list;

    return node;
}

//11. 通过字符串构造广义表
Gen_list create_genlist(char *string)
{
    char *sub_str = NULL;
    char *item_str = NULL;
    int str_len = strlen(string);
    Gen_node *p_node = NULL;

    if(is_input_empty(string) == TRUE)
    {
        fprintf(stderr, "input illegal!\n");
        return NULL;
    }
    
    Gen_list start = create_head_node(1);
    p_node = start;

    sub_str = (char *)Malloc(sizeof(char) * str_len);
    item_str = (char *)Malloc(sizeof(char) * str_len);

    //1.去掉外层括号
    delete_braket(string, sub_str, str_len);
    //2.通过逗号分割广义表元素
    while(strlen(sub_str))
    {
        get_item(sub_str, item_str);
        //3.根据元素类型构造节点（遇到子表递归调用）
        if(item_str[0] != '(' && item_str[0] != '\'')
        {
            p_node->next = create_int_node(atoi(item_str));
        }      
        else if(item_str[0] != '(' && item_str[0] == '\'')
        {
            p_node->next = create_char_node(item_str[1]);
        }      
        else
        {
            p_node->next = create_list_node(create_genlist(item_str));
        }
        p_node = p_node->next;
    }

    free(sub_str);
    free(item_str);

    return start;
}
//12. 显示广义表
void show_genlist_value(Gen_list gen_list)
{
    Gen_node *p_node = NULL;

    if(gen_list == NULL)
    {
    //  printf("NULL\n");
        return ;
    }
    printf("(");
    p_node = gen_list->next;

    while(p_node != NULL)
    {
        if(p_node->n_type == INT)
        {
            printf("%d", p_node->value.int_value);
        }
        else if(p_node->n_type == CHARACTER)
        {
            printf("'%c'", p_node->value.char_value);
        }
        else
        {
            show_genlist_value(p_node->value.head);
        }
        if(p_node->next != NULL)
        {
            printf(",");
        }
        p_node = p_node->next;
    }
    printf(")");
}

//广义表接口实现：
//1.广义表的创建
Gen_list init_genlist(char *input_str)
{
    //判断字符串条件
    if(input_str == NULL || is_input_empty(input_str) == TRUE
    || is_braket_match(input_str) == NOT_MATCH)
    {
        return NULL;
    }
    //删除空格
    delete_blank(input_str);
    //
    //字符串构建广义表
    return create_genlist(input_str);
}

//2.广义表的销毁
void destroy_genlist(Gen_list *gen_list)
{
    Gen_node *p_node = NULL;
    if(gen_list == NULL || *gen_list == NULL)
    {
        return ;
    }

    p_node = *gen_list;
    while(p_node != NULL)
    {
        *gen_list = p_node->next;
        if(p_node->n_type == LIST)
        {
            destroy_genlist(&(p_node->value.head));
        }
        free(p_node);
        p_node = *gen_list;
    }
}
//3.广义表元素个数
int get_genlist_count(Gen_list gen_list)
{
    int count = 0;
    Gen_node *p_node = NULL;

    if(gen_list == NULL)
    {
        return -1;
    }
    p_node = gen_list->next;

    while(p_node != NULL)
    {
        if(p_node->n_type == INT)
        {
            count ++;
        }
        else if(p_node->n_type == CHARACTER)
        {
            count ++;
        }
        else
        {
            count += get_genlist_count(p_node->value.head);
        }
        p_node = p_node->next;
    }
    return count;
}
//4.广义表深度
int get_genlist_depth(Gen_list gen_list)
{
    int count = 0;
    Gen_node *p_node = NULL;

    if(gen_list == NULL)
    {
        return -1;
    }
    p_node = gen_list->next;

    while(p_node != NULL)
    {
        if(p_node->n_type == LIST)
        {
            count += get_genlist_depth(p_node->value.head);
        }
        p_node = p_node->next;
    }
    count++;
    return count;
}
//5.广义表的拷贝
Gen_list copy_genlist(Gen_list gen_list)
{
    Gen_node *p_node = NULL;
    Gen_node *q_node = NULL;
    Gen_list new_list = (Gen_list)Malloc(sizeof(gen_list));
    bzero(new_list, sizeof(gen_list));

    if(gen_list == NULL)
    {
      printf("NULL\n");
        return NULL;
    }
    p_node = gen_list->next;
    q_node = new_list;

    while(p_node != NULL)
    {
        if(p_node->n_type == INT)
        {
            q_node->next = create_int_node(p_node->value.int_value);
        }
        else if(p_node->n_type == CHARACTER)
        {
            q_node->next = create_char_node(p_node->value.char_value);
        }
        else
        {
            q_node->next = create_list_node(p_node->value.head);
        }
        p_node = p_node->next;
        q_node = q_node->next;
    }
    q_node = NULL;

    return new_list;
}
//6.显示广义表信息

void show_genlist(Gen_list gen_list)
{
    show_genlist_value(gen_list);
    printf("\n");
}

