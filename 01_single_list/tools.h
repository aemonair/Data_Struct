#ifndef  _TOOLS_H_
#define  _TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//包裹函数

static void *Malloc(size_t size);
static void swap(void *a, void *b, int length);

static void *Malloc(size_t size)
{
    void *result = malloc(size);
    if(result == NULL){   //失败情况处理
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    return result;
}

static void swap(void *a, void *b, int length)
{
    void *temp = Malloc(length);

    memcpy(temp, a, length);
    memcpy(a, b, length);
    memcpy(b, temp, length);
   
    free(temp);
}

#endif //_TOOLS_H_
