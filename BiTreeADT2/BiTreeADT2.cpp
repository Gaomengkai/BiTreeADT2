#include "BiTreeADT2.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define PAUSE system("pause >>nul");

BiTree Second_menu(BiTree T, TREELISTS& treelist) {
	int op = 1;
	int st;

	int num = 0;
	int nums[MAX_N_NODES];
	memset(nums, 0, sizeof(nums));
	TElemType definition[100];
	memset(definition, 0, sizeof(definition));
	int k = -1;
	TElemType tempElemType;
	int key = -1;
	int L_or_R = -1;
	char filename[100];

	status result = OK;
	BiTree addr;

	while (op) {
		system("cls");
		printf("\n\n");
		printf("                     菜单选项 \n");
		printf("---------------------------------------------------------------"
			"--\n");
		printf(" 1. 创建二叉树                         2. 清空二叉树\n");
		printf(" 3. 求二叉树深度                       4. "
			"寻找结点位置并返回地址\n");
		printf(" 5. 给结点赋值                         6. 兄弟结点\n");
		printf(" 7. 插入结点                           8. 删除结点\n");
		printf(" 9. 先序遍历                       10. 中序遍历\n");
		printf(" 11. 后序遍历                          12. 按层遍历\n");
		printf(" 13. 保存文件              14. "
			"加载文件\n");
		printf(" 0. 输入0可返回上一级菜单\n");
		printf("---------------------------------------------------------------"
			"--\n");
		printf("您的选择：");
		cin >> op;
		switch (op) {
		case 1: {
			if (!isEmpty(T)) {
				cout << "表不为空。禁止操作！\n";
				break;
			}
			num = 0;
			memset(nums, 0, sizeof(nums));
			printf("请输入二叉树的结点key和数据(以-1 null结束)：");
			for (int i = 0;; i++) {
				int a;
				char s[20];

				cin >> a >> s;
				if (a == -1)
					break;
				else {
					definition[i].key = a;
					strcpy(definition[i].others, s);
				}
			}
			//T = treelist.elem[treelist.length - 1].T;
			st = CreateBiTree(T, definition);
			if (st == OK)
				printf("创建成功！\n");
			else if (st == ERROR)
				printf("创建失败！\n");
			else if (st == OVERFLOW)
				printf("溢出！\n");
			break;
		}
		case 2:
			st = ClearBiTree(T);
			if (st == OK)
				cout << "SUCCEED!\n";
			else if (st == INFEASIBLE)
				cout << "线性表不为空！\n";
			break;
		case 3:
			st = BiTreeDepth(T);
			if (st == INFEASIBLE)
				cout << "二叉树不存在！\n";
			else
				cout << "深度为 " << st << endl;
			break;
		case 4:
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			cout << "请输入结点的key值： ";
			cin >> key;
			addr = LocateNode(T, key);
			if (!addr)
				printf("无此结点。\n");
			else {
				printf("结点为：%d %s ,地址为%p", addr->data.key,
					addr->data.others, addr);
			}
			break;
		case 5:
			// 赋值
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			cout << "请输入要赋值的结点的key：";
			cin >> key;
			cout << "\n请输入key与数据：";
			cin >> tempElemType.key >> tempElemType.others;
			st = Assign(T, key, tempElemType);
			if (st == OK)
				cout << "[+]\tSUCCEED!\n";
			else if (st == INFEASIBLE)
				cout << "[-]\tNo BiTree\n";
			else if (st == ERROR)
				cout << "[-]\tERROR\n";
			break;
		case 6:
			// 获取兄弟节点
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			cout << "请输入结点的key值：";
			cin >> key;
			addr = GetSibling(T, key);
			if (addr == NULL)
				printf("[-]\t不存在！\n");
			else if (addr)
				printf("存在兄弟结点，为：%d %s ,地址为%p。\n",
					addr->data.key, addr->data.others, addr);
			break;
		case 7:
			// 插入
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			printf("在key结点后插入，请输入结点的key值：");
			cin >> key;
			printf(
				"输入-1在根节点插入，0插入为左子树，1插入为右子树，你选择：");
			cin >> L_or_R;
			printf("请输入key与数据：");
			cin >> tempElemType.key >> tempElemType.others;
			st = InsertNode(T, key, L_or_R, tempElemType);
			if (st == OK)
				printf("插入成功！");
			else
				printf("插入失败！");
			break;
		case 8:
			// ノードを削除します
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			printf("请输入结点的key值：");
			cin >> key;
			st = DeleteNode(T, key);
			if (st == OK)
				printf("删除成功！");
			else
				printf("删除失败！");
			break;
		case 9:
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			PreOrderTraverse(T, visit);
			break;
		case 10:
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			InOrderTraverse(T, visit);
			break;
		case 11:
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			PostOrderTraverse(T, visit);
			break;
		case 12:
			if (isEmpty(T)) {
				cout << "表为空。禁止操作！\n";
				break;
			}
			LevelOrderTraverse(T, visit);
			break;
		case 13:
			// ファイルを保存
			if (isEmpty(T)) {
				cout << "二分木が空で、操作が禁止されています！\n";
				break;
			}
			printf("请输入文件名称：");
			cin >> filename;
			st = SaveBiTree(T, filename);
			if (st == FILEERROR) {
				cout << "文件打开错误！";
			}
			else
				printf("保存成功！\n");
			break;
		case 14:
			// ファイルを読む
			if (!isEmpty(T)) {
				cout << "二分木は空ではなく、操作は禁止されています\n";
				break;
			}
			printf("请输入文件名称：");
			cin >> filename;
			st = LoadBiTree(T, filename);
			if (st == FILEERROR) {
				cout << "文件打开错误！";
			}
			else
				printf("导入成功！\n");
			break;
		case 0:
			return T;
			break;
		default:
			printf("你惊扰了Witch！\n");
			break;
		} // end of switch
		PAUSE;
	} // end of while
	return T;
}
int main() {
	TREELISTS treelist;
	BiTree T = NULL;

	treelist.length = 0;
	memset(&treelist, 0, sizeof(treelist));
	char treename[100];
	char filename[100];
	status result = OK;
	int op = 1;
	while (op) {
		system("cls");
		printf("\n");
		printf("                     主菜单（多二叉树管理） \n");
		printf("---------------------------------------------------------------"
			"--\n");
		printf("1. 增加二叉树                          2. 删除指定二叉树\n");
		printf("3. 查找二叉树                          4. 选中二叉树\n");
		printf("5. 保存某个二叉树                      6. 从文件加载二叉树\n");
		puts("100. 声明。\n");
		printf("0. 输入0可退出系统\n");
		printf("---------------------------------------------------------------"
			"--\n");
		printf("君の選択:");
		cin >> op;
		switch (op) {
		case 1:
			printf("请输入你想添加的二叉树的名称：");
			cin >> treename;
			if (LocateTree(treelist, treename) != 0)
				printf("二叉树已存在!\n");
			else {
				AddBiTree(treelist, treename);
				printf("添加成功！\n");
			}
			break;
		case 2:
			printf("请输入你想删除的二叉树的名称：");
			cin >> treename;
			result = DelBiTree(treelist, treename);
			if (result == ERROR)
				cout << "不存在您说的二叉树！\n選択した二分木は存在しません: " << treename;
			else
				printf("删除成功！\n");
			break;
		case 3:
			printf("请输入你想查找的二叉树的名称：");
			cin >> treename;
			result = LocateTree(treelist, treename);
			if (result == 0)
				cout << "不存在您说的二叉树！\n選択した二分木は存在しません: " << treename;
			else
				printf("该%s二叉树在第%d个。", treename, result);
			break;
		case 4:
			printf("请输入你想选中的二叉树的名称：");
			cin >> treename;
			result = LocateTree(treelist, treename);
			if (result != 0) {
				T = treelist.elem[result - 1].T;
				treelist.elem[result - 1].T = Second_menu(T, treelist);
			}
			else
				cout << "不存在您说的二叉树！\n選択した二分木は存在しません: " << treename;
			break;
		case 5:
			cout << "请输入要保存的二叉树名：";
			cin >> treename;
			result = LocateTree(treelist, treename);
			if (result == 0) {
				cout << "選択した二分木は存在しません!\n";
				break;
			}
			else {
				T = treelist.elem[result - 1].T;
				if (isEmpty(T)) {
					cout << "二分木が空で、操作が禁止されています！\n";
					break;
				}
				cout << "请输入要保存的文件名：";
				cin >> filename;
				result = SaveBiTree(T, filename);
				if (result == FILEERROR) cout << "ファイルオープンエラー\n";
				else if (result == OK) cout << "保存成功！\n";
				else if (result == INFEASIBLE) cout << "二分木が空で\n";
				break;
			}
		case 6:
			cout << "请输入要读取的文件名：";
			cin >> filename;
			cout << "输入要保存的二叉树名字：";
			cin >> treename;
			if (LocateTree(treelist, treename) != 0) {
				printf("二叉树已存在!\n");
				break;
			}
			else {
				AddBiTree(treelist, treename);
				printf("添加成功！\n");
			}
			result = LoadBiTree(treelist.elem[treelist.length - 1].T, filename);
			if (result == OK) cout << "读取成功！\n";
			else if (result == FILEERROR)cout << "文件读取错误！\n";
			else if (result == ERROR)cout << "未知错误！\n";
			else if (result == INFEASIBLE)cout << "二叉树不可操作！\n";
			else cout << "：（\t未知错误！！！\n";
			break;
		case 0:
			return 0;
			// break;
		default:
			printf("高盟凯U202015490");
			break;
		} // end of switch
		PAUSE;
	}     // end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}
