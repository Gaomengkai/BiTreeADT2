#include "Def.h"

status CreateBiTreeTrueFunctionToDoCheckRepeating(BiTree& T,
                                                  TElemType definition[],
                                                  int repeating[],
                                                  TElemType *&cp) {

    if (definition[0].key == 0) {
        T = NULL;
        return OK;
    } else {
        status flag;
        // Check if it is fxxking repeated
        if (repeating[definition[0].key] == 1 && definition[0].key > 0)
            return ERROR;
        else
            repeating[definition[0].key] = 1;
        T = new BiTNode;
        if (!T)return OVERFLOW;

        T->data = definition[0]; // 生成根结点
        cp = definition;
        cp = cp + 1;
        flag = CreateBiTreeTrueFunctionToDoCheckRepeating(
            T->lchild, cp, repeating, cp); // 构造左子树
        if (flag == ERROR)
            return ERROR;
        cp = cp + 1;
        flag = CreateBiTreeTrueFunctionToDoCheckRepeating(
            T->rchild, cp, repeating, cp); // 构造右子树
        if (flag == ERROR)
            return ERROR;
        return OK;
    }
}

status CreateBiTree(BiTree& T, TElemType definition[]) //构造二叉树
{
    ASSERT_EMPTY;
    if (!isEmpty(T))
        return INFEASIBLE;
    const int DEFINITION_NUM = 1000;
    int repeating[DEFINITION_NUM];
    memset(repeating, 0, sizeof(repeating));
    auto cp = definition;
    return CreateBiTreeTrueFunctionToDoCheckRepeating(T, definition, repeating,
                                                      cp);
}

