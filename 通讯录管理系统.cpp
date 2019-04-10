// 通讯录管理系统.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>

#include<stdio.h>
#include<string.h>
void Input();
void mean();
void save();
void back();
void load();
void show();
void fine();
void name_fine();
void phone_fine();
int j;
FILE *fp;
void mean()
{
	int chioce;
	printf("\t\t\t\t欢迎来到通讯录系统\t\t\t\t\n");
	printf("\t\t\t请选择菜单：1、输入联系人 2、查看联系人 3、查找联系人4、退出系统\n");
	scanf_s("%d", &chioce);
	switch (chioce)
	{
	case 1:; system("cls"); Input(); break;
	case 4:exit(0);  break;
	case 2:show(); break;
	case 3:system("cls"); fine();
	}
}

struct person
{
	char phone[20];
	char name[10];
	char address[20];
};
struct person per[50];
void save()
{
	int i;
	FILE *fq;
	if (fopen_s(&fp,"15.txt", "w")!= NULL)
	{
		printf("打开文件出错\n");
		return;
	}
	for (i = 0; i<j; i++)
	{
		fwrite(&per[i], sizeof(struct person), 1, fp);
	}
	fclose(fp);
	if (fopen_s(&fq,"通讯录.txt", "w") != NULL)
	{
		printf("打开文件出错\n");
		return;
	}
	for (i = 0; i<j; i++)
	{
		fprintf(fq, "%d\t%-16s%-16s%-16s\n", i + 1, per[i].name, per[i].phone, per[i].address);
	}
	fclose(fq);
}
void Input()
{
	int n, i;
	printf("请输入联系人的人数：\n");
	scanf_s("%d", &n);
	for (i = 0; i<n; i++)
	{
		printf("请输入第%d个联系人的信息\n", i + 1);
		printf("姓名:\n");
		scanf_s("%s", per[i].name,10);
		printf("联系电话:\n");
		scanf_s("%s", per[i].phone,20);
		printf("地址:\n");
		scanf_s("%s", per[i].address,20);
	}
	j = i;
	save();
	printf("信息已输入并保存\n");
	back();
}
void load()
{
	int i;
	if (fopen_s(&fp,"15.txt", "r") != NULL)
		printf("打开文件错误\n");
	for (i = 0; !feof(fp); i++)
		fread(&per[i], sizeof(struct person), 1, fp);
	fclose(fp);
	j = i - 1;
}
void show()
{
	int i;
	printf("序号\t姓名\t\t联系电话\t地址\n");
	load();
	for (i = 0; i<j; i++)
	{
		printf("%d\t%-16s%-16s%-16s\n", i + 1, per[i].name, per[i].phone, per[i].address);
	}
}
void back()
{
	int n;
	printf("\n\n");
	printf("\t\t\t\t\t你现在要做什么?\n");
	printf("\t\t\t\t\t1、返回主菜单 2、退出系统\n");
	scanf_s("%d", &n);
	while (1)
	{
		if (n == 1)
		{
			system("cls");
			mean();
		}
		if (n == 2)
		{
			exit(0);
		}
		if (n != 1 && n != 2)
		{
			printf("错误！请重新输入：\n");
			scanf_s("%d", &n);
		}
	}
}
void fine()
{
	int n;
	printf("你想通过什么方式查找？\n");
	printf("1、姓名 2、电话\n");
	scanf_s("%d", &n);
	if (n == 1)
	{
		name_fine(); back();
	}
	if (n == 2)
	{
		phone_fine(); back;
	}
	if (n != 1 && n != 1)
	{
		printf("错误！请重新输入：\n");
		scanf_s("%d", &n);
	}
}
void name_fine()
{
	int i;
	char a[20];
	printf("请输入你要查找联系人的姓名:\n");
	scanf_s("%s", a,20);
	load();
	for (i = 0; i<j; i++)
	{
		if (strcmp(per[i].name, a) == 0)
		{
			printf("你要查找的联系人的信息是:\n");
			printf("\n姓名\t\t电话\t地址\n");
			printf("%-8s%-15s%-15s", per[i].name, per[i].phone, per[i].address); break;
		}
	}
	if (i == j)printf("找不到该联系人\n");
}
void phone_fine()
{
	int i;
	char a[20];
	printf("请输入你要查找联系人的电话:\n");
	scanf_s("%s", a, 20);
	load();
	for (i = 0; i<j; i++)
	{
		if (strcmp(per[i].phone, a) == 0)
		{
			printf("你要查找的联系人的信息是:\n");
			printf("\n姓名\t\t电话\t地址\n");
			printf("%-8s%-15s%-15s", per[i].name, per[i].phone, per[i].address); break;
		}
	}
	if (i == j)printf("找不到该联系人\n");
}

int main()
{
	while (1)
	{
		mean();
	}
	return 0;
}

