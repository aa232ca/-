#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STR_LEN 30

// 节点结构体
typedef struct double_loop_list
{
    char *name;
    struct double_loop_list *next, *prev;

}list_node, *list_link;

// 函数的声明
list_link Create_List_Node();
int Head_Add_Node(list_link head);
int Show_List_Data(list_link head);
int Mode_Select(list_link head);
int Anywhere_Add_Node(list_link head);
int Del_List_Node(list_link head);
int Move_List_Node(list_link head);
int Destory_List(list_link head);

// 函数的定义
list_link Create_List_Node()
{
    list_link node = (list_link) malloc(sizeof(list_node));
    if (node == (list_link)NULL)
    {
        perror("malloc ...");
        return (list_link)-1;
    }

    // 内存清空
    memset(node, 0, sizeof(node));

    // malloc name
    if ((node->name = (char *)malloc(sizeof(char *) * STR_LEN)) == (char *)NULL)
    {
        perror("malloc ... node->name ...");
        return (list_link)-1;
    }

    // 内存清空
    memset(node->name, 0, sizeof(char *) * STR_LEN);

    node->next = node;
    node->prev = node;

    return node;
}

int Head_Add_Node(list_link head)
{
    if (head == (list_link)NULL)
    {
        printf("头结点异常,无法头插!\n");
        return -1;
    }

    // 创建节点
    list_link new_node = Create_List_Node();
    if (new_node == (list_link)-1)
    {
        printf("创建新的节点失败!\n");
        return -1;
    }

    // 第一次添加
    //new_node->prev = head;
    //new_node->next = head;
    //head->prev     = new_node;
    //head->next     = new_node;
    printf("输入想要添加的数据:");
    scanf("%s",new_node->name);

    // 第n次添加
    new_node->next = head->next;
    head->next->prev = new_node;
    
    head->next = new_node;
    new_node->prev = head;


    return 0;
}

int Tail_Add_Node(list_link head)
{
    if (head == (list_link)NULL)
    {
        printf("头节点异常，无法尾插!\n");
        return -1;
    }

    // 创建节点
    list_link new_node = Create_List_Node();
    if (new_node == (list_link)-1)
    {
        printf("创建节点失败！\n");
        return -1;
    }


    printf("请输入数据:");
    scanf("%s",new_node->name);
    // 第一次添加

    // head->next = new_node;
    // head->prev = new_node;
    // new_node->next = head;
    // new_node->prev = head;

    // 第n次添加
    
    head->prev->next = new_node;
    new_node->prev   = head->prev;
    head->prev = new_node;
    new_node->next = head;


    return 0;
}

list_link Find_List_Node(list_link head)
{
    if (head == (list_link)NULL)
    {
        printf("头节点异常，检索失败!\n");
        return (list_link)-1;
    }

    if (head->next == head)
    {
        printf("空链表，无需检索!\n");
        return (list_link)0;
    }

    char obj_name[STR_LEN];
    memset(obj_name, 0, STR_LEN); 
    printf("请输入要检索的数据:");
    scanf("%s", obj_name);
    for (list_link tmp_node = head->next; tmp_node != head; tmp_node=tmp_node->next)
    {
        if (strcmp(obj_name, tmp_node->name) == 0)
        {
            printf("击中目标!\n");
            return tmp_node;
        }
    }

    printf("没有该数据，检索失败!\n");
    return (list_link)-2;
}

int Anywhere_Add_Node(list_link head)
{
    if (head == (list_link)NULL)
    {
        printf("头节点异常！\n");
        return -1;
    }
    else if (head->next == head)
    {
        printf("空链表，默认头插!\n");
        if (Head_Add_Node(head) == -1)
        {
            printf("头插失败!\n");
            return -1;
        }
    }
    else
    {
        list_link obj_node = Find_List_Node(head);
        if (obj_node == (list_link)-2)
        {
            printf("没有该数据节点，任意位置添加失败!\n");
            return -1;
        }

        list_link new_node = Create_List_Node();
        if (new_node == (list_link)-1)
        {
            printf("创建新节点失败, 任意位置添加失败\n");
            return -1;
        }

        printf("请输入数据:");
        scanf("%s", new_node->name);

        // new_node->prev = obj_node;
        // obj_node->next = new_node;

        //head->prev = new_node;
        //new_node->next = head;

        // 第n次
        obj_node->next->prev = new_node;
        new_node->next = obj_node->next;
        
        obj_node->next = new_node;
        new_node->prev = obj_node;

    }

    return 0;
}

