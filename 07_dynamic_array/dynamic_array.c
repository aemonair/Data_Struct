#include "dynamic_array.h"
#include "tools.h"

static Boolean array_push_front(Array *array, void *value);
static Boolean array_push_back(Array *array, void *value);
static Boolean array_pop_front(Array *array);
static Boolean array_pop_back(Array *array);

static void *array_iter_head(Iterator *iter, Array *array);
static void *array_iter_tail(Iterator *iter, Array *array);
static void *array_iter_next(Iterator *iter, Array *array);
static void *array_iter_prev(Iterator *iter, Array *array);

static void array_grow(Array *array, int size);
static int  adjust_size(int size);

static int  adjust_size(int size)
{
    size += (MODE_SIZE -1);
    size /= (MODE_SIZE);
    size *= (MODE_SIZE);

    return size;
}
static void array_grow(Array *array, int size)
{
    int adjust = 0;

    if(array->capacity < size)
    {
        adjust = adjust_size(size);
        array->capacity = adjust;

        if(array->data != NULL)
        {
            array->data = Realloc(array->data,
                              sizeof(void *)*adjust);
        }
        else
        {
            array->data = Malloc(sizeof(void *)*adjust);
        }
    }
}
static Boolean array_push_front(Array *array, void *value)
{
    return array_insert_prev(array, 0, value);
}
static Boolean array_push_back(Array *array, void *value)
{
    if(array ==NULL || value == NULL)
    {
        return FALSE;
    }

    //如果数组容量不够，增长
    if(array->count >= array->capacity)
    {
        array_grow(array, array->count + MODE_SIZE);
    }

    array->data[array->count] = value ;
    array->count ++;

    return TRUE;
}
static Boolean array_pop_front(Array *array)
{
    int i =0 ;
    void *delete = NULL;
  
    if(array == NULL || array->count == ZERO)
    {
        return FALSE; 
    }
    array->count -- ;
  
    delete = array->data[0];
    if(array->free != NULL)
    {
        array->free(delete);
    }

    while(i < array->count)
    {
        array->data[i] = array->data[i+1];
        ++i;
    }

    array->data[i] = NULL;
    return TRUE;
}
static Boolean array_pop_back(Array *array)
{
    void *delete = NULL;
    if(array == NULL || array->count == ZERO)
    {
        return FALSE; 
    }
    array->count -- ;
    delete = array->data[array->count];
    if(array->free != NULL)
    {
        array->free(delete);
    }
    
    array->data[array->count] = NULL;
    return TRUE;

}


