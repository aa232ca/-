#include <stdio.h>


struct demo
{
    int data;
    struct demo * str_p;
};


int main()
{

    struct demo A,B;

    A.str_p = &B;


    return 0;
}