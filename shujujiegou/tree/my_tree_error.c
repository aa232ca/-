#include "drawtree.h"


/* ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ 自定义构建二叉树API ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ */

_linktree Create_Cross_Tree_Node();  //创建二叉树节点
int Structure_Cross_Tree();          //构建形成二叉树（构建数据二叉树）
_linktree Insert_Corss_Tree_Node(_linktree root_node,_linktree new_node);//递归添加节点
/* ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ 自定义构建二叉树API ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ */


_linktree Create_Cross_Tree_Node()
{
    _linktree tree_node = (_linktree)malloc(sizeof(_treenode));
    if(tree_node == (_linktree)NULL)
    {
        perror("malloc tree node ... ");
        return (_linktree)-1;
    }

    memset(tree_node,0,sizeof(_treenode));

    tree_node->rchild = NULL;
    tree_node->lchild = NULL;

    return tree_node;
}

int Structure_Cross_Tree() // 构建形成二叉树
{
    _linktree root_node = Create_Cross_Tree_Node();
    if (root_node == (_linktree)-1)
    {
        printf("创建二叉树根节点失败!\n");
        return -1;
    }

    printf("请输入要添加到根节点的数据:");
    scanf("%d", &(root_node->data));
    while (getchar() != '\n');

    while (1) // 循环添加节点，当输入的数据为999的时候停止添加二叉树节点
    {
        _linktree new_node = Create_Cross_Tree_Node();
        if (new_node == (_linktree)-1)
        {
            printf("创建新节点失败!\n");
            return -1;
        }

        printf("请输入要添加的数据:");
        scanf("%d\n", &(new_node->data));

        while (getchar() != '\n');

        if (new_node->data == 999)
        {
            free(new_node);
            printf("二叉树数据节点构建完成，准备画树!\n");
            break;
        }

        // 将节点添加到二叉树中
        if (Insert_Corss_Tree_Node(root_node, new_node) == (_linktree)-1)
        {
            printf("构建二叉树数据节点失败，终止!\n");
            return -1;
        }
    }

    draw(root_node);
    return 0;
}

_linktree Insert_Corss_Tree_Node(_linktree root_node,_linktree new_node)
{
    if (new_node == (_linktree)NULL)
    {
        printf("新节点异常，添加失败!\n");
        return (_linktree)-1;
    }

    if (root_node == (_linktree)NULL)
    {
        return new_node;
    }

    char seat;
    printf("请输入'r'或者'l'决定添加的位置:");
    scanf("%c", &seat);
    while (getchar() != '\n');

    if (seat == 'l')
    {
        root_node->lchild = Insert_Corss_Tree_Node(root_node->lchild, new_node);
    }
    else if (seat == 'r')
    {
        root_node->rchild = Insert_Corss_Tree_Node(root_node->rchild, new_node);
    }
    else 
    {
        printf("输入的指令有误，终止本次添加!\n");
        return root_node;
    }

    return root_node;
}

int main()
{

    Structure_Cross_Tree();

    return 0;
}
