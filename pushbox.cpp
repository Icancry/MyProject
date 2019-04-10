// pushbox.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include <windows.h>
int map[9][11] = { { 0,1,1,1,1,1,1,1,1,1,0 } ,
                   { 0,1,0,0,0,1,0,0,0,1,0 } ,
                   { 0,1,0,0,0,0,0,4,0,1,0 } ,
                   { 0,1,0,4,0,4,0,4,0,1,1 } ,
                   { 0,1,0,0,0,0,0,0,0,0,1 } ,
                   { 1,1,5,1,1,1,1,0,0,0,1 } ,
                   { 1,0,0,0,0,0,0,1,0,0,1 } ,
                   { 1,0,0,3,3,3,3,0,0,1,1 } ,
                   { 1,1,1,1,1,1,1,1,1,1,0 }
                 };
void Map()
{
	int i, j;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 11; j++)
		{
			switch (map[i][j])
			{
			case 0:printf("  "); break;//0����յ�
			case 1:printf("��"); break;//1����ǽ
			case 3:printf("��"); break;//3����Ŀ�ĵ�
			case 4:printf("��"); break;//4��������
			case 5:printf("��"); break;//5������
			case 7:printf("��"); break;//����4+Ŀ�ĵ�3=7
			case 8:printf("��"); break;//��5+Ŀ�ĵ�3=8
			}
		}
		printf("\n");
	}
}
void PlayGame()
{
	int r, c;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (map[i][j] == 5||map[i][j]==8)
			{
				r = i;
				c = j;
			}

		}
	}
	char ch;
	ch = _getch();//���ռ���ֵ W A S D ������
	switch (ch)
	{
	case 'W':
	case 'w':
		if (map[r - 1][c] == 0)//��ǰ���ǿյ� �˵����� r-1,c
		{
			map[r - 1][c] = 5;//������ȥ �����5
			if (map[r][c] == 5)//�ж���ԭ����λ����(5+0)����(5+3)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r - 1][c] == 3)//�˵�ǰ����Ŀ�ĵ�
		{
			map[r - 1][c] = 8;//����Ŀ�ĵ��ϣ�5+3��
			if (map[r][c] == 5)//�ж���ԭ����λ����(5+0)����(5+3)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)//�˵�ǰ��������
		{
			if (map[r - 2][c] == 0 || map[r - 2][c] == 3)//���ӵ�ǰ���ǿյػ���Ŀ�ĵ�
			{
				map[r - 2][c] += 4;//����4����ȥ��λ��+4
				map[r - 1][c] += 1;//������ȥ+5�������ƿ�-4��������+1
				map[r][c] -= 5;//���߿���ԭ����λ�þ�-5
			}
		}
		break;
	case 'S':
	case 's':
		if (map[r + 1][c] == 0)
		{
			map[r + 1][c] = 5;
			if (map[r][c] == 5)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r + 1][c] == 3)
		{
			map[r + 1][c] = 8;
			if (map[r][c] == 5)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r + 1][c] == 4 || map[r + 1][c] == 7)
		{
			if (map[r + 2][c] == 0 || map[r + 2][c] == 3)//
			{
				map[r + 2][c] += 4;
				map[r + 1][c] += 1;
				map[r][c] -= 5;
			}
		}
		break;
	case 'A':
	case 'a':
		if (map[r][c - 1] == 0)
		{
			map[r][c - 1] = 5;
			if (map[r][c] == 5)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r][c - 1] == 3)
		{
			map[r][c - 1] = 8;
			if (map[r][c] == 5)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)
		{
			if (map[r][c - 2] == 0 || map[r][c - 2] == 3)
			{
				map[r][c - 2] += 4;
				map[r][c - 1] += 1;
				map[r][c] -= 5;
			}
		}
		break;
	case 'D':
	case 'd':
		if (map[r][c + 1] == 0)
		{
			map[r][c + 1] = 5;
			if (map[r][c] == 5)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r][c + 1] == 3)
		{
			map[r][c + 1] = 8;
			if (map[r][c] == 5)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r][c + 1] == 4 || map[r][c + 1] == 7)
		{
			if (map[r][c + 2] == 0 || map[r][c + 2] == 3)
			{
				map[r][c + 2] += 4;
				map[r][c + 1] += 1;
				map[r][c] -= 5;
			}
		}
		break;
	}
}
void GameOver()
{
	int flag=0;
	for(int i=0;i<9;i++)
		for (int j = 0; j < 11; j++)
		{
			if (map[i][j] == 7)
			{
				flag++;
			}
			if (flag == 4)
			{
				printf("YOU WIN������\n");
				Sleep(3000);
				exit(0);
			}
		}
}

int main()
{
	while (1)
	{
		system("cls");
		Map();
		PlayGame();
		GameOver();
	}

	return 0;
}

