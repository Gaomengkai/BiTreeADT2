#include "Def.h"

status CreateBiTreeTrueFunctionToDoCheckRepeating(
    BiTree&     T,
    TElemType   definition[],
    int         repeating[], 
    TElemType*  &cp) {

    if (definition[0].key == 0) {
        T = NULL;
        return OK;
    } else {
        status flag;
        // Check if it is fxxking repeated
        if (repeating[definition[0].key] == 1 && definition[0].key > 0)
            return ERROR;
        else repeating[definition[0].key] = 1;

        if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
            return OVERFLOW;
        T->data = definition[0]; // ���ɸ����
        cp = definition;
        cp = cp + 1;
        flag = CreateBiTreeTrueFunctionToDoCheckRepeating(T->lchild, cp,repeating,cp); // ����������
        if (flag == ERROR) return ERROR;
        cp = cp + 1;
        flag = CreateBiTreeTrueFunctionToDoCheckRepeating(T->rchild, cp,repeating,cp); // ����������
        if (flag == ERROR) return ERROR;
        return OK;
    }
}

status CreateBiTree(BiTree& T, TElemType definition[])//���������
{
    const int DEFINITION_NUM = 1000;
    int repeating[DEFINITION_NUM];
    memset(repeating, 0, sizeof(repeating));
    auto cp = definition;
    return CreateBiTreeTrueFunctionToDoCheckRepeating(T, definition, repeating, cp);
}

