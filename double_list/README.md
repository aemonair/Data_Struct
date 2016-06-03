This is a Double Linked list with control information.
==============================================
**directory tree**
```
.
├── bin
├── head
│   ├── dlist.h
│   └── tools.h
├── Makefile
├── obj
├── README.md
├── src
│   ├── dlist.c
│   └── tools.c
└── test
    └── main.c

5 directories, 7 files
```
---------------------------------------------
> please use the Makefile to test.

- use `make` to build the `com/dlist.o` & `com/tools.o` 
- use `make test` to build the `test/main.c` to create `bin/dlist`  
- use `make clean` to remove the `./obj/dlist.o` `./obj/tools.o` `./obj/main.o` `./bin/list`



这是一个带有控制信息的双向链表。
===========================================
**生成后的目录树结构：**
```
.
├── bin
│   └── dlist
├── head
│   ├── dlist.h
│   └── tools.h
├── Makefile
├── obj
│   ├── dlist.o
│   ├── main.o
│   └── tools.o
├── README.md
├── src
│   ├── dlist.c
│   └── tools.c
└── test
    └── main.c

5 directories, 11 files

```
-----------------------------------------
> 请使用`Makefile`来做测试，生成可执行代码。


- 使用 `make`命令 可以生成 `./obj/dlist.o` & `./obj/tools.o` 
- 使用 `make test` 可以联合 `./test/main.c`一起生成可执行文件  `./bin/dlist`  
- 使用 `make clean` 删除多余的 `./obj/dlist.o` `./obj/tools.o` `./obj/main.o` `./bin/dlist`文件

