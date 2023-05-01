#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 数据结构体类型
typedef struct stack_data
{
    int data;
    struct stack_data *next;
}SD_NODE, *SD_LINK;

// 控制结构体类型
typedef struct Ctrl_Stack
{
    SD_LINK stack_top;
    int stack_size;
}CS, *CS_P;


// 函数的声明
CS_P Link_Stack_Init();                         // 初始化栈
SD_LINK Create_Data_Node();                     // 创建数据节点
int Push_Link_Stack(CS_P link_stack_ctrl);      // 压栈
int Pop_Link_Stack(CS_P link_stack_ctrl);       // 出栈
int Show_Link_Stack(CS_P link_stack_ctrl);      // 遍历 
int Destory_Link_Stack(CS_P link_stack_ctrl);   // 摧毁
int Mode_Select(CS_P list_stack_ctrl);

// 函数的定义
CS_P Link_Stack_Init()
{
    CS_P link_stack_ctrl = (CS_P)malloc(sizeof(CS));
    if (link_stack_ctrl == (CS_P)NULL)
    {
        perror("malloc link_stack_ctrl...");
        return (CS_P)-1;
    }

    memset(link_stack_ctrl, 0, sizeof(CS));

    link_stack_ctrl->stack_top = NULL;
    link_stack_ctrl->stack_size = 0;

    return link_stack_ctrl;
}

SD_LINK Create_Data_Node()
{
    SD_LINK sd_link = (SD_LINK)malloc(sizeof(SD_NODE));
    if (sd_link == (SD_LINK)NULL)
    {
        perror("malloc sd_link ...");
        return (SD_LINK)-1;
    }

    memset(sd_link, 0, sizeof(SD_NODE));

    sd_link->next = NULL;

    return sd_link;
}


int Push_Link_Stack(CS_P link_stack_ctrl)
{
    if (link_stack_ctrl == (CS_P)NULL)
    {
        printf("控制结构体异常！\n");
        return -1;
    }

    // 创建数据节点
    SD_LINK new_sd = Create_Data_Node();
    if(new_sd == (SD_LINK)-1)
    {
        printf("创建新节点失败,无法压栈！\n");
        return -1;
    }

    printf("请输入要添加的数据:");
    scanf("%d",&(new_sd->data));

    new_sd->next = link_stack_ctrl->stack_top;
    link_stack_ctrl->stack_top = new_sd;

    link_stack_ctrl->stack_size += 1;

    return 0;
}

int Show_Link_Stack(CS_P link_stack_ctrl)
{
    if (link_stack_ctrl == (CS_P)NULL)
    {
        printf("控制结构体异常，无法遍历!\n");
        return -1;
    }

    if (link_stack_ctrl->stack_size == 0)
    {
        printf("空栈，无需遍历!\n");
        return 0;
    }

    printf("链式栈遍历的的数据:\n");
    for (SD_LINK tmp_node = link_stack_ctrl->stack_top; tmp_node != NULL; tmp_node = tmp_node->next)
    {
        printf("%d\n", tmp_node->data);
    }

    return 0;
}

int Pop_Link_Stack(CS_P link_stack_ctrl)
{
    if (link_stack_ctrl == (CS_P)NULL)
    {
        printf("控制结构体异常,无法弹栈!\n");
        return -1;
    }

    if (link_stack_ctrl->stack_size == 0)
    {
        printf("空栈，无需弹栈!\n");
        return -1;
    }

    printf("弹出的数据是:%d\n", link_stack_ctrl->stack_top->data);

    // // 剩下一个弹出
    // link_stack_ctrl->stack_top = NULL;
    // 还存在多个数据
    SD_LINK pop_node = link_stack_ctrl->stack_top;
    link_stack_ctrl->stack_top = pop_node->next;
    pop_node->next = NULL;

    link_stack_ctrl->stack_size -= 1;
    return 0;
}

int Destory_Link_Stack(CS_P link_stack_ctrl)
{
    if (link_stack_ctrl == (CS_P)NULL)
    {
        printf("控制结构体异常，无法摧毁!\n");
        return -1;
    }

    if (link_stack_ctrl->stack_size == 0)
    {
        free(link_stack_ctrl);
        return 0;
    }

    SD_LINK tmp_node = link_stack_ctrl->stack_top;
    SD_LINK free_node = link_stack_ctrl->stack_top;

    while (free_node != NULL)
    {
        tmp_node = free_node->next;
        link_stack_ctrl->stack_top = free_node->next;
        free_node->next = NULL;

        free(free_node);

        free_node = tmp_node;
        printf("----\n");
    }

    free(link_stack_ctrl);
    printf("销毁链式栈成功!\n");
    return 0;
}

int Mode_Select(CS_P link_stack_ctrl)
{
    int select_num;
    while(1)
    {
        system("clear");
        printf("⚪⚪⚪⚪ 1 压栈！⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 2 弹栈！⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 3 遍历栈⚪⚪⚪⚪\n");
        printf("⚪⚪⚪⚪ 4 退出栈⚪⚪⚪⚪\n");
        printf("请输入要实现的功能:");
        scanf("%d",&select_num);

        switch (select_num)
        {
        case 1: Push_Link_Stack(link_stack_ctrl);break;
        case 2: Pop_Link_Stack(link_stack_ctrl);break;
        case 3: Show_Link_Stack(link_stack_ctrl);break;
        case 4: return 0;
        default: printf("指令有无，请重新输入！\n");break;
        }
        sleep(1);
    }

    return 0;
}

int main()
{

    CS_P link_stack_ctrl = Link_Stack_Init();
    if (link_stack_ctrl == (CS_P)-1)
    {
        printf("链式栈初始化失败!\n");
        return -1;
    }
    
    Mode_Select(link_stack_ctrl);

    Destory_Link_Stack(link_stack_ctrl);
    return 0;
}