static void *array_iter_head(Iterator *iter, Array *array)
{
    if(iter == NULL || array == NULL)
    {
        return NULL;
    }
    iter->index = 0;
    iter->size = array->count;
    if(array->data == NULL || array->count == ZERO)
    {
        iter->ptr = NULL;
    }
    else
    {
        iter->ptr = array->data[0];
    }
    return iter->ptr;
}
static void *array_iter_tail(Iterator *iter, Array *array)
{
    if(iter == NULL || array == NULL)
    {
        return NULL;
    }
    iter->index = array->count -1;
    iter->size = array->count;
    if(array->data == NULL || array->count == ZERO)
    {
        iter->ptr = NULL;
    }
    else
    {
        iter->ptr = array->data[iter->index];
    }
    return iter->ptr;
}
static void *array_iter_next(Iterator *iter, Array *array)
{
    if(iter == NULL || array == NULL)
    {
        return NULL;
    }
    iter->index ++;
    iter->size = array->count;
    if( iter->index >= iter->size)
    {
        iter->ptr = NULL;
    }
    else
    {
        iter->ptr = array->data[iter->index];
    }
    return iter->ptr;
}
static void *array_iter_prev(Iterator *iter, Array *array)
{
    if(iter == NULL || array == NULL)
    {
        return NULL;
    }
    iter->index --;
    iter->size = array->count;
    if( iter->index <= ZERO)
    {
        iter->ptr = NULL;
    }
    else
    {
        iter->ptr = array->data[iter->index];
    }
    return iter->ptr;
}
//动态数组接口
//1.初始化
Array *init_array(int init_size)
{
    Array *array = (Array *)Malloc(sizeof(Array));
    //控制信息初始化
    array->count = 0;

    array->free = NULL;
    array->match = NULL;
    array->copy = NULL;

    array->push_front = array_push_front;
    array->push_back  =  array_push_back;
    array->pop_front  =  array_pop_front;
    array->pop_back   =   array_pop_back;

    array->iter_head = array_iter_head;
    array->iter_tail = array_iter_tail;
    array->iter_next = array_iter_next;
    array->iter_prev = array_iter_prev;

    array->data = NULL;
    array->capacity = 0;

    if(init_size > 0)
    {
        array_grow(array, init_size);
    }
    return array;
}
//2.销毁
void destroy_array(Array **array)
{
    if(array == NULL)
    {
        return ;
    }
    delete_range_value(*array, 0, get_array_count(*array));

    free(*array);
    *array = NULL;
}
//3.清空
void clean_array(Array *array)
{
    if(array == NULL)
    {
        return ;
    }
    int i = 0 ;
    while(i < array->count)
    {
        array->data[i] =  NULL;
        ++i;
    }
}
//4.插入到指定下标的前面
Boolean array_insert_prev(Array *array, int index, void *value)
{
    int i = 0;
    if(array == NULL || value == NULL
                     || index > get_array_count(array))
    {
        return FALSE;
    }

    //如果数组容量不够，增长
    if(array->count+1 >= array->capacity)
    {
        array_grow(array, array->count + MODE_SIZE);
    }
    i = array->count;
    while(i > index)
    {
        array->data[i] = array->data[i-1];
        --i;
    }
    array->count ++;
    array->data[i] = value;
    return TRUE;
}
//5.插入到指定下标的后面
Boolean array_insert_next(Array *array,
                         int index, void *value)
{
    int i = 0;
    if(array == NULL || value == NULL
                     || index > get_array_count(array))
    {
        return FALSE;
    }

    //如果数组容量不够，增长
    if(array->count+1 >= array->capacity)
    {
        array_grow(array, array->count + MODE_SIZE);
    }
    i = array->count;
    while(i > index)
    {
        array->data[i] = array->data[i-1];
        --i;
    }
    array->count ++;
    array->data[i] = value;
    return TRUE;
}
//6.得到数组个数
int get_array_count(Array *array)
{
    if(array == NULL)
    {
        return -1;
    }
    return array->count;
}
//7.得到指定下标元素
void *get_index_value(Array *array, int index)
{
    if(array == NULL || index > get_array_count(array))
    {
        return NULL;
    }
    return array->data[index];
}
//8.删除指定下标元素
Boolean delete_index_value(Array *array, int index)
{
    int i = 0;
    if(array == NULL || index > get_array_count(array))
    {
        return FALSE;
    }

    i = index;
    while(i < array->count)
    {
        array->data[i] = array->data[i+1];
        ++i;
    }
    if(array->free != NULL)
    {
        free(array->data[array->count]);
    }
    array->data[array->count] = NULL;
    array->count --;
    return TRUE;
}
//9.删除指定下标范围的元素
Boolean delete_range_value(Array *array, int begin, int end)
{
#if 1
    int i = begin;
    int diff = end - begin + 1;
    int count = get_array_count(array);
// 0 1 2 3 4 5 6 7 8 9 
//     x x x           count:10  begin:2    end:4   diff:3
// 0 1 5 6 7 8 9 x x x
    if(array == NULL || begin > count || begin < 0 || end < 0
         || end > count || diff < 0 )
    {
        return FALSE;
    }

    while(i < count-diff)
    {
        array->data[i] = array->data[i+diff];
        ++i;
    }

    if(array->free != NULL)
    {
        i = array->count;
        while(i-- > count - diff)
        {
            free(array->data[i]);
            array->data[i] = NULL;
        }
    }
    array->count -= diff;
    return TRUE;
#endif
}
//10.查找指定元素的下标
int find_array_value(Array *array, void *value)
{
    int i = 0 ;
    int count = get_array_count(array);
    printf("array_count:%d\n",count);
    if(array == NULL || value == NULL)
    {
        return -1;
    }
    while(i++ < count)
    {
        if(*((int *)(&array->data[i])) == *((int *)value))
        {
            return i;
        }
    }
    return -1;
}

