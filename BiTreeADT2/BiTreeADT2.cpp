#include "BiTreeADT2.h"
#define _CRT_SECURE_NO_WARNINGS


BiTree Second_menu(BiTree T, TREELISTS& treelist)
{
    int op = 1;
    int result1;

    int num = 0;
    int nums[1000];
    memset(nums, 0, sizeof(nums));
    TElemType definition[100];
    memset(definition, 0, sizeof(definition));
    int k = -1;
    TElemType temp1;
    int key = -1;
    int LR = -1;
    char filename[100];
    char treename[100];
    status result = OK;
    BiTree address;

    while (op) {
        system("cls");	printf("\n\n");
        printf("                     菜单选项 \n");
        printf("-----------------------------------------------------------------\n");
        printf(" 1. 创建二叉树                           2. 清空二叉树\n");
        printf(" 3. 求二叉树深度                         4. 寻找结点位置并返回地址\n");
        printf(" 5. 给结点赋值                           6. 获得兄弟结点\n");
        printf(" 7. 插入结点                             8. 删除结点\n");
        printf(" 9. 先序遍历                             10. 中序遍历\n");
        printf(" 11. 后序遍历                            12. 按层遍历\n");
        printf(" 13. 将树中的数据读入文件                 14. 将文件数据存入树中\n");
        printf(" 0. 输入0可返回上一级菜单\n");
        printf("-----------------------------------------------------------------\n");
        printf("请选择你的操作[0~14]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
        {
            num = 0;
            for (int i = 0; i < 20; i++)
                nums[i] = 0;
            printf("请输入二叉树的结点key和数据(以-1 null结束)：");
            for (int i = 0;; i++)
            {
                int a;
                char s[10];
                scanf("%d%s", &a, s);
                if (a == -1)   break;
                else
                {
                    definition[i].key = a;
                    strcpy(definition[i].others, s);
                }
            }
            T = treelist.elem[treelist.length - 1].T;
            result1 = CreateBiTree(T, definition);
            if (result1 == OK) printf("创建成功！\n");
            else if (result1 == ERROR) printf("创建失败！\n");
            else if (result1 == OVERFLOW) printf("溢出！\n");
            getchar(); getchar();
            break;
        }
        case 2:
            result1 = ClearBiTree(T);
            printf("清空成功！\n");
            getchar(); getchar();
            break;
        case 3:
            result1 = BiTreeDepth(T);
            printf("深度为%d。\n", result1);
            getchar(); getchar();
            break;
        case 4:
            printf("请输入结点的key值：");
            scanf("%d", &key);
            address = LocateNode(T, key);
            if (!address) printf("无此结点。\n");
            else
            {
                printf("结点为：%d %s ,地址为%p", address->data.key, address->data.others, address);
            }
            getchar(); getchar();
            break;
        case 5:
            printf("请输入要赋值的结点的key：");
            scanf("%d", &key);
            printf("请输入key与数据：");
            scanf("%d%s", &temp1.key, temp1.others);
            result1 = Assign(T, key, temp1);
            if (result1 == ERROR) printf("赋值失败！\n");
            else printf("赋值成功！\n");
            getchar(); getchar();
            break;
        case 6:
            printf("请输入结点的key值：");
            scanf("%d", &key);
            address = GetSibling(T, key);
            if (address == NULL) printf("不存在！\n");
            else if (address) printf("存在兄弟结点，为：%d %s ,地址为%p。\n", address->data.key, address->data.others, address);
            getchar(); getchar();
            break;
        case 7:
            printf("在key结点后插入，请输入结点的key值：");
            scanf("%d", &key);
            printf("输入-1在根节点插入，0插入为左子树，1插入为右子树，你选择：");
            scanf("%d", &LR);
            printf("请输入key与数据：");
            scanf("%d%s", &temp1.key, temp1.others);
            result1 = InsertNode(T, key, LR, temp1);
            if (result1 == OK)
                printf("插入成功！");
            else
                printf("插入失败！");
            getchar(); getchar();
            break;
        case 8:
            printf("请输入结点的key值：");
            scanf("%d", &key);
            result1 = DeleteNode(T, key);
            if (result1 == OK)
                printf("删除成功！");
            else
                printf("删除失败！");
            getchar(); getchar();
            break;
        case 9:
            PreOrderTraverse(T, visit);
            getchar(); getchar();
            break;
        case 10:
            InOrderTraverse(T, visit);
            getchar(); getchar();
            break;
        case 11:
            PostOrderTraverse(T, visit);
            getchar(); getchar();
            break;
        case 12:
            LevelOrderTraverse(T, visit);
            getchar(); getchar();
            break;
        case 13:
            printf("请输入文件名称：");
            scanf("%s", filename);
            SaveBiTree(T, filename);
            printf("保存成功！\n");
            getchar(); getchar();
            break;
        case 14:
            printf("请输入文件名称：");
            scanf("%s", filename);
            LoadBiTree(T, filename);
            printf("传入成功！\n");
            getchar(); getchar();
            break;
        case 0:
            break;
        default:
            printf("输入错误！\n");
            getchar(); getchar();
            break;
        }//end of switch
    }//end of while
    return T;
}
int main()
{
    TREELISTS treelist;
    BiTree T;

    treelist.length = 0;
    char treename[100];
    char filename[100];
    status result = OK;
    int op = 1;
    while (op) {
        system("cls");	printf("\n\n");
        printf("                     菜单选项 \n");
        printf("-----------------------------------------------------------------\n");
        printf("1. 增加二叉树                          2. 删除指定二叉树\n");
        printf("3. 查找二叉树                          4. 选中二叉树\n");
        printf("0. 输入0可退出系统\n");
        printf("-----------------------------------------------------------------\n");
        printf("请选择你的操作[0~4]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            printf("请输入你想添加的二叉树的名称：");
            scanf("%s", treename);
            if (LocateTree(treelist, treename) != 0)
                printf("二叉树已存在!\n");
            else
            {
                AddBiTree(treelist, treename);
                printf("添加成功！\n");
            }
            getchar(); getchar();
            break;
        case 2:
            printf("请输入你想删除的二叉树的名称：");
            scanf("%s", treename);
            result = DelBiTree(treelist, treename);
            if (result == ERROR) printf("二叉树不存在！");
            else printf("删除成功！\n");
            getchar(); getchar();
            break;
        case 3:
            printf("请输入你想查找的二叉树的名称：");
            scanf("%s", treename);
            result = LocateTree(treelist, treename);
            if (result == 0) printf("未找到该二叉树！\n");
            else printf("该二叉树在第%d个。", result);
            getchar(); getchar();
            break;
        case 4:
            printf("请输入你想选中的二叉树的名称：");
            scanf("%s", treename);
            result = LocateTree(treelist, treename);
            if (result != 0)
            {
                T = treelist.elem[result - 1].T;
                treelist.elem[result - 1].T = Second_menu(T,treelist);
            }
            else  printf("不存在！");
            getchar(); getchar();
            break;
        case 0:
            break;
        default:
            printf("输入错误！");
            getchar(); getchar();
            break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
