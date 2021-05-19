#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int KeyType;
typedef struct {
    KeyType  key;
    char others[20];
} TElemType; //������������Ͷ���
typedef struct BiTNode {    //�����������Ķ���
    TElemType data;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;
typedef struct
{
    struct {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
}TREELISTS;

//TREELISTS treelist;
//BiTree T, address;
//int num;
//TElemType  defination[20], temp1;
//int nums[20]�� result, key, LR;
//char treename[20], filename[20];
//TElemType* cp;

status CreateBiTreeTrueFunctionToDoCheckRepeating(BiTree& T, TElemType definition[], int repeating[]);
status CreateBiTree(BiTree& T, TElemType definition[]);
status ClearBiTree(BiTree& T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, KeyType e);
status FindRepetition(BiTree& T, KeyType e);
status Assign(BiTree& T, KeyType e, TElemType value);
BiTNode* GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c);
BiTree FindParent(BiTree T, KeyType e);
status DeleteNode(BiTree& T, KeyType e);
void visit(BiTree T);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
status AddBiTree(TREELISTS& treelist, char treename[]);
status DelBiTree(TREELISTS& treelist, char treename[]);
int LocateTree(TREELISTS treelist, char ListName[]);
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree& T, char FileName[]);