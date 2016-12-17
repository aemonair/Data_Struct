#include <stdio.h>
#include <stdlib.h>
#include "gen_list.h"

int main(int argc, char **argv)
{
    Gen_list list = NULL;
    Gen_list new_list = NULL;

    char str[] = "(15, 'c', (20, 'd', (30, 'f')), ('g', 'i'), 60)";

    list = init_genlist(str);
  
    show_genlist(list);    //显示广义表信息

    printf("%d\n",get_genlist_count(list));
    printf("%d\n",get_genlist_depth(list));

    new_list = copy_genlist(list);
    show_genlist(new_list);    //显示广义表信息
    destroy_genlist(&list);   //广义表的销毁
    return 0;
}


//(15, 'c', (20, 'd', (30, 'f')), ('g', 'i'), 60)
