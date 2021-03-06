#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "iterator.h"

#define TRUE       (1)
#define FALSE      (0)
#define MODE_SIZE  (32)
#define ZERO       (0)

typedef unsigned char Boolean;
typedef struct Array Array;

struct Array
{
    void  **data;    //1.存储实体
    int capacity;    //2.动态数组申请大小
    int    count;    //3.当前元素个数

    //4.拷贝函数指针
    void *(*copy)(void *src_value);
    //5.匹配函数指针
    Boolean (*match)(void *value1, void *value2);
    //6.释放函数指针
    void (*free)(void *ptr);
    
    //7.头部插入
    Boolean (*push_front)(Array *array, void *value);
    //8.尾部插入
    Boolean (*push_back)(Array *array, void *value);
    //9.头部删除
    Boolean (*pop_front)(Array *array);
    //10.尾部删除
    Boolean (*pop_back)(Array *array);
    //
    //迭代器操作
    //11.指向数组头部的位置
    void *(*iter_head)(Iterator *iter, Array *array);
    //12.指向数组尾部的位置
    void *(*iter_tail)(Iterator *iter, Array *array);
    //13.指向后一个元素的位置
    void *(*iter_next)(Iterator *iter, Array *array);
    //14.指向前一个元素的位置
    void *(*iter_prev)(Iterator *iter, Array *array);
};

//动态数组接口
//1.初始化
Array *init_array(int init_size);
//2.销毁
void destroy_array(Array **array);
//3.清空
void clean_array(Array *array);
//4.插入到指定下标的前面
Boolean array_insert_prev(Array *array,
                         int index, void *value);
//5.插入到指定下标的后面
Boolean array_insert_next(Array *array,
                         int index, void *value);
//6.得到数组个数
int get_array_count(Array *array);
//7.得到指定下标元素
void *get_index_value(Array *array, int index);
//8.删除指定下标元素
Boolean delete_index_value(Array *array, int index);
//9.删除指定下标范围的元素
Boolean delete_range_value(Array *array, int begin, int end);
//10.查找指定元素的下标
int find_array_value(Array *array, void *value);

#endif

