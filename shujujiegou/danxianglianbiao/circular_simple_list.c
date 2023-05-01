#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERACH_PRESENT_NODE 0
#define SERACH_BEFORE_NODE  1


typedef struct list_link
{
    int data;
    struct list_link *next;

}list_node, *list_link;

// 函数的声明
list_link   Create_List_Node();
int         Head_List_Node(list_link head);
int         Tail_List_Node(list_link head);
int         Show_List_Node(list_link head);
list_link   Find_List_Node(list_link head, int search_mode);
int         Del_List_Node(list_link head);
int         Anywhere_Add_Node(list_link head);
int         Move_List_Node(list_link head);
int         Destory_List(list_link head);
int         Mode_Select(list_link head);
// 函数的定义

// 创建节点
list_link Create_List_Node()
{
    list_link node = (list_link) malloc (sizeof(list_node));
    if (node == (list_link)NULL)
    {
        perror("malloc list node ...");
        return (list_link)-1;
    }
    
    // 内存清空
    memset(node, 0, sizeof(list_node));

    // 单向循环链表和单向链表的区别
    // 单向循坏链表的next的是指向自己的
    node->next = node;

    return node;
}
// 头插法
int Head_List_Node(list_link head)
{
    if (head == NULL)
    {
        printf("头节点异常，无法头插!\n");
        return -1;
    }

    // 创建要插入的节点
    list_link new_node = Create_List_Node();
    if (new_node == (list_link)-1)
    {
        printf("创建新的几点失败!\n");
        return -1;
    }

    // 输入数据
    printf("请输入数据:");
    scanf("%d",&(new_node->data));

    // 头插
    new_node->next = head->next;
    head->next = new_node;

    return 0;
}
// 尾插法
int Tail_List_Node(list_link head)
{
    if (head == NULL)
    {
        printf("头结点异常，无法尾插!\n");
        return -1;
    }

    // 获取尾结点
    list_link tmp_node = NULL;
    for (tmp_node=head->next; tmp_node->next != head; tmp_node=tmp_node->next);

    // 创建新的节点
    list_link new_node = Create_List_Node();
    if (new_node == (list_link)-1)
    {
        printf("创建新节点失败!\n");
        return -1;
    }

    printf("输入数据:");
    scanf("%d", &(new_node->data));

    tmp_node->next = new_node;
    new_node->next = head;

    return 0;
}
// 遍历链表的数据
int Show_List_Node(list_link head)
{
    if (head == NULL)
    {
        printf("头节点异常，无法遍历!\n");
        return -1;
    }

    if (head->next == head)
    {
        printf("空链表，无需遍历!\n");
        return 0;
    }

    for (list_link tmp_node=head->next; tmp_node != head; tmp_node = tmp_node->next)
    {
        printf("%d\n",tmp_node->data);
    }
    return 0;
}
// 检索指定的数据节点
list_link Find_List_Node(list_link head, int search_mode)
{
    if (head == NULL)
    {
        printf("头节点异常，无法检索!\n");
        return (list_link)-1;
    }
    else if (head->next == head)
    {
        printf("空链表,无需检索!\n");
        return (list_link)0;
    }
    else
    {
        int obj_data;
        printf("请输入要指定的数据:");
        scanf("%d",&obj_data);

        for (list_link obj_node=head; obj_node->next != head; obj_node = obj_node->next)
        {
            if (obj_data == obj_node->next->data)
            {
                printf("击中目标节点!\n");
                if (search_mode == SERACH_PRESENT_NODE)
                {
                    return obj_node->next;
                }
                
                if (search_mode == SERACH_BEFORE_NODE)
                {
                    return obj_node;
                }
            }
        }
    }
    
    printf("链表中没有该数据!\n");
    return (list_link)-2;
}
// 删除指定节点
int Del_List_Node(list_link head)
{
    if (head == NULL)
    {
        printf("头节点异常，无法删除!\n");
        return -1;
    }

    if (head->next == head)
    {
        printf("空链表，无需删除!\n");
        return 0;
    }
    
    list_link before_del_node = Find_List_Node(head, SERACH_BEFORE_NODE);
    if (before_del_node == (list_link)-2)
    {
        printf("没有该数据节点，删除操作失败!\n");
        return -1;
    }

    // 备份一下要删除的结点
    list_link del_node = before_del_node->next;

    before_del_node->next = before_del_node->next->next;

    del_node->next = NULL;
    free(del_node);

    return 0;
}
// 任意位置添加节点的数据
int Anywhere_Add_Node(list_link head)
{

    if (head == NULL)
    {
        printf("头节点异常，无法添加");
        return -1;
    }
    else if (head->next == head)
    {
        printf("空链表，无法指定位置添加，默认进行头插法!\n");
        if (Head_List_Node(head) == -1)
        {
            printf("头插法添加新节点失败!\n");
            return -1;
        }
    }
    else
    {
        list_link obj_node = Find_List_Node(head, SERACH_PRESENT_NODE);
        if (obj_node == (list_link)-2)
        {
            printf("没有该数据结点，指定位置添加失败!\n");
            return -1;
        }

        list_link new_node = Create_List_Node();
        if (new_node == (list_link)-1)
        {
            printf("新结点创建失败!指定位置添加数据失败！\n");
            return -1;
        }

        printf("请输入要添加的新数据:");
        scanf("%d\n", &(new_node->data));

        new_node->next = obj_node->next;
        obj_node->next = new_node;

    }
    
    return 0;
}
//移动指定数据节点
int Move_List_Node(list_link head)
{
    if (head == NULL)
    {
        printf("头结点异常，无法移动!\n");
        return -1;
    }

    if (head->next == head)
    {
        printf("空链表，无需移动!\n");
        return 0;
    }

    if (head->next->next == head)
    {
        printf("只有一个数据，无需移动!\n");
        return 0;
    }

    list_link before_obj_node = Find_List_Node(head, SERACH_BEFORE_NODE);
    if (before_obj_node == (list_link)-2)
    {
        printf("没有该数据节点,无法移动!\n");
        return -1;
    }

    list_link select_node = Find_List_Node(head, SERACH_PRESENT_NODE);
    if (select_node == (list_link)-2)
    {
        printf("没有该数据节点，无法移动!\n");
        return -1;
    }

    if (before_obj_node->next == select_node)
    {
        printf("同一个节点，无需操作!\n");
        return 0;
    }

    // 断开目标节点
    list_link obj_node = before_obj_node->next;
    before_obj_node->next = obj_node->next;
    obj_node->next = NULL;
    // 再将目标节点接到某个节点之后
    obj_node->next = select_node->next;
    select_node->next = obj_node;

    return 0;
}
// 销毁链表
int Destory_List(list_link head)
{
    if (head == NULL)
    {
        printf("头节点异常,无法销毁!\n");
        return -1;
    }

    if (head->next == head)
    {
        printf("空链表，直接释放头结点!\n");
        free(head);
        return 0;
    }

    list_link tmp_node = head->next;
    list_link free_node = head->next;
    
    while (tmp_node != head)
    {
        tmp_node = free_node->next;
        head->next = free_node->next;
        free_node->next = NULL;
        free(free_node);

        free_node = tmp_node;
        printf("----\n");
    }

    free(head);

    return 0;
}
// 模式的选择
int Mode_Select(list_link head)
{
    int select_num;
    while(1)
    {
        system("clear");
        printf("⚪⚪⚪⚪ 1 头插添加数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 2 尾插添加数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 3 指定位置添加数据⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 4 删除指定数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 5 检索指定数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 6 移动指定数据结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 7 遍历单项循环链表⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 8 退出单向链表！！⚪⚪⚪⚪\n");
        
        printf("输入要操作前面的数字:");
        scanf("%d",&select_num);

        switch (select_num)
        {
        case 1: Head_List_Node(head);break;
        case 2: Tail_List_Node(head);break;
        case 3: Anywhere_Add_Node(head);break;
        case 4: Del_List_Node(head);break;
        case 5: Find_List_Node(head,SERACH_PRESENT_NODE);break;
        case 6: Move_List_Node(head);break;
        case 7: Show_List_Node(head);break;
        case 8: Destory_List(head);printf("退出单向链表！！\n");return 0;
        default: printf("指令有无，请重新输入！\n");break;
        }

        sleep(1);
    }
    

    return 0;
}
int main()
{
    list_link head = Create_List_Node();
    if (head == (list_link)-1)
    {
        printf("单项循环链表初始化失败!\n");
        return -1;
    }
    else
    {
        printf("单向循环链表初始化成功!\n");
    }

    Mode_Select(head);

    return 0;
}