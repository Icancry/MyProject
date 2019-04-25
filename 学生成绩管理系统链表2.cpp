// 学生成绩管理系统链表2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 环境：VS2017  开发人员：cxx  时间：2019/4/25 21:30

#include "pch.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node
{
	char num[10];
	char name[10];
	int score;
	struct Node *Next;
}Stu;//定义学生结构体
void interface();               //菜单界面
void meau();                    //主菜单
void print_list(Stu *pHead);    //遍历链表
void inquire_Stu(Stu *pHead);   //查询
void input_stu(Stu *pHead);     //添加
void delete_Stu(Stu *pHead);    //删除
void modify_Stu(Stu *pHead);    //修改
void Save_Data(Stu *Head);      //保存数据到文件
Stu *Read_Data();				//从文件读取到链表
Stu *creat_node(char num[10], char name[10], int score);      //创建学生结点
void insert_node(Stu *pHead, char num[10], char name[10], int score);  //插入结点
int list_length(Stu *pHead);       //链表长度
float average_score(Stu *pHead);   //求平均分
Stu *Sequence(Stu *pHead);         //排序
void clear_list(Stu *pHead);       //清空链表

void interface()
{
	printf("\t\t\t\t\t******************************\n");
	printf("\t\t\t\t\t*  欢迎来到学生成绩管理系统  *\n");
	printf("\t\t\t\t\t*     1、录入学生成绩        *\n");
	printf("\t\t\t\t\t*     2、打印学生成绩        *\n");
	printf("\t\t\t\t\t*     3、查找学生成绩        *\n");
	printf("\t\t\t\t\t*     4、删除学生成绩        *\n");
	printf("\t\t\t\t\t*     5、修改学生成绩        *\n");
	printf("\t\t\t\t\t*     6、清空所有数据        *\n");
	printf("\t\t\t\t\t*     7、退出管理系统        *\n");
	printf("\t\t\t\t\t******************************\n");
}

Stu *creat_list()
{
	Stu *pHead = (Stu *)malloc(sizeof(Stu));
	if (pHead == NULL)
	{
		printf("申请内存失败！\n");
		exit(0);
	}
	pHead->Next = NULL;
	return (pHead);
}          

int list_length(Stu *pHead)
{
	int len = 0;
	Stu *p = pHead;
	while (p ->Next!= NULL)
	{
		p = p->Next;
		len++;
	}
	return len;
}

float average_score(Stu *pHead)
{
	Stu *p = pHead->Next;
	float sum = 0.0;
	float avg = 0.0;
	if (pHead->Next == NULL)
	{
		return 0.0;
	}
	while (p != NULL)
	{
		sum += p->score;
		p = p->Next;
	}
	avg = (sum / list_length(pHead));
	return avg;
}

Stu * creat_node(char num[10],char name[10],int score)
{
	Stu *NewNode = (Stu *)malloc(sizeof(Stu));
	strcpy_s(NewNode->num, 10,num);
	strcpy_s(NewNode->name, 10,name);
	NewNode->score = score;
	NewNode->Next = NULL;
	return (NewNode);
}

void insert_node(Stu *pHead, char num[10], char name[10], int score)
{
	Stu *NewNode = creat_node(num,name,score);
	//pHead->Next = NewNode;
	//pHead = NewNode;
	NewNode->Next = pHead->Next;
	pHead->Next = NewNode;
}

void inquire_Stu(Stu *pHead)
{
	int flag = 0;
	Stu *pMove = (Stu *)malloc(sizeof(Stu));
	char Stu_Name[10] = { 0 };
	printf("\t\t\t\t\t请输入你要查找的学生姓名：");
	scanf_s("%s", Stu_Name, sizeof(Stu_Name));
	pMove = pHead;
	while (pMove)
	{
		if (strcmp(pMove->name, Stu_Name) == 0)
		{
			printf("\t\t\t\t\t该学生信息：\n");
			printf("\t\t\t\t\t学号：%s \t姓名：%s \t分数：%d\n", pMove->num, pMove->name, pMove->score);
			flag = 1;
		}
		pMove = pMove->Next;
	}
	if (flag == 0)
	{
		printf("\t\t\t\t\t没有找到此学生！\n");
	}
}

void delete_Stu(Stu *pHead)
{
	Stu *PosNode = (Stu *)malloc(sizeof(Stu));
	Stu *PosNode_front = (Stu *)malloc(sizeof(Stu));
	PosNode = pHead->Next;
	PosNode_front = pHead;
	char Stu_Name[10] = { 0 };
	printf("\t\t\t\t\t请输入你要删除学生的名字：");
	scanf_s("%s", Stu_Name, sizeof(Stu_Name));
	if (PosNode == NULL)
	{
		printf("无法操作，链表为空！");
	}
	else
	{
		while (strcmp(PosNode->name, Stu_Name) != 0)
		{
			PosNode_front = PosNode;
			PosNode = PosNode_front->Next;
			if (PosNode == NULL)
			{
				printf("\t\t\t\t\t\t找不到该学生！\n");
				break;
			}
		}
		PosNode_front->Next = PosNode->Next;
		free(PosNode);
		printf("\t\t\t\t\t删除成功！");
	}
}

