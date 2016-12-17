#ifndef  _HASH_H_
#define  _HASH_H_

#include "dlist.h"
#include "tools.h"

#define  TRUE  (1)
#define  FALSE (0)

typedef  unsigned char Boolean         ;
typedef  int (*Hash_func)(const void *); //函数指针，指向参数为const void *的函数;

typedef  struct Hash
{
    int   bucket_size  ; //桶的个数
    int   element_count; //哈希表中所有元素个数
    Dlist **table      ; //数据存储的链式结构

    //hash相关函数
    int (*hash_func)(const void *key);
    //匹配函数
    Boolean (*hash_match)(const void *value1, const void *value2);
    //元素的销毁函数
    void (*hash_free)(void *ptr);
}Hash;

//
Hash    *init_hash(int b_size, Hash_func hash_func); //hash表的初始化
void    destroy_hash(Hash **hash)                  ; //hash表的销毁
Boolean hash_search(Hash *hash, const void *value) ; //hash表寻找元素
Boolean hash_insert(Hash *hash, const void *value) ; //hash表插入元素
Boolean hash_remove(Hash *hash, const void *value) ; //hash表移除元素
int     get_hash_element_count(Hash *hash)         ; //hash表元素个数
void    show_hash_table(Hash *hash)                ; //hash表的显示

//hash函数
int int_hash_func(const void *key);
#endif
