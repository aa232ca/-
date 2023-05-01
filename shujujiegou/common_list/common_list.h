在指针域不变情况下，数据域变的情况下使用的。

疑问：
    一开始，我写了一条链表，链表节点类型如下,同时我也把他的每一个函数接口都写好了
    
    struct xxx
    {
        char name[20];
      struct xxx *next,*prev;      
    };
    
    Creta
    tail_add
    head_add
    del...
    move
    但是现在你发现还需要一条新的链表，也是双向循环链表
    struct xxx
    {
       int number;
      struct xxx *next,*prev;      
    };

list.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#ifndef DATA_TYPE
    #define DATA_TYPE int

                                        
struct commom_demo
{
     DATA_TYPE data;
    
    struct xxx *next,*prev;  
};

struct data//定义新的数据域
{
   long fads;//充当链表节点中的数据
   gjh
   hkj
   hk
   hk
   hk
};

main.c
#define DATA_TYPE  long
#include <list.h>
int main（）
{


    return 0;
}