#include <stdio.h>


struct demo
{
    int a;
    long b;
}D;

int main()
{
    // 先求出已知成员变量的到结构体的偏移量
    D.b = 110;

    int offset = (char *)(&(((struct demo *)0)->b)) - (char *)0;
    printf("d的偏移量是:%d\n", offset);

    printf("&D:%p --- 自己算的：%p\n", &D, (struct demo *)((char *)(&(D.b))-offset));
    printf("%ld --- %ld\n", D.b, ((struct demo *)((char *)(&D.b)-offset))->b);
    return 0;
}