// 五子棋.cpp: 定义控制台应用程序的入口点。
//开发环境：VS2017

#include "stdafx.h"
#include<graphics.h>
#include<stdio.h>
#include<windows.h>


void InitGame();
void PlayChess();
int GameOver(int a,int b);

int flag = 0;                   //判断下黑棋还是白棋的标志
int arr[20][20] = { 0 };		//0代表没棋子在上面

void InitGame()                 //游戏初始化
{
	initgraph(500, 500);        //创建窗口
	loadimage(NULL,L"背景.jpg");//贴背景图片
	setlinecolor(BLACK);        //设置棋盘线为黑色
	for (int i = 1; i < 20; i++)
	{
		line(i * 25, 10, i * 25, 490);//画竖线
		line(10, i * 25, 490, i * 25);//画横线
	}
}
void PlayChess()
{
	MOUSEMSG m;
	int a = 0, b = 0,x=0,y=0;
	while (1)
	{
		m = GetMouseMsg();//接收鼠标信息
		for (int i = 1; i < 20; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				if (abs(m.x - i * 25) < 12 && abs(m.y - j * 25) < 12)
				{
					a = i;
					b = j;
					x = i * 25;
					y = j * 25;
				}
			}
		}
		if (m.uMsg == WM_LBUTTONDOWN)   //当左键按下
		{
			if (arr[a][b] != 0)			//判断此位置是否为空，如果有棋子则退出循环，左键重新选点
			{
				continue;
			}
			if (flag % 2 == 0)			//flag取余，双数轮到黑棋下，单数白棋下
			{
				setfillcolor(BLACK);	//设置棋子颜色为黑色
				solidcircle(x, y, 10);	//画圆圈代表棋子，圆心坐标(x，y),半径10
				arr[a][b] = 1;
			}
			else
			{
				setfillcolor(WHITE);	//设置颜色白色
				solidcircle(x, y, 10);	//同上
				arr[a][b] = 2;
			}
			flag++;
		}
		if (GameOver(a, b))//符合五子连线的条件
		{
			if (flag % 2 == 1)
			{
				setbkmode(0);
				outtextxy(200, 200, L"黑棋赢了");
				Sleep(3000);
				exit(0);
			}
			else
			{
				setbkmode(0);
				outtextxy(200, 200, L"白棋赢了");
				Sleep(3000);
				exit(0);
			}
		}
	}
}

int GameOver(int a,int b)
{
	int i = 0, j = 0;
	int t = 2 - flag % 2;
	for (i = a - 4, j = b; i <= a; i++)//判断横，五子连线
		if (i >= 1 && i <= 15 && t == arr[i][j] && t == arr[i + 1][j] && t == arr[i + 2][j] && t == arr[i + 3][j] && t == arr[i + 4][j])
			return 1;
	for (j = b - 4, i = a; j <= b; j++)//判断竖
		if (j >= 1 && j <= 15 && t == arr[i][j] && t == arr[i][j + 1] && t == arr[i][j + 2] && t == arr[i][j + 3] && t == arr[i][j + 4])
			return 1;
	for (i = a - 4, j = b - 4; i <= a, j <= b; i++, j++)
		if (i >= 1 && i <= 15 && j >= 1 && j <= 15 && t == arr[i][j] && t == arr[i + 1][j + 1] && t == arr[i + 2][j + 2] && t == arr[i + 3][j + 3] && t == arr[i + 4][j + 4])
			return 1;
	for (i = a - 4, j = b + 4; i <= a, j >= 1; i++, j--)
		if (i >= 1 && i <= 15 && j >= 1 && j <= 15 && t == arr[i][j] && t == arr[i + 1][j -1] && t == arr[i + 2][j - 2] && t == arr[i + 3][j - 3] && t == arr[i + 4][j - 4])
			return 1;
	return 0;
}


int main()
{
	InitGame();
	PlayChess();
	getchar();
    return 0;
}