int Del_List_Node(list_link head)
{
    if (head == (list_link)NULL)
    {
        printf("头节点异常，无法删除！\n");
        return -1;
    }
    if (head->next == head)
    {
        printf("空链表，无需删除!\n");
        return 0;
    }

    char del_name[STR_LEN];

    printf("请输入要删除的数据:");
    scanf("%s",del_name);

    list_link tmp_node;
    for (tmp_node = head->next; tmp_node != head; tmp_node = tmp_node->next)
    {
        if (strcmp(del_name, tmp_node->name) == 0)
        {
            printf("击中目标!\n");
            // 找到要删除的节点
            
            // 第一种情况（特殊情况）
            // head->next = head;
            // head->prev = head;
            // tmp_node->next = NULL;
            // tmp_node->prev = NULL;
            // free(tmp_node);

            // 一般情况
            tmp_node->next->prev = tmp_node->prev;
            tmp_node->prev->next = tmp_node->next;

            tmp_node->next = NULL;
            tmp_node->prev = NULL;
            
            free(tmp_node);

            return 0;

        }

    }
    printf("没有该数据节点，删除失败!\n");
    return -1;

}

int Move_List_Node(list_link head)
{
    if (head == (list_link)NULL)
    {
        printf("头节点异常，无法移动!\n");
        return -1;
    }
    if (head->next == head)
    {
        printf("空链表，无需移动!\n");
        return 0;
    }

    if (head->next->next == head)
    {
        printf("只有一个数据节点，无需移动!\n");
        return 0;
    }

    list_link move_node = Find_List_Node(head);
    if (move_node == (list_link)-2)
    {
        printf("没有该数据节点，移动失败!\n");
        return -1;
    }

    list_link obj_node = Find_List_Node(head);
    if (obj_node == (list_link)-2)
    {
        printf("没有该数据节点，移动失败!\n");
        return -1;
    }

    move_node->prev->next = move_node->next;
    move_node->next->prev = move_node->prev;

    move_node->next = NULL;
    move_node->prev = NULL;

    move_node->next = obj_node->next;
    obj_node->next->prev = move_node;

    obj_node->next = move_node;
    move_node->prev = obj_node;

    return 0;
}

int Destory_List(list_link head)
{

    if (head == (list_link)NULL)
    {
        printf("头结点异常，无法摧毁!\n");
        return -1;
    }

    if (head->next == head)
    {
        printf("空链表!\n");
        free(head);
        return 0;
    }

    list_link tmp_node = head->next;
    list_link free_node = head->next;

    while (free_node != head)
    {
        tmp_node = free_node->next;

        if (free_node->next != head)
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

        free_node  = tmp_node;
        printf("-----\n");
    }

    free(head);

    return 0;
}

int Show_List_Data(list_link head)
{
    if (head == (list_link)NULL)
    {
        printf("头节点异常，无法遍历!\n");
        return -1;
    }

    if (head->next == head)
    {
        printf("空链表，无需遍历!\n");
        return 0;
    }

    for (list_link tmp_node = head->next; tmp_node != head; tmp_node = tmp_node->next)
    {
        printf("%s\n",tmp_node->name);
    }

    return 0;
}

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
        printf("⚪⚪⚪⚪ 7 遍历单向链表结点⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 8 退出单向链表！！⚪⚪⚪⚪\n");
        printf("输入要选择的功能编号:");
        scanf("%d",&select_num);

        switch (select_num)
        {
        case 1: Head_Add_Node(head);break;
        case 2: Tail_Add_Node(head);break;
        case 3: Anywhere_Add_Node(head);break;
        case 4: Del_List_Node(head);break;
        case 5: Find_List_Node(head);break;
        case 6: Move_List_Node(head);break;
        case 7: Show_List_Data(head);break;
        case 8: Destory_List(head);printf("退出单向链表！！\n");return 0;;
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
        printf("创建头节点失败!\n");
        return -1;
    }
    else
    {
        printf("创建头结点成功！\n");
    }

    Mode_Select(head);

    return 0;
}