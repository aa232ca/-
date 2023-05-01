#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// 定义节点结构体
typedef struct double_listlink
{
    int data;
    struct double_listlink *next, *prev;

}double_listnode, *double_listlink;


// 函数的声明
double_listlink     Create_List_Node();
int                 Head_Add_Node(double_listlink head);
int                 Tail_Add_Node(double_listlink head);
int                 Show_List_Node(double_listlink head);
double_listlink     Find_List_Node(double_listlink head);
int                 Del_List_Node(double_listlink head);
int                 Anywhere_Add_Node(double_listlink head);
int                 Move_List_Node(double_listlink head);
int                 Destory_List(double_listlink head, struct double_listlink **head_p);
int                 Mode_Select(double_listlink head, struct double_listlink **head_p);


// 函数的定义

// 创建节点
double_listlink Create_List_Node()
{
    double_listlink new_node = (double_listlink) malloc (sizeof(double_listnode));
    if (new_node == (double_listlink)NULL) 
    {
        perror("malloc list node ...");
        return (double_listlink)-1;
    }

    memset(new_node, 0, sizeof(double_listnode));

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}
// 头插法
int Head_Add_Node(double_listlink head)
{
    if (head == NULL)
    {
        printf("头节点异常，无法头插!\n");
        return -1;
    }

    double_listlink new_node = Create_List_Node();
    if (new_node == (double_listlink)-1)
    {
        printf("创建新节点失败!\n");
        return -1;
    }

    printf("请输入要添加的数据:");
    scanf("%d",&(new_node->data));

    if (head->next == NULL)
    {
        // 第一次添加
        new_node->prev      = head;
        head->next          = new_node;
    }
    else
    {
        // 第n次添加
        new_node->next      = head->next;
        head->next->prev    = new_node;

        new_node->prev      = head;
        head->next          = new_node;

    }

    return 0;
}
// 尾插法
int Tail_Add_Node(double_listlink head)
{

    if (head == NULL)
    {
        printf("头结点异常，无法尾插!\n");
        return -1;
    }

    // 遍历获取最后一个节点
    double_listlink tmp_node;
    for (tmp_node = head; tmp_node->next != NULL; tmp_node = tmp_node->next);

    // 创建节点
    double_listlink new_node = Create_List_Node();
    if (new_node == (double_listlink)-1)
    {
        printf("创建新节点失败!\n");
        return -1;
    }    

    printf("请输入要添加的数据:");
    scanf("%d",&(new_node->data));

    tmp_node->next = new_node;
    new_node->prev = tmp_node;



    return 0;
}
// 检索指定的数据节点
double_listlink Find_List_Node(double_listlink head)
{
    if (head == NULL)
    {
        printf("头结点异常，无法检索!\n");
        return (double_listlink)-1;
    }
    else if (head->next == NULL)
    {
        printf("空链表，无需检索!\n");
        return (double_listlink)-1;
    }
    else
    {
        int obj_data;
        printf("请输入要检索的数据:");
        scanf("%d",&obj_data);

        for (double_listlink tmp_node = head->next; tmp_node != NULL; tmp_node = tmp_node->next)
        {
            if (obj_data == tmp_node->data)
            {
                printf("击中目标节点!\n");
                return tmp_node;
            }
        }
    }

    printf("没有该数据节点!\n");
    return (double_listlink)-2;
}
//删除链表的节点
int Del_List_Node(double_listlink head)
{
    if (head == NULL)
    {
        printf("头结点异常,无法删除!\n");
        return -1;
    }
    else if (head->next == NULL)
    {
        printf("空链表，无需删除!\n");
        return -1;
    }
    else
    {
        // 对于删除某一个节点，我们需要去获取它的前一个节点
        double_listlink del_node = Find_List_Node(head);
        if (del_node == (double_listlink)-2)
        {
            printf("没有该数据节点,删除操作失败!\n");
            return -1;
        }

        // 如果要删除的节点不是最后节点
        if (del_node->next != NULL)
        {
            del_node->prev->next = del_node->next;
            del_node->next->prev = del_node->prev;
        }
        else  // 要删除的节点是最后一个节点
        {
            del_node->prev->next = NULL;
        }

        del_node->next = NULL;
        del_node->prev = NULL;
        free(del_node);

    }
    return 0;
}
// 任意位置添加
int Anywhere_Add_Node(double_listlink head)
{
    if (head == NULL)
    {
        printf("头结点异常，无法任意位置添加!\n");
        return -1;
    }
    else if (head->next == NULL)
    {
        printf("空链表，无法指定位置添加，默认头插!\n");
        if (Head_Add_Node(head) == -1)
        {
            printf("头插法添加新的节点失败!\n");
            return -1;
        }
    }
    else
    {
        double_listlink obj_node = Find_List_Node(head);
        if (obj_node == (double_listlink)-2)
        {
            printf("没有该数据节点，指定位置添加失败!\n");
            return -1;
        }

        double_listlink new_node = Create_List_Node();
        if (new_node == (double_listlink)-1)
        {
            printf("创建新节点失败，指定位置添加数据失败!\n");
            return -1;
        }

        printf("请输入要添加的数据:");
        scanf("%d",&(new_node->data));


        if (obj_node->next == NULL)
        {
            obj_node->next = new_node;
            new_node->prev = obj_node;
        }
        else
        {
            new_node->next = obj_node->next;
            obj_node->next->prev = new_node;
            obj_node->next = new_node;
            new_node->prev = obj_node;
        }
    }

    return 0;
}
// 移动链表
int Move_List_Node(double_listlink head)
{
    if (head == NULL)
    {
        printf("头节点异常，无法移动!\n");
        return -1;
    }
    else if (head->next == NULL)
    {
        printf("空链表，无需移动!\n");
        return -1;
    }
    else if (head->next->next == NULL)
    {
        printf("只有一个数据，无需移动!\n");
        return -1;
    }
    else
    {
        // 一般情况
        double_listlink obj_node = Find_List_Node(head);
        if (obj_node == (double_listlink)-2)
        {
            printf("没有该数据节点，无法移动!\n");
            return -1;
        }

        double_listlink select_node = Find_List_Node(head);
        if (select_node == (double_listlink)-2)
        {
            printf("没有该数据节点，无法移动！\n");
            return -1;
        }

        // 先将要移动的节点删除出来
        if (obj_node->next == NULL)
        {
            // 最后一个节点
            obj_node->prev->next = NULL;
        }
        else
        {
            // 中间的节点
            obj_node->prev->next = obj_node->next;
            obj_node->next->prev = obj_node->prev;
        }

        obj_node->next = NULL;
        obj_node->prev = NULL;

        // 再将移动出来的点进行添加
        if (select_node->next == NULL) // 添加到最后一个
        {
            select_node->next = obj_node;
            obj_node->prev    = select_node;
        }
        else // 添加在中间
        {
            obj_node->next = select_node->next;
            select_node->next->prev = obj_node;

            select_node->next = obj_node;
            obj_node->prev = select_node;
        }
    }

    return 0;
}
// 遍历链表
int Show_List_Node(double_listlink head)
{

    if (head == NULL)
    {
        printf("头结点异常，无法遍历!\n");
        return -1;
    }

    if (head->next == NULL)
    {
        printf("空链表，无需遍历!\n");
        return -1;
    }

    for (double_listlink tmp_node = head->next; tmp_node != NULL; tmp_node = tmp_node->next)
    {
         printf("%d\n",tmp_node->data);
    }

    return 0;
}
// 销毁链表
int Destory_List(double_listlink head, struct double_listlink **head_p)
{
    if (head == NULL)
    {
        printf("头节点异常，无法销毁!\n");
        return -1;
    }
    else if (head->next == NULL)
    {
        printf("空链表!\n");
        free(head);
        return 0;
    }
    else
    {
        double_listlink tmp_node = head->next;
        double_listlink free_node = head->next;

        while (tmp_node != NULL)
        {
            tmp_node = free_node->next;
            
            if (free_node->next != NULL)
            {
                free_node->next->prev = free_node->prev;
                free_node->prev->next = free_node->next;
            }
            else
            {
                free_node->prev->next = NULL;
            }

            free_node->next = NULL;
            free_node->prev = NULL;
            free(free_node);
            free_node = tmp_node;
            printf("-----\n");
        }
        free(head);
        *head_p = NULL;

    }
    return 0;
}

// 模式选择
int Mode_Select(double_listlink head, struct double_listlink **head_p)
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
        printf("⚪⚪⚪⚪ 7 遍历双向链表结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 8 退出双向链表！！⚪⚪⚪⚪\n");
        printf("请输入要进行操作的数字:");
        scanf("%d", &select_num);

        switch (select_num)
        {
        case 1:
            Head_Add_Node(head);
            break;
        case 2:
            Tail_Add_Node(head);
            break;
        case 3:
            Anywhere_Add_Node(head);
            break;
        case 4:
            Del_List_Node(head);
            break;
        case 5:
            Find_List_Node(head);
            break;
        case 6:
            Move_List_Node(head);
            break;
        case 7:
            Show_List_Node(head);
            break;
        case 8:
            Destory_List(head, head_p);
            printf("退出单向链表！！\n");
            return 0;
        default:
            printf("指令有无，请重新输入！\n");
            break;
        }
        sleep(1);
    }

    return 0;
}

int main()
{

    double_listlink head = Create_List_Node();
    if (head == (double_listlink)-1)
    {
        printf("双向链表初始化失败!\n");
        return -1;
    }
    else
    {
        printf("双向链表初始化成功!\n");
    }
    Mode_Select(head,&head);

    return 0;
}