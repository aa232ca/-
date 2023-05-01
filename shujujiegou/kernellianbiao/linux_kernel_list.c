#include "list.h"

int Kernel_List_Fun()
{
    printf("My kernel list!\n");
    return 0;
}

BIG_LINK Create_Node()
{
    // 申请大头结点的堆空间
    BIG_LINK big_node = (BIG_LINK)malloc(sizeof(BIG_NODE));
    if (big_node == (BIG_LINK)NULL)
    {
        perror("malloc ...");
        return (BIG_LINK)-1;
    }

    memset(big_node, 0, sizeof(BIG_NODE));

    INIT_LIST_HEAD(&(big_node->little_head)); // 使用内核链表的API来初始化

    return big_node;
}

 int Head_Add_Node(BIG_LINK big_head)
{

    if (big_head == (BIG_LINK)NULL)
    {
        printf("头结点异常!\n");
        return -1;
    }

    BIG_LINK new_node = Create_Node();
    if (new_node == (BIG_LINK)-1)
    {
        printf("创建新节点失败,无法添加!\n");
        return -1;
    }

    printf("请输入要添加的数据:");
    scanf("%d", &(new_node->data));
    // printf("%d\n", big_head->data);
    list_add(&(new_node->little_head), &(big_head->little_head));

    return 0;
}

int Show_List_Data(BIG_LINK big_head)
{

    if (big_head == (BIG_LINK)NULL)
    {
        printf("头节点异常!\n");
        return -1;
    }

    if (list_empty(&(big_head->little_head)))
    {
        printf("空链表，无需遍历!\n");
        return 0;
    }

    BIG_LINK pos = NULL;
    list_for_each_entry(pos, &(big_head->little_head), little_head)
    {
        printf("%d\n", pos->data);
    }

    return 0;
}

int Tail_Add_Node(BIG_LINK big_head)
{
    if (big_head == (BIG_LINK)NULL)
    {
        printf("头节点异常!\n");
        return -1;
    }

    BIG_LINK new_node = Create_Node();
    if (new_node == (BIG_LINK)-1)
    {
        printf("创建新节点失败!\n");
        return -1;
    }

    printf("请输入要添加的数据:");
    scanf("%d", &(new_node->data));
    list_add_tail(&(new_node->little_head), &(big_head->little_head));

    return 0;
}

BIG_LINK Find_List_Node(BIG_LINK big_head)
{
    if (big_head == (BIG_LINK)NULL)
    {
        printf("头节点异常!\n");
        return (BIG_LINK)-1;
    }

    if (list_empty(&(big_head->little_head)))
    {
        printf("空链表，无需检索!\n");
        return (BIG_LINK)0;
    }

    int obj_data;
    printf("请输入要操作的数据:");
    scanf("%d", &obj_data);

    BIG_LINK pos = NULL;
    list_for_each_entry(pos, &(big_head->little_head), little_head)
    {
        if (pos->data == obj_data)
        {
            printf("击中目标！\n");
            return pos;
        }
    }

    printf("没击中目标!\n");

    return (BIG_LINK)-2;
}

int Anywhere_Add_Node(BIG_LINK big_head)
{
    if (big_head == (BIG_LINK)NULL)
    {
        printf("头结点异常！\n");
        return -1;
    }

    if (list_empty(&(big_head->little_head)))
    {
        printf("空链表，默认头插!\n");
        if (Head_Add_Node(big_head) == -1)
        {
            printf("头插法失败!\n");
            return -1;
        }
        return 0;
    }

    BIG_LINK obj_node = Find_List_Node(big_head);
    if (obj_node == (BIG_LINK)-2)
    {
        printf("没有该数据，指定位置添加失败!\n");
        return -1;
    }

    BIG_LINK new_node = Create_Node();
    if (new_node == (BIG_LINK)-1)
    {
        printf("创建新节点失败,无法指定位置添加!\n");
        return -1;
    }

    printf("请输入要添加的数据:");
    scanf("%d", &(new_node->data));

    list_add(&(new_node->little_head), &(obj_node->little_head));

    return 0;
}

