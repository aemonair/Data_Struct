#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "hash.h"

#define MAXSIZE (100)
#define HASH_SEARCH (0)
#define HASH_REMOVE (1)

int main(int argc, char **argv)
{
    Hash *hash = NULL; 
    int *array = (int *)Malloc(sizeof(int) * MAXSIZE);
    int i = 0;    

    for(i = 0; i < MAXSIZE; ++i){
        array[i] = rand() % 1000;
    }

    printf("init_hash(10, int_hash_func):\n");
    hash = init_hash(10, int_hash_func);    //整型hash表初始化

    printf("init_insert:\n");
    for(i = 0; i < MAXSIZE; ++i){
        hash_insert(hash, &array[i]);
    }

    printf("show_hash_table:\n");
    show_hash_table(hash);

    printf("the count: %d\n", get_hash_element_count(hash));

#if HASH_SEARCH
    for(i = 0; i < MAXSIZE; ++i)
        hash_search(hash, &array[i]);
#endif

#if HASH_REMOVE
    printf("hash_remove:\n");
    for(i = 0; i < MAXSIZE/2; ++i)
    {
        hash_remove(hash, &array[i]);
    }
    printf("show_hash_table:\n");
    show_hash_table(hash);
    printf("the count: %d\n", get_hash_element_count(hash));
#endif

    printf("destroy_hash:\n");
    destroy_hash(&hash);    //hash表的销毁

    return 0;
}
