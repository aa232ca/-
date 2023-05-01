#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ARRAY_LEN 10

/*实现冒泡排序*/
/*遍历n次，每一次让最大的值置于最后/
/*函数的声明*/
int Get_Array_Data(int array[]);
void Swap_Array_Data(int array[], int i, int j);
int Print_Array_Data(int array[]);
int Bubble_Sort(int array[]);

/*函数的定义*/
int Get_Array_Data(int array[])
{
    srand(time(0));
    for (int lp=0; lp<ARRAY_LEN; lp++) array[lp] = rand()%100;
    return 0;
}

int Print_Array_Data(int array[])
{
    for (int lp=0; lp<ARRAY_LEN; lp++) printf("%d ", array[lp]);
    printf("\n");
    return 0;
}

void Swap_Array_Data(int array[],int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}
int Bubble_Sort(int array[])
{
    for (int i=ARRAY_LEN-1; i>0; i--)
        for (int j=0; j<i; j++)
            if (array[j]>array[j+1])
                Swap_Array_Data(array, j, j+1);

    return 0;
}

int main()
{
    int arr[ARRAY_LEN];
    Get_Array_Data(arr);
    Print_Array_Data(arr);
    Bubble_Sort(arr);
    Print_Array_Data(arr);
    return 0;
}