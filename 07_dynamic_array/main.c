#include <stdio.h>
#include "iterator.h"
#include "dynamic_array.h"

int main(int argc, char **argv)
{
    int i = 0;
    Array *array= init_array(30);
    int a[] = {1, 2, 3, 4, 5};
    int length = sizeof(a)/sizeof(a[0]);
 
    for(i = 0; i < length; ++i)
    {
        array_insert_prev(array, i, &a[i]);
    }

    for(i = 0; i < length; ++i)
    {
        array_insert_next(array, i, &a[i]);
    }

    printf("array_count:");
    printf("%d \n",get_array_count(array));

    length = get_array_count(array);
    printf("length:%d\n",length);
    printf("Array :\n");
    for(i = 0; i < length; ++i)
    {
        printf("%d ",*(int *)array->data[i]);
    }
    printf("\n");
    printf("array_index_count_2:");
    printf("%d \n",*(int *)get_index_value(array, 2));


    printf("delete_index_value(array, 2):\n");
    delete_index_value(array, 2);

    length = get_array_count(array);
    for(i = 0; i < length; ++i)
    {
        printf("%d ",*(int *)array->data[i]);
    }
    printf("\n");
    
    delete_range_value(array, 1, 3);
    length = get_array_count(array);
    for(i = 0; i < length; ++i)
    {
        printf("%d ",*(int *)array->data[i]);
    }
    printf("\n");
/*    foreach(iter, array)
    {
        printf("%d ",*(int *)array->data[i]);
   }
 */
    printf("find_array_value(array, ?)\n");
    printf("array[5]: %d \n",find_array_value(array, &array->data[5]));
    printf("array[3]:%d \n",find_array_value(array, &array->data[3]));
    printf("\n");

    printf("clean_array(array)\n");
    clean_array(array);
    length = get_array_count(array);
    for(i = 0; i < length; ++i)
    return 0;
}