int Del_List_Node(BIG_LINK big_head)
{
    if (big_head == (BIG_LINK)NULL)
    {
        printf("头节点异常!\n");
        return -1;
    }

    if (list_empty(&(big_head->little_head)))
    {
        printf("空链表，无法删除!\n");
        return 0;
    }

    BIG_LINK del_obj_node = Find_List_Node(big_head);
    if (del_obj_node == (BIG_LINK)-2)
    {
        printf("没有该数据节点，删除失败!\n");
        return -1;
    }

    list_del(&(del_obj_node->little_head));
    free(big_head);

    return 0;
}

int Move_List_Node(BIG_LINK big_head)
{
    if (big_head == (BIG_LINK)NULL)
    {
        printf("头节点异常!\n");
        return -1;
    }

    if (list_empty(&(big_head->little_head)))
    {
        printf("空链表，无法移动!\n");
        return 0;
    }

    if (big_head->little_head.next->next == &(big_head->little_head))
    {
        printf("只有一个数据节点，无需移动!\n");
        return 0;
    }

    BIG_LINK move_node = Find_List_Node(big_head);
    if (move_node == (BIG_LINK)-2)
    {
        printf("没有该数据节点，无法移动!\n");
        return -1;
    }

    printf("请选择要移动到哪里:");
    BIG_LINK obj_node = Find_List_Node(big_head);
    if (obj_node == (BIG_LINK)-2)
    {
        printf("没有该数据节点，无法移动!\n");
        return -1;
    }

    list_del(&(move_node->little_head));

    list_add(&(move_node->little_head), &(obj_node->little_head));

    return 0;
}

int Destory_List(BIG_LINK big_head)
{
    if (big_head == (BIG_LINK)NULL)
    {
        printf("头节点异常!\n");
        return -1;
    }

    if (list_empty(&(big_head->little_head)))
    {
        free(big_head);
        printf("摧毁链表成功!\n");
        return 0;
    }

    BIG_LINK pos_big;
    // 直接备份最后的大头节点
    BIG_LINK last_big_node = list_entry(big_head->little_head.prev, BIG_NODE, little_head);
    list_for_each_entry(pos_big, &(big_head->little_head), little_head)
    {
        BIG_LINK free_big_node = list_entry(pos_big->little_head.prev, BIG_NODE, little_head);
        if (free_big_node != big_head)
        {
            list_del(&(free_big_node->little_head));
            printf("即将释放的节点的数据是：%d\n", free_big_node->data);
            free(free_big_node);
        }
    }

    printf("即将释放的节点的数据是：%d\n", last_big_node->data);
    list_del(&(last_big_node->little_head));
    free(last_big_node);
    printf("摧毁链表成功!\n");
    return 0;
}

int Mode_Select(BIG_LINK big_head)
{
    int select_num;
    while (1)
    {
        system("clear");
        printf("⚪⚪⚪⚪ 1 头插添加数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 2 尾插添加数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 3 指定位置添加数据⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 4 删除指定数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 5 检索指定数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 6 移动指定数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 7 遍历单向链表结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 8 退出单向链表！！⚪⚪⚪⚪\n");
        printf("输入你想要选择的功能的序号:");
        scanf("%d", &select_num);

        switch (select_num)
        {
        case 1:
            Head_Add_Node(big_head);
            break;
        case 2:
            Tail_Add_Node(big_head);
            break;
        case 3:
            Anywhere_Add_Node(big_head);
            break;
        case 4:
            Del_List_Node(big_head);
            break;
        case 5:
            Find_List_Node(big_head);
            break;
        case 6:
            Move_List_Node(big_head);
            break;
        case 7:
            Show_List_Data(big_head);
            break;
        case 8:
            Destory_List(big_head);
            printf("退出内核链表！！\n");
            return 0;
        default:
            printf("指令有无，请重新输入！\n");
            break;
        }

        sleep(1);
    }

    return 0;
}
