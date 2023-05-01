#include "list.h"

int main()
{

    Kernel_List_Fun();

    BIG_LINK big_head = Create_Node();
    if (big_head == (BIG_LINK)-1)
    {
        printf("创建头结点失败!\n");
        return -1;
    }
    else
    {
        printf("创建头结点成功!\n");
    }

    // Head_Add_Node(big_head);

    /*
    第一个大头:                 *big_head
    第一个大头的地址:           big_head
    第一个小头：         big_head->little_head
    第一个小头的地址：      &(big_head->little_head)

    对于第二个大头的地址以及第二个大头需要用结构体的成员变量取获取
    偏移量然后来得到该结构体的地址

    第二个大头：
    第二个大头的地址：
    第二个小头：       *(big_head->little_head.next)
    第二个小头的地址：  big_head->little_head.next
    */

    /*
     获取偏移量
    */

    // int offset = (int)((char *)&(((BIG_LINK)0)->little_head) - (char *)0);

    // BIG_LINK BIG_POS = (BIG_LINK)((char *)big_head->little_head.next - offset);

    // printf("你添加的数据是:%d\n", BIG_POS->data);

    // long offset = (long)((&(((BIG_LINK)0)->little_head)) - 0);
    // // printf("%ld\n",offset);
    // BIG_LINK BIG_POS = (BIG_LINK)((char *)(big_head->little_head.next) - offset);
    
    // printf("你添加的数据是:%d\n", BIG_POS->data);

    // Show_List_Data(big_head);

    Mode_Select(big_head);

    return 0;
}
