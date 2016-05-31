This is a Linked list with control information.
==============================================
**directory tree**
.
├── bin
│   └── test
├── head
│   └── list.h
├── Makefile
├── obj
├── src
│   └── list.c
└── test
    └── main.c

5 directories, 5 files
---------------------------------------------
> please use the Makefile to test.

- use `make` to build the `com/list.o`  
- use `make test` to build the `test/main.c` to create `bin/list`  
- use `make clean` to remove the `./obj/list.o` `./obj/main.o` `./bin/list`



这是一个带有控制信息的单链表。
===========================================
**生成后的目录树结构：**
.
├── bin
│   ├── list
│   └── test
├── head
│   └── list.h
├── Makefile
├── obj
│   ├── list.o
│   └── main.o
├── README.md
├── src
│   └── list.c
└── test
    └── main.c

5 directories, 9 files
-----------------------------------------
> 请使用`Makefile`来做测试，生成可执行代码。


- 使用 `make`命令 可以生成 `com/list.o`  
- 使用 `make test` 可以联合 `test/main.c`一起生成可执行文件  `bin/list`  
- 使用 `make clean` 删除多余的 `./obj/list.o` `./obj/main.o` `./bin/list`文件