status ClearBiTree(BiTree& T)//��ն�����
{
    if (!T) return OK;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

int BiTreeDepth(BiTree T) //�������T�����
{
    if (!T) return 0;
    int depth = 0;
    depth++;
    depth += BiTreeDepth(T->lchild) > BiTreeDepth(T->rchild) ? BiTreeDepth(T->lchild) : BiTreeDepth(T->rchild);
    return depth;
}

BiTNode* LocateNode(BiTree T, KeyType e)  //���ҽ��
{
    BiTNode* flag = NULL;
    if (!T) return flag;
    if ((T->data).key == e)
    {
        flag = T;
        return flag;
    }
    flag = LocateNode(T->lchild, e);
    if (flag != NULL) return flag;
    flag = LocateNode(T->rchild, e);
    if (flag != NULL) return flag;
    return flag;
}

status FindRepetition(BiTree& T, KeyType e) {
    /// <summary>
    /// �ж��Ƿ���keyΪe�Ľ��
    /// </summary>
    /// <param name="T"></param>
    /// <param name="e"></param>
    /// <returns></returns>
    int flag = OK;
    if (!T)
    {
        return OK;
    }
    else
    {
        if ((T->data).key == e) return ERROR;
        flag = FindRepetition(T->lchild, e);
        if (flag == ERROR) return ERROR;
        flag = FindRepetition(T->rchild, e);
        if (flag == ERROR) return ERROR;
        return flag;
    }
}

status Assign(BiTree& T, KeyType e, TElemType valve)  //ʵ�ֽ�㸳ֵ��   ******
{
    BiTree flag;
    int res;
    if (e != valve.key)
    {
        res = FindRepetition(T, valve.key);
        if (res == ERROR)
            return ERROR;
    }
    flag = LocateNode(T, e);
    if (flag == NULL) return ERROR;
    (flag->data).key = valve.key;
    strcpy((flag->data).others, valve.others);
    return OK;
}

BiTNode* GetSibling(BiTree T, KeyType e)  //����ֵܽ��
{
    BiTNode* flag = NULL;
    if (!T) return flag;
    if (T->lchild == NULL || T->rchild == NULL) return flag; //����˫�׽��
    else
        if ((T->lchild->data).key == e)
        {
            flag = T->rchild;
            return flag;
        }
        else if ((T->rchild->data).key == e)
        {
            flag = T->lchild;
            return flag;
        }
    flag = GetSibling(T->lchild, e);
    if (flag != NULL) return flag;
    flag = GetSibling(T->rchild, e);
    if (flag != NULL) return flag;
    return flag;
}


status InsertNode(BiTree& T, KeyType e, int LR, TElemType c)  //�����㡣
{
    BiTree flag = LocateNode(T, e);
    if (FindRepetition(T, c.key) == ERROR) return ERROR;  //ԭ����������keyΪc.key�Ľ��
    if (LR == -1)  //�ڸ��ڵ�ǰ����
    {
        BiTNode* r = (BiTNode*)malloc(sizeof(BiTNode));
        if (!r) return OVERFLOW;
        r->data = c;
        r->rchild = T;
        r->lchild = NULL;
        T = r;
        return OK;
    }
    if (!flag) return ERROR;  //û�н��e

    if (LR == 0)  //����Ϊ���ӽ��
    {
        BiTNode* r = (BiTNode*)malloc(sizeof(BiTNode));
        if (!r) return OVERFLOW;
        BiTree Lnode = flag->lchild;
        flag->lchild = r;
        r->data = c;
        r->rchild = Lnode;
        r->lchild = NULL;
        return OK;
    }
    if (LR == 1)  //����Ϊ�Һ��ӽ��
    {
        BiTNode* r = (BiTNode*)malloc(sizeof(BiTNode));
        if (!r) return OVERFLOW;
        BiTree Rnode = flag->rchild;
        flag->rchild = r;
        r->data = c;
        r->rchild = Rnode;
        r->lchild = NULL;
        return OK;
    }
}

BiTree FindParent(BiTree T, KeyType e)  //����������ڲ���˫�׽��ĺ���
{
    BiTNode* flag = NULL;
    if (!T) return flag;  //TΪ�ն�����
    if (T->lchild == NULL && T->rchild == NULL) return flag;  //Tû�к��ӽ�㣬��û�н���˫�׽����T
    else if (T->lchild != NULL && T->rchild == NULL) //���ӽ��ΪnullҪ�����ó�����������ɵ�ַ���ʴ���
    {
        if (T->lchild->data.key == e) //����Ϊ���e
        {
            flag = T;
            return flag;
        }
    }
    else if (T->rchild != NULL && T->lchild == NULL)
    {
        if (T->rchild->data.key == e)  //�Һ���Ϊ���e
        {
            flag = T;
            return flag;
        }
    }
    else
        if (T->lchild->data.key == e || T->rchild->data.key == e)  //���������ӽ��
        {
            flag = T;
            return flag;
        }
    flag = FindParent(T->lchild, e);
    if (flag != NULL) return flag;
    flag = FindParent(T->rchild, e);
    if (flag != NULL) return flag;
    return flag;
}
status DeleteNode(BiTree& T, KeyType e)  //ɾ����㡣
{
    BiTree Loc_e = LocateNode(T, e);  // To find the location of "e"
    if (!Loc_e) return ERROR;

    BiTree pl = NULL, pr = NULL, parent;
    parent = FindParent(T, e);  // To find the parent of Node "e"
    //if (!parent) return ERROR;
    if (!Loc_e->lchild && !Loc_e->rchild && parent) // Case: e has no child (e is a leaf)
    {
        if (parent->lchild == Loc_e)  parent->lchild = NULL;
        if (parent->rchild == Loc_e)  parent->rchild = NULL;
        free(Loc_e);
        Loc_e = NULL;
        return OK;
    }
    /* e�ϥ�`�ȥΩ`�ɤǤϤ���ޤ��� */
    if (Loc_e != T)
    {
        if (!parent) return ERROR;
        if (parent->lchild == Loc_e)
            pl = Loc_e;
        else if (parent->rchild == Loc_e)
            pr = Loc_e;
    }
    else {/* e�ϥ�`�ȥΩ`�ɤǤ� */
        if (Loc_e->lchild == NULL && Loc_e->rchild)  //deg == 1
            T = Loc_e->rchild;
        else if (Loc_e->rchild == NULL && Loc_e->lchild)
            T = Loc_e->lchild;
        else if (Loc_e->rchild == NULL && Loc_e->lchild == NULL)  /* ֱ�ӥ��`�� */
        {
            free(Loc_e);
            return OK;
        }
        else  //deg == 2
        {
            BiTree temp1 = Loc_e->lchild, temp2 = temp1->rchild;
            while (temp2)   //�������������ҽ��
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
    if (Loc_e->lchild && !Loc_e->rchild)  //���e���Ǹ��ڵ��Ҷ�Ϊ1
    {
        if (pl)
            parent->lchild = Loc_e->lchild;//parentΪ��ָ�������������Ѿ����۹�
        else if (pr)
            parent->rchild = Loc_e->lchild;
        free(Loc_e);
        Loc_e = NULL;
    }
    else if (Loc_e->rchild && !Loc_e->lchild)//���e���Ǹ��ڵ��Ҷ�Ϊ1
    {
        if (pl)
            parent->lchild = Loc_e->rchild;
        else if (pr)
            parent->rchild = Loc_e->rchild;
        free(Loc_e);
        Loc_e = NULL;
    }
    else if (Loc_e->rchild && Loc_e->lchild) //���e���Ǹ��ڵ��Ҷ�Ϊ2
    {
        if (parent->lchild == Loc_e)
            parent->lchild = Loc_e->lchild;
        if (parent->rchild == Loc_e)
            parent->rchild = Loc_e->lchild;
        BiTree temp1 = Loc_e->lchild, temp2 = temp1->rchild;
        while (temp2)
        {
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

void visit(BiTree T)
{
    printf(" %d,%s", T->data.key, T->data.others);
}
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))  //�������������T
{
    if (T)
    {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree))  //�������������T���ǵݹ飩
{
    struct BiTNode* st[20]; //����ָ��ջst[20]
    int top = 0; //�ÿ�ջ
    BiTree t = T;
    do
    {
        while (t) //��ָ��t��ʾ��Ϊ�ǿն�����
        {
            if (top == 19) exit(OVERFLOW);//ջ����,�˳�
            st[++top] = t; //��ָ���ջ(�ǿ�ָ�룩
            t = t->lchild; //t����������
        }//ѭ��������ʾ��ջ��Ԫ��Ϊ��ָ��Ķ���������������������
        if (top) //Ϊ�ǿ�ջ
        {
            t = st[top--];
            visit(t);//������ָ����ʸ����
            t = t->rchild; //����������
        }
    } while (top || t);
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree))  //�������������T
{
    if (T)
    {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
    }
    return OK;
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))   //�������������T
{
    BiTree st[20];  //����һ������
    int head = 0;
    if (T)
    {
        st[head++] = T;
    }
    while (head > 0)
    {
        if (head == 19) return OVERFLOW;
        BiTree p = *st;
        visit(p);
        head--;
        for (int i = 0; i < head; i++)
            st[i] = st[i + 1];
        if (p->lchild)
            st[head++] = p->lchild;
        if (p->rchild)
            st[head++] = p->rchild;
    }
    return OK;
}

status AddBiTree(TREELISTS& treelist, char treename[])
{
    TElemType defination[20];
    if (treelist.length == 10)   return ERROR;
    strcpy(treelist.elem[treelist.length].name, treename);
    treelist.length++;
    return OK;
}

status DelBiTree(TREELISTS& treelist, char treename[]) //ɾ��������
{
    for (int i = 0; i < treelist.length; i++)
    {
        if (!strcmp(treename, treelist.elem[i].name))
        {
            ClearBiTree(treelist.elem[i].T);
            for (int j = i; j < treelist.length; j++)
            {
                strcpy(treelist.elem[i].name, treelist.elem[i + 1].name);
                treelist.elem[i].T = treelist.elem[i + 1].T;
            }
            treelist.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateTree(TREELISTS treelist, char ListName[])// ���Ҷ�����
{
    for (int i = 0; i < treelist.length; i++)
    {
        if (!strcmp(ListName, treelist.elem[i].name))
            return i + 1;
    }
    return 0;
}

status SaveBiTree(BiTree T, char FileName[]) //���������Ľ������д�뵽�ļ�FileName��
{
    char rs[] = "null";
    FILE* fp = fopen(FileName, "wt");
    if (fp == NULL) exit(-1);
    BiTree s[100];
    int top = 0;
    do
    {
        while (T)
        {
            s[++top] = T;
            fprintf(fp, "%d %s ", T->data.key, T->data.others);//�ǵݹ�ǰ�����
            T = T->lchild;
        }
        fprintf(fp, "%d %s ", 0, rs);//���0��ʾΪ����
        if (top)
        {
            T = s[top--];
            T = T->rchild;
        }
    } while (top || T);
    fprintf(fp, "%d %s ", 0, rs);//���0��ʾΪ����
    fprintf(fp, "-1 null ");
    fclose(fp);

    return OK;
}

status LoadBiTree(BiTree& T, char FileName[])  //�����ļ�FileName�Ľ�����ݣ�����������
{
    TElemType defination[20];
    FILE* fp = fopen(FileName, "r");
    if (!fp) exit(-1);
    for (int i = 0;; i++)
    {
        fscanf(fp, "%d%s", &defination[i].key, defination[i].others);
        if (defination[i].key == -1)
            break;
    }
    CreateBiTree(T, defination);
    fclose(fp);
    return OK;
}
