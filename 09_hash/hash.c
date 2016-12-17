#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dlist.h"
#include "tools.h"

//hash表的初始化
Hash *init_hash(int b_size, Hash_func hash_func)
{
    if(b_size < 0)
    {
        return NULL;
    }
    Hash *hash = (Hash *)Malloc(sizeof(Hash));
    bzero(hash, sizeof(Hash));

    hash->element_count = 0;     
    //hash初始元素个数为0
    hash->bucket_size = b_size;  
    //指定了初始化桶的个数
    hash->table = (Dlist **)Malloc(sizeof(Dlist *) * b_size);
    bzero(hash->table, sizeof(Dlist *)* b_size);
    //先为各个桶申请地址，但不初始化;
    //后面进行插入时再初始化
    hash->hash_func = hash_func;
    hash->hash_match = NULL;
    hash->hash_free = NULL;
    return hash;
}
//2.哈希表的销毁
void    destroy_hash(Hash **hash)                      //哈希表的销毁
{
   int i = 0;
   int bucket_size = 0;
   Hash *p_hash = NULL;
   //   销毁步骤：
   //1. 销毁每一个桶（双端链表）；
   //2. 销毁table；
   //3. 销毁hash；
    if(hash == NULL || *hash == NULL){
        return ;
    }
    p_hash = *hash;
    bucket_size = p_hash->bucket_size;
    for(i = 0; i < bucket_size; ++i){
        destroy_dlist(&(p_hash->table[i]));
    } 
    free(p_hash->table);
    free(p_hash);
    p_hash = NULL;
}
//hash表寻找元素
Boolean hash_search(Hash *hash, const void *value)
{
    if(NULL == hash || NULL == value)
    {
        return FALSE;
    }
    int i = 0;
    int bucket = 0;
    Dlist_node *p_node = NULL;
    //1.通过value和hash_func可以计算value元素应该在哪个桶里
    bucket = hash->hash_func(value) % hash->bucket_size;
    //2.是否存在桶?不存在则返回FALSE
    if(hash->table[bucket] == NULL)
    {
        return FALSE;
    }
    //3.如果存在这样的桶,则遍历链表查找
    for(p_node = hash->table[bucket]->head;
            p_node ; p_node = p_node->next)
    {
        //如果用户设置了匹配方案,则按该方法判断,
        if( hash->hash_match != NULL )
        {
            if(hash->hash_match(p_node->data, value) == TRUE)
            {
                return TRUE;
            }
        }
        else//若用户未设置匹配方法,则直接比较
        {
            if(p_node->data == value)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}
//hash表插入元素
Boolean hash_insert(Hash *hash, const void *value)
{
    //如果hash表不存在或元素已经存在于桶中,则不进行插入
    if(NULL == hash || NULL == value || TRUE == hash_search(hash, value))
    {
        return FALSE;
    }
    int i = 0;
    int bucket = 0;
    //判断元素所在桶的下标
    bucket = hash->hash_func(value) % hash->bucket_size;
    //插入操作时,如果桶不存在,则初始化这个桶
    if(NULL== hash->table[bucket] )
    {
        hash->table[bucket] = init_dlist();
    }
    //通过尾插将元素插入当前桶
    push_back(hash->table[bucket], (void *)value);
    hash->element_count ++;
    return TRUE;
}
//hash表移除元素
Boolean hash_remove(Hash *hash, const void *value)
{
    //如果hash表不存在或元素不存在于桶中,则不进行删除
    if(NULL == hash || NULL == value || FALSE == hash_search(hash, value))
    {
        return FALSE;
    }
    int i = 0;
    int bucket = 0;
    Dlist_node *p_node = NULL;
    //判断元素所在桶的下标
    bucket = (*(int *)value) % hash->bucket_size;
    //遍历链表查找
    for(p_node = hash->table[bucket]->head;
            p_node ; p_node = p_node->next)
    {
        //如果用户设置了匹配方案,则按该方法判断,
        if( hash->hash_match != NULL )
        {
            if(hash->hash_match(p_node->data, value) == TRUE)
            {   
                //先寻找,再删除
                remove_dlist_node(hash->table[bucket], p_node);
                hash->element_count--;
                return TRUE;
            }
        }
        else
        {
            //若用户未设置匹配方法,则直接比较
            if(p_node->data == value)
            {
                remove_dlist_node(hash->table[bucket], p_node);
                hash->element_count--;
                return TRUE;
            }
        }
    }
    return FALSE;
}
//hash表元素个数
int get_hash_element_count(Hash *hash)
{
    if(NULL == hash)
    {
        return -1;
    }
    return hash->element_count;
}
//hash表的显示
void show_hash_table(Hash *hash)
{
    int i = 0;
    int size = hash->bucket_size;
    if(NULL == hash || hash->element_count == ZERO)
    {
        printf("The hash table is NULL.\n");
        return; 
    }
    for(i = 0; i < size; i++)
    {
        if(hash->table[i] != NULL)
        {
            printf("table[%d]: ", i);
            show_dlist((hash->table[i]), print_int);
        }
    }
}
int int_hash_func(const void *key)
{
    return *(int *)key;
}
