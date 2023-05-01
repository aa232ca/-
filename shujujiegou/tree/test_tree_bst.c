#include "drawtree.h"

_linktree Create_Cross_Tree_Node();  //创建二叉树节点
int Structure_Cross_Tree();          //构建形成二叉树（构建数据二叉树）
_linktree Insert_Corss_Tree_Node(_linktree root_node,_linktree new_node);//递归添加节点


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



int Structure_Cross_Tree()          //构建形成二叉树
{
    _linktree root_node = Create_Cross_Tree_Node();
    if(root_node == (_linktree)-1)
    {
        printf("创建二叉树根节点失败!\n");
        return -1;
    }

    printf("请输入要添加到根节点的数据：");
    scanf("%d",&(root_node->data));
    while(getchar()!='\n');

    while(1) //循环一次添加一个节点，直到输入999停止添加二叉树节点
    {
        _linktree new_node = Create_Cross_Tree_Node();
        if(new_node == (_linktree)-1)
        {
            printf("创建新节点失败！\n");
            return -1;
        }

        printf("请输入要添加的数据：");
        scanf("%d",&(new_node->data));
        while(getchar()!='\n');

        if(new_node->data == 999)
        {
            free(new_node);
            printf("二叉树数据节点构建完成，准备画树！\n");
            break;
        }

        //进行节点添加到二叉树中
        if(Insert_Corss_Tree_Node(root_node,new_node) == (_linktree)-1)
        {
            printf("构建二叉树数据节点失败，终止！\n");
            return -1;
        }
    }

    //在这里调用头文件提供的画树函数
    draw(root_node);
    return 0;
}


_linktree Insert_Corss_Tree_Node(_linktree root_node,_linktree new_node)//递归添加节点
{
    if(new_node == NULL)
    {
        printf("新节点异常，添加失败!\n");
        return (_linktree)-1;
    }

    if(root_node == NULL) return new_node;//递归到了最后一层，新节点连接到最后一层

    if (new_node->data < root_node->data)
    {
         root_node->lchild = Insert_Corss_Tree_Node(root_node->lchild,new_node);
    }
    else if (new_node->data > root_node->data)
    {
        root_node->rchild = Insert_Corss_Tree_Node(root_node->rchild,new_node);
    }
    else
    {
        printf("已经有了该数据无需添加!\n");
    }
    return root_node; //返回上一级， 返回当前子树的根节点。
}


int main()
{
    Structure_Cross_Tree();

    return 0;
}