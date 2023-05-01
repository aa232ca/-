#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ARRAY_LEN 10

/*实现插入排序*/
/*0-0\0-1\0-n-1这样不断地排序*/

/*函数的声明*/
int Get_Array_Data(int array[]);
void Swap_Array_Data(int array[], int i, int j);
int Print_Array_Data(int array[]);
int Insert_Sort(int array[]);

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
int Insert_Sort(int array[])
{
    for (int i=0; i<ARRAY_LEN; i++)
        for (int j=i-1; j>=0&&array[j]>array[j+1]; j--)
            Swap_Array_Data(array, j, j+1);
    return 0;
}

int main()
{
    int arr[ARRAY_LEN];
    Get_Array_Data(arr);
    Print_Array_Data(arr);
    Insert_Sort(arr);
    Print_Array_Data(arr);
    return 0;
}