void modify_Stu(Stu *pHead)
{
	int flag = 0;
	Stu *p = (Stu *)malloc(sizeof(Stu));
	char Stu_Name[10] = { 0 };
	printf("\t\t\t\t\t请输入你要修改学生的姓名：");
	scanf_s("%s", Stu_Name, sizeof(Stu_Name));
	p = pHead;
	while (p)
	{
		if (strcmp(p->name, Stu_Name) == 0)
		{
			printf("\t\t\t\t\t请输入修改后的学号：");
			scanf_s("%s", p->num, 10);
			printf("\t\t\t\t\t请输入修改后的姓名：");
			scanf_s("%s", p->name, 10);
			printf("\t\t\t\t\t请输入修改后的分数：");
			scanf_s("%d", &p->score);
			flag = 1;
		}
		p = p->Next;
	}
	if (flag == 0)
	{
		printf("\t\t\t\t\t没有找到此学生！\n");
	}

}

Stu *Sequence(Stu *pHead)
{
	Stu *p = NULL;
	int t;
	char name[10];
	char num[10];
	int len = list_length(pHead);
	if (pHead==NULL||pHead->Next == NULL)
	{
		return pHead;
	}
	for (int i = 1; i < len; i++)
	{
		p = pHead->Next;
		for (int j = 0; j < len - i ; j++)
		{
			if (p->score > p->Next->score)
			{
				strcpy_s(num ,10, p->num);
				strcpy_s(p->num ,10, p->Next->num);
				strcpy_s(p->Next->num ,10, num);
				strcpy_s(name,10, p->name);
				strcpy_s(p->name,10, p->Next->name);
				strcpy_s(p->Next->name,10, name);
				t = p->score;
				p->score = p->Next->score;
				p->Next->score = t;
			}
			p = p->Next;
		}
	}
	return pHead;
}

void print_list(Stu *pHead)
{
	Stu *pMove = pHead->Next;
	printf("\n\t\t\t\t\t所有学生信息：\n");
	while (pMove)
	{
		printf("\t\t\t\t\t学号:%-10s 姓名:%-10s 分数:%-10d\n", pMove->num, pMove->name, pMove->score);
		pMove = pMove->Next;
	}
	printf("\t\t\t\t\t总人数：%d\t\t\t平均分：%f", list_length(pHead), average_score(pHead));
}

void input_stu(Stu *pHead)
{
	char num[10] = " ";
	char name[10] = " ";
	int score=0;
	printf("\n\t\t\t\t\t请输入添加学生的学号：");
	scanf_s("%s", num, 10);
	printf("\t\t\t\t\t请输入添加学生的名字：");
	scanf_s("%s", name, 10);
	printf("\t\t\t\t\t请输入添加学生的分数：");
	scanf_s("%d", &score);
	insert_node(pHead, num, name, score);
}

void Save_Data(Stu *pHead)
{
	Stu *p = (Stu *)malloc(sizeof(Stu));
	p = pHead->Next;
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "Data.txt", "w");
	if (err != 0)
	{
		printf("\t\t\t\t\t打开文件失败\n");
	}
	//fprintf(fp, "学号\t姓名\t分数\r\n");
	while (p)
	{
		fprintf(fp, "%s\t%s\t%d\r\n", &p->num, &p->name, p->score);
		p = p->Next;
	}
	fclose(fp);
}

Stu *Read_Data()
{
	Stu *pHead=NULL;
	Stu *p=NULL;
	pHead = p = creat_list();
	FILE *fp= NULL;
	errno_t err;
	err = fopen_s(&fp, "Data.txt", "r");
	if (err != 0)
	{
		printf("\t\t\t\t\t打开文件失败\n");
		exit(0);
	}
	while (fscanf_s(fp, "%s\t%s\t%d\r\n", p->num, 10, p->name, 10, &(p->score))!=EOF)
	{
		insert_node(pHead, p->num, p->name, p->score);
	}
	fclose(fp);
	return pHead;
}

void clear_list(Stu *pHead)
{
	Stu *p = NULL;
	Stu *q = NULL;
	p = pHead->Next;
	while (p != NULL)
	{
		q = p->Next;
		free(p);
		p = q;
	}
	pHead->Next = NULL;
}

void meau()
{
	Stu *List = Read_Data();
	int chioce;
	interface();
	while (1)
	{
		printf("\n\t\t\t\t\t请输入操作指令：");
		scanf_s("%d", &chioce);
		switch (chioce)
		{
		case 1:
			system("cls");
			interface();
			input_stu(List);
			printf("\t\t\t\t\t添加成功！");
			getchar();
			break;
		case 2:
			system("cls");
			interface();
			List = Sequence(List);
			print_list(List);
			break;
		case 3:
			system("cls");
			interface();
			inquire_Stu(List);
			break;
		case 4:
			system("cls");
			interface();
			delete_Stu(List);
			break;
		case 5:
			system("cls");
			interface();
			modify_Stu(List);
			printf("\t\t\t\t\t修改成功！");
			break;
		case 6:
			system("cls");
			interface();
			clear_list(List);
			printf("\t\t\t\t\t清空成功！");
			break;
		case 7:exit(0);
			break;
		default:
			printf("输入有误！");
		}
		Save_Data(List);
	}
}

int main()
{
	while (1)
	{
		meau();
	}
	return 0;
}