status ClearBiTree(BiTree& T) //清空二叉树
{
    if (!T)
        return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

int BiTreeDepth(BiTree T) //求二叉树T的深度
{
    if (!T) return 0;
    int depth = 0;
    depth++;
    depth += BiTreeDepth(T->lchild) > BiTreeDepth(T->rchild)
                 ? BiTreeDepth(T->lchild)
                 : BiTreeDepth(T->rchild);
    return depth;
}

BiTNode *LocateNode(BiTree T, KeyType e) //查找结点
{
    BiTNode *flag = NULL;
    if (!T)
        return flag;
    if ((T->data).key == e) {
        flag = T;
        return flag;
    }
    flag = LocateNode(T->lchild, e);
    if (flag != NULL)
        return flag;
    flag = LocateNode(T->rchild, e);
    return flag;
}

status FindRepetition(BiTree &T, KeyType e) {
    /// <summary>
    /// 判断是否有key为e的结点
    /// </summary>
    /// <param name="T"></param>
    /// <param name="e"></param>
    /// <returns></returns>
    ASSERT_NOT_EMPTY;
    int flag = OK;
    if (!T) {
        return OK;
    } else {
        if ((T->data).key == e)
            return ERROR;
        flag = FindRepetition(T->lchild, e);
        if (flag == ERROR)
            return ERROR;
        flag = FindRepetition(T->rchild, e);
        if (flag == ERROR)
            return ERROR;
        return flag;
    }
}

status Assign(BiTree &T, KeyType e, TElemType valve) //实现结点赋值。
{
    ASSERT_NOT_EMPTY;
    BiTree flag;
    int res;
    if (e != valve.key) {
        res = FindRepetition(T, valve.key);
        if (res == ERROR)
            return ERROR;
    }
    flag = LocateNode(T, e);
    if (flag == NULL)
        return ERROR;
    (flag->data).key = valve.key;
    strcpy((flag->data).others, valve.others);
    return OK;
}

BiTNode *GetSibling(BiTree T, KeyType e) {
    /// <summary>
    /// 兄弟ノードを取得する
    /// </summary>
    /// <param name="T"></param>
    /// <param name="e"></param>
    /// <returns></returns>
    BiTNode *flag = NULL;
    if (!T)
        return flag;
    if (T->lchild == NULL || T->rchild == NULL)
        return flag; //先找双亲结点
    else if ((T->lchild->data).key == e) {
        flag = T->rchild;
        return flag;
    } else if ((T->rchild->data).key == e) {
        flag = T->lchild;
        return flag;
    }
    flag = GetSibling(T->lchild, e);
    if (flag != NULL)
        return flag;
    flag = GetSibling(T->rchild, e);
    if (flag != NULL)
        return flag;
    return flag;
}

status InsertNode(BiTree &T, KeyType e, int L_or_R, TElemType c) //插入结点。
{
    ASSERT_NOT_EMPTY;
    BiTree flag = LocateNode(T, e);
    if (!flag)
        return ERROR; // ノードeは存在しません
    if (FindRepetition(T, c.key) == ERROR)
        return ERROR; //同じ名前のノードがすでに存在します
    // 新しいノードを初期化します
    BiTNode *r = new BiTNode;
    if (!r)
        return OVERFLOW;

    if (L_or_R == ROOT) {
        r->data = c;
        r->rchild = T;
        r->lchild = NULL;
        T = r;
        return OK;
    } else if (L_or_R == LEFT) {
        BiTree Lnode = flag->lchild;
        flag->lchild = r;
        r->data = c;
        r->rchild = Lnode;
        r->lchild = NULL;
        return OK;
    } else if (L_or_R == RIGHT) {
        BiTree Rnode = flag->rchild;
        flag->rchild = r;
        r->data = c;
        r->rchild = Rnode;
        r->lchild = NULL;
        return OK;
    }
    return ERROR;
}

BiTree FindParent(BiTree T, KeyType e) {
    if (!T)
        return NULL; // 空の二分木を操作することはできません
    BiTNode *flag = NULL;
    if (T->lchild == NULL && T->rchild == NULL)
        return NULL; // T没有孩子结点，即没有结点的双亲结点是T
    else if (T->lchild != NULL && T->rchild == NULL) {
        if (T->lchild->data.key == e)
            return T;
    } else if (T->rchild != NULL && T->lchild == NULL) {
        if (T->rchild->data.key == e)
            return T;
    } else if (T->lchild->data.key == e || T->rchild->data.key == e)
        return T;
    flag = FindParent(T->lchild, e);
    if (flag != NULL)
        return flag;
    flag = FindParent(T->rchild, e);
    return flag;
}
status DeleteNode(BiTree &T, KeyType e) //删除结点。
{
    ASSERT_NOT_EMPTY;
    BiTree Loc_e = LocateNode(T, e); // To find the location of "e"
    if (!Loc_e)
        return ERROR;

    BiTree pl = NULL, pr = NULL, parent;
    parent = FindParent(T, e); // To find the parent of Node "e"
    // if (!parent) return ERROR;
    if (!Loc_e->lchild && !Loc_e->rchild &&
        parent) // Case: e has no child (e is a leaf)
    {
        if (parent->lchild == Loc_e)
            parent->lchild = NULL;
        if (parent->rchild == Loc_e)
            parent->rchild = NULL;
        free(Loc_e);
        Loc_e = NULL;
        return OK;
    }
    /* eはルートノードではありません */
    if (Loc_e != T) {
        if (!parent)
            return ERROR;
        if (parent->lchild == Loc_e)
            pl = Loc_e;
        else if (parent->rchild == Loc_e)
            pr = Loc_e;
    } else { /* eはルートノードです */
        if (Loc_e->lchild == NULL && Loc_e->rchild) // deg == 1
            T = Loc_e->rchild;
        else if (Loc_e->rchild == NULL && Loc_e->lchild)
            T = Loc_e->lchild;
        else if (Loc_e->rchild == NULL &&
                 Loc_e->lchild == NULL) /* 直接リリース */
        {
            free(Loc_e);
            return OK;
        } else // deg == 2
        {
            BiTree temp1 = Loc_e->lchild, temp2 = temp1->rchild;
            while (temp2) //找左子树的最右结点
            {
                temp1 = temp2;
                temp2 = temp2->rchild;
            }
            temp1->rchild = Loc_e->rchild;
            T = Loc_e->lchild;
            free(Loc_e);
            Loc_e = NULL;
        }
        return OK;
    }
    if (Loc_e->lchild && !Loc_e->rchild) //结点e不是根节点且度为1
    {
        if (pl)
            parent->lchild =
                Loc_e->lchild; // parent为空指针的情况在上面已经讨论过
        else if (pr)
            parent->rchild = Loc_e->lchild;
        free(Loc_e);
        Loc_e = NULL;
    } else if (Loc_e->rchild && !Loc_e->lchild) //结点e不是根节点且度为1
    {
        if (pl)
            parent->lchild = Loc_e->rchild;
        else if (pr)
            parent->rchild = Loc_e->rchild;
        free(Loc_e);
        Loc_e = NULL;
    } else if (Loc_e->rchild && Loc_e->lchild) //结点e不是根节点且度为2
    {
        if (parent->lchild == Loc_e)
            parent->lchild = Loc_e->lchild;
        if (parent->rchild == Loc_e)
            parent->rchild = Loc_e->lchild;
        BiTree temp1 = Loc_e->lchild, temp2 = temp1->rchild;
        while (temp2) {
            temp1 = temp2;
            temp2 = temp2->rchild;
        }
        temp1->rchild = Loc_e->rchild;
        if (Loc_e == T)
            T = pl;
        free(Loc_e);
        Loc_e = NULL;
    }
    return OK;
}
/// <summary>
/// 访问函数
/// </summary>
/// <param name="T">树</param>
void visit(BiTree T) { printf(" %d,%s", T->data.key, T->data.others); }
/// <summary>
/// 先序遍历 递归
/// </summary>
/// <param name="T">树</param>
/// <param name="visit">访问函数</param>
/// <returns></returns>
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    ASSERT_NOT_EMPTY;
    if (T) {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
}
/// <summary>
/// 中序 非递归遍历
/// </summary>
/// <param name="T">树</param>
/// <param name="visit">访问函数</param>
/// <returns></returns>
status InOrderTraverse(BiTree T,
                       void (*visit)(BiTree))
{
    ASSERT_NOT_EMPTY;
    struct BiTNode *st[MAX_QUEUE_DEPTH]; // the simulated pointer stack
    int top = 0;   // set stack to EMPTY
    BiTree t = T;
    do {
        while (t) //根指针t表示的为非空二叉树
        {
            if (top == MAX_QUEUE_DEPTH-1)
                exit(OVERFLOW);
            st[++top] = t;
            t = t->lchild;// t was tuened to left child
        } // Left Tree was OK
        if (top) 
        {
            t = st[top--];
            visit(t);      //弹出根指针访问根结点
            t = t->rchild; //遍历右子树
        }
    } while (top || t);
    return ERROR;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree)) //后序遍历二叉树T
{
    ASSERT_NOT_EMPTY;
    if (T) {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
    }
    return OK;
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) //按层遍历二叉树T
{
    BiTree q[MAX_QUEUE_DEPTH];
    int head = 0;
    if (T) {
        q[head++] = T;
    }
    while (head > 0) {
        if (head == MAX_QUEUE_DEPTH - 1)
            return OVERFLOW; // OVERFLOW!!
        BiTree p = *q;
        visit(p);
        head--;
        // Seq the queue
        for (int i = 0; i < head; ++i)
            q[i] = q[i + 1];
        if (p->lchild)
            q[head++] = p->lchild;
        if (p->rchild)
            q[head++] = p->rchild;
    }
    return OK;
}

