#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*数据结构体*/
typedef struct queue_data_node
{
    int data;
    struct queue_data_node *next;
} QD, *QD_LINK;

/*控制结构体*/
typedef struct Ctrl_Queue_Str
{
    int queue_size;                     // 队列的大小
    struct queue_data_node *queue_head; // 队头
    struct queue_data_node *queue_tail; // 队尾
} CQ, *CQ_LINK;

/*函数的声明*/
CQ_LINK Link_Queue_Init();
QD_LINK Create_Queue_Node();
int Push_Queue(CQ_LINK cq_link);
int Pop_Queue(CQ_LINK cq_link);
int Show_Queue_Data(CQ_LINK cq_link);
int Destroy_Queue(CQ_LINK cq_link);
int Mode_Select(CQ_LINK cq_link);

/*函数的定义*/
CQ_LINK Link_Queue_Init()
{
    CQ_LINK cq_link = (CQ_LINK)malloc(sizeof(CQ));
    if (cq_link == (CQ_LINK)NULL)
    {
        perror("malloc cq_link");
        return (CQ_LINK)-1;
    }

    memset(cq_link, 0, sizeof(CQ));

    cq_link->queue_size = 0;
    cq_link->queue_head = NULL;
    cq_link->queue_tail = NULL;

    return cq_link;
}

QD_LINK Create_Queue_Node()
{
    QD_LINK new_node = (QD_LINK)malloc(sizeof(QD));
    if (new_node == (QD_LINK)NULL)
    {
        perror("malloc qd_link");
        return (QD_LINK)-1;
    }

    memset(new_node, 0, sizeof(QD));

    new_node->next = NULL;

    return new_node;
}

int Push_Queue(CQ_LINK cq_link)
{
    if (cq_link == (CQ_LINK)NULL)
    {
        printf("控制结构体异常,无法!\n");
        return -1;
    }

    // 创建新节点
    QD_LINK new_node = Create_Queue_Node();
    if (new_node == (QD_LINK)-1)
    {
        printf("新节点创建失败!\n");
        return -1;
    }

    printf("请输入要入队的数据:");
    scanf("%d", &(new_node->data));

    // 进行连接

    if (cq_link->queue_size == 0) // 第一次入队
    {
        cq_link->queue_head = new_node;
        cq_link->queue_tail = new_node;
    }
    else // 第n次入队
    {
        cq_link->queue_tail->next = new_node;
        cq_link->queue_tail = new_node;
    }

    cq_link->queue_size += 1;

    return 0;
}

int Pop_Queue(CQ_LINK cq_link)
{
    if (cq_link == (CQ_LINK)NULL)
    {
        printf("控制结构体异常，无法出队!\n");
        return -1;
    }

    if (cq_link->queue_size == 0)
    {
        printf("空队列，无需出队!\n");
        return -1;
    }

    QD_LINK del_node = cq_link->queue_head;
    if (cq_link->queue_size == 1)
    {
        cq_link->queue_head = NULL;
        cq_link->queue_tail = NULL;
    }
    else
    {
        cq_link->queue_head = cq_link->queue_head->next;
        del_node->next = NULL;
    }

    printf("当前出队的数据是%d\n", del_node->data);
    free(del_node);
    cq_link->queue_size -= 1;

    return 0;
}
int Show_Queue_Data(CQ_LINK cq_link)
{
    if (cq_link == (CQ_LINK)NULL)
    {
        printf("控制结构体异常，无法遍历!\n");
        return -1;
    }

    if (cq_link->queue_size == 0)
    {
        printf("空队列，无需遍历!\n");
        return -1;
    }

    printf("队列中的数据为:\n");
    QD_LINK pos_node = cq_link->queue_head;
    for (int lp = 0; lp < cq_link->queue_size; lp++, pos_node = pos_node->next)
    {
        printf("%d\n", pos_node->data);
    }

    return 0;
}

int Destroy_Queue(CQ_LINK cq_link)
{
    if (cq_link == (CQ_LINK)NULL)
    {
        printf("控制结构体异常，无法摧毁!\n");
        return -1;
    }

    if (cq_link->queue_size == 0)
    {
        printf("空队列，无需摧毁!\n");
        return 0;
    }

    QD_LINK tmp_node = cq_link->queue_head;
    QD_LINK free_node = cq_link->queue_head;
    while (free_node != NULL)
    {
        tmp_node = free_node->next;
        if (cq_link->queue_size == 1)
        {
            cq_link->queue_head = NULL;
            cq_link->queue_tail = NULL;
        }
        else
        {
            cq_link->queue_head = cq_link->queue_head->next;
            free_node->next = NULL;
        }

        cq_link->queue_size -= 1;

        free(free_node);
        free_node = tmp_node;

        printf("----\n");
    }
    return 0;
}
int Mode_Select(CQ_LINK cq_link)
{
    int select_num;
    while (1)
    {
        system("clear");
        printf("⚪⚪⚪⚪ 1 入队！⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 2 出队！⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 3 遍历队列⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 4 退出队列⚪⚪⚪⚪\n");
        printf("请输入要实现的功能:");
        scanf("%d", &select_num);

        switch (select_num)
        {
        case 1:
            Push_Queue(cq_link);
            break;
        case 2:
            Pop_Queue(cq_link);
            break;
        case 3:
            Show_Queue_Data(cq_link);
            break;
        case 4:
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

    CQ_LINK cq_link = Link_Queue_Init();
    if (cq_link == (CQ_LINK)-1)
    {
        printf("链式队列初始化失败!\n");
        return -1;
    }

    Mode_Select(cq_link);

    Destroy_Queue(cq_link);

    printf("队列摧毁成功!\n");
    return 0;
}