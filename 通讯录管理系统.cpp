// ͨѶ¼����ϵͳ.cpp: �������̨Ӧ�ó������ڵ㡣
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
	printf("\t\t\t\t��ӭ����ͨѶ¼ϵͳ\t\t\t\t\n");
	printf("\t\t\t��ѡ��˵���1��������ϵ�� 2���鿴��ϵ�� 3��������ϵ��4���˳�ϵͳ\n");
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
		printf("���ļ�����\n");
		return;
	}
	for (i = 0; i<j; i++)
	{
		fwrite(&per[i], sizeof(struct person), 1, fp);
	}
	fclose(fp);
	if (fopen_s(&fq,"ͨѶ¼.txt", "w") != NULL)
	{
		printf("���ļ�����\n");
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
	printf("��������ϵ�˵�������\n");
	scanf_s("%d", &n);
	for (i = 0; i<n; i++)
	{
		printf("�������%d����ϵ�˵���Ϣ\n", i + 1);
		printf("����:\n");
		scanf_s("%s", per[i].name,10);
		printf("��ϵ�绰:\n");
		scanf_s("%s", per[i].phone,20);
		printf("��ַ:\n");
		scanf_s("%s", per[i].address,20);
	}
	j = i;
	save();
	printf("��Ϣ�����벢����\n");
	back();
}
void load()
{
	int i;
	if (fopen_s(&fp,"15.txt", "r") != NULL)
		printf("���ļ�����\n");
	for (i = 0; !feof(fp); i++)
		fread(&per[i], sizeof(struct person), 1, fp);
	fclose(fp);
	j = i - 1;
}
void show()
{
	int i;
	printf("���\t����\t\t��ϵ�绰\t��ַ\n");
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
	printf("\t\t\t\t\t������Ҫ��ʲô?\n");
	printf("\t\t\t\t\t1���������˵� 2���˳�ϵͳ\n");
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
			printf("�������������룺\n");
			scanf_s("%d", &n);
		}
	}
}
void fine()
{
	int n;
	printf("����ͨ��ʲô��ʽ���ң�\n");
	printf("1������ 2���绰\n");
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
		printf("�������������룺\n");
		scanf_s("%d", &n);
	}
}
void name_fine()
{
	int i;
	char a[20];
	printf("��������Ҫ������ϵ�˵�����:\n");
	scanf_s("%s", a,20);
	load();
	for (i = 0; i<j; i++)
	{
		if (strcmp(per[i].name, a) == 0)
		{
			printf("��Ҫ���ҵ���ϵ�˵���Ϣ��:\n");
			printf("\n����\t\t�绰\t��ַ\n");
			printf("%-8s%-15s%-15s", per[i].name, per[i].phone, per[i].address); break;
		}
	}
	if (i == j)printf("�Ҳ�������ϵ��\n");
}
void phone_fine()
{
	int i;
	char a[20];
	printf("��������Ҫ������ϵ�˵ĵ绰:\n");
	scanf_s("%s", a, 20);
	load();
	for (i = 0; i<j; i++)
	{
		if (strcmp(per[i].phone, a) == 0)
		{
			printf("��Ҫ���ҵ���ϵ�˵���Ϣ��:\n");
			printf("\n����\t\t�绰\t��ַ\n");
			printf("%-8s%-15s%-15s", per[i].name, per[i].phone, per[i].address); break;
		}
	}
	if (i == j)printf("�Ҳ�������ϵ��\n");
}

int main()
{
	while (1)
	{
		mean();
	}
	return 0;
}

