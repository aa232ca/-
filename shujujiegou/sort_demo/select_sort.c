#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ARRAY_LEN 10

/*实现选择排序*/


/*函数的声明*/
int Get_Array_Data(int array[]);
void Swap_Array_Data(int array[], int i, int j);
int Print_Array_Data(int array[]);
int Select_Sort(int array[]);

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
int Select_Sort(int array[])
{
    for(int i=0; i<ARRAY_LEN; i++)
    {
        int minIndex = i;
        for (int j=i+1; j<ARRAY_LEN; j++)
        {
            minIndex = array[minIndex] > array[j] ? j : minIndex;
        }
        Swap_Array_Data(array, i, minIndex);
    }
    return 0;
}

int main()
{
    int arr[ARRAY_LEN];
    Get_Array_Data(arr);
    Print_Array_Data(arr);
    Select_Sort(arr);
    Print_Array_Data(arr);
    return 0;
}