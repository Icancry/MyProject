// pushbox.cpp: 定义控制台应用程序的入口点。
//开发环境：VS2017

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
			case 0:printf("  "); break;//0代表空地
			case 1:printf("■"); break;//1代表墙
			case 3:printf("○"); break;//3代表目的地
			case 4:printf("▲"); break;//4代表箱子
			case 5:printf("♀"); break;//5代表人
			case 7:printf("●"); break;//箱子4+目的地3=7
			case 8:printf("♀"); break;//人5+目的地3=8
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
	ch = _getch();//接收键盘值 W A S D 代表方向
	switch (ch)
	{
	case 'W':
	case 'w':
		if (map[r - 1][c] == 0)//人前面是空地 人的坐标 r-1,c
		{
			map[r - 1][c] = 5;//人走上去 变成人5
			if (map[r][c] == 5)//判断人原来的位置是(5+0)还是(5+3)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r - 1][c] == 3)//人的前面是目的地
		{
			map[r - 1][c] = 8;//人在目的地上（5+3）
			if (map[r][c] == 5)//判断人原来的位置是(5+0)还是(5+3)
				map[r][c] = 0;
			else
				map[r][c] = 3;
		}
		else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)//人的前面是箱子
		{
			if (map[r - 2][c] == 0 || map[r - 2][c] == 3)//箱子的前面是空地或者目的地
			{
				map[r - 2][c] += 4;//箱子4移上去的位置+4
				map[r - 1][c] += 1;//人走上去+5，箱子移开-4，合起来+1
				map[r][c] -= 5;//人走开，原来的位置就-5
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
				printf("YOU WIN！！！\n");
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