/// <summary>
/// 添加一个二叉树
/// </summary>
/// <param name="treelist">总的二叉树列表</param>
/// <param name="treename">二叉树名字</param>
/// <returns>ERROR (Too Many / Repeat) or OK</returns>
status AddBiTree(TREELISTS &treelist, char treename[]) {
    if (treelist.length >= 10)
        return ERROR;
    for (int i = 0; i < treelist.length; ++i) {
        if (strcmp(treelist.elem[i].name, treename) == 0)
            return ERROR;
    }
    /* ノードを初期化します */
    strcpy(treelist.elem[treelist.length].name, treename);
    treelist.elem[treelist.length].T = NULL;
    treelist.length++;
    return OK;
}

/// <summary>
/// 在总的列表中删除一个二叉树
/// </summary>
/// <param name="treelist">总的列表</param>
/// <param name="treename">二叉树名字</param>
/// <returns>ERROR / OK</returns>
status DelBiTree(TREELISTS &treelist, char treename[]) // 二分木を削除する
{
    for (int i = 0; i < treelist.length; i++) {
        if (!strcmp(treename, treelist.elem[i].name)) {
            ClearBiTree(treelist.elem[i].T);
            for (int j = i; j < treelist.length; j++) {
                strcpy(treelist.elem[i].name, treelist.elem[i + 1].name);
                treelist.elem[i].T = treelist.elem[i + 1].T;
            }
            treelist.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateTree(TREELISTS treelist, char ListName[]) // 查找二叉树
{
    for (int i = 0; i < treelist.length; i++) {
        if (!strcmp(ListName, treelist.elem[i].name))
            return i + 1;
    }
    return 0;
}

status SaveBiTree(BiTree T,
                  char FileName[]) //将二叉树的结点数据写入到文件FileName中
{
    /// <summary>
    /// Save BiTree to a certain file
    /// </summary>
    /// <param name="T">Root of BiTree</param>
    /// <param name="FileName">FileName</param>
    /// <returns>INFEASIBLE, FILEERROR, ERROR, OK</returns>
    if (!T) return INFEASIBLE;
    char rs[100] = "null";
    FILE *fp = fopen(FileName, "wt");
    if (!fp)
        return FILEERROR;
    BiTree s[100];
    int top = 0;
    do {
        while (T) {
            s[++top] = T;
            fprintf(fp, "%d %s ", T->data.key, T->data.others); //非递归前序遍历
            T = T->lchild;
        }
        fprintf(fp, "%d %s ", 0, rs); //输出0表示为空树
        if (top) {
            T = s[top--];
            T = T->rchild;
        }
    } while (top || T);
    fprintf(fp, "%d %s ", 0, rs); //输出0表示为空树
    fprintf(fp, "-1 null ");
    fclose(fp);

    return OK;
}

status LoadBiTree(BiTree &T,
                  char FileName[]) //读入文件FileName的结点数据，创建二叉树
{
    if (T) return INFEASIBLE;
    TElemType def1[20];
    memset(def1, 0, sizeof(def1));
    FILE *fp = fopen(FileName, "r");
    if (!fp)
        return FILEERROR;
    for (int i = 0;; i++) {
        fscanf(fp, "%d%s", &def1[i].key, def1[i].others);
        if (def1[i].key == -1)
            break;
    }
    CreateBiTree(T, def1);
    fclose(fp);
    return OK;
}

inline bool isEmpty(BiTree T) {
    if (T)
        return false;
    else
        return true;
}