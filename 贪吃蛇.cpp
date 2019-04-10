// 贪吃蛇.cpp: 定义控制台应用程序的入口点。
//开发环境：vs2017

#include "stdafx.h"
#include<stdio.h>
#include<time.h>
#include"conio.h"
#include"graphics.h"

void InitGame();		//游戏初始化
void SnakeMove();	    //蛇的移动
void SnakePrint();      //画蛇
void ChangeSnakeCh();   //改变蛇的方向
void EatFood();         //吃掉食物
void FoodCoor();        //生成食物位置
void FoodPrint();       //画食物
void GameOver();        //游戏结束

#define MAX 1000        //蛇的最大节数
#define Size 20         //蛇一节的尺寸
struct COOR  
{
	int x;
	int y;
};
enum CH    
{
	up = 72,
	down = 80,
	left = 75,
	right = 77
};
struct Snake
{
	int n;        //蛇的节数
	COOR src[MAX];//蛇的坐标
	CH ch;      //蛇的方向
}snake;
struct FOOD
{
	COOR frc;//食物的坐标
	int flag;//生成食物的标志
}food;

void InitGame()//游戏初始化
{
	initgraph(500, 500); //窗口尺寸
	snake.n = 1;         //蛇的节数初始为1
	snake.src[0].x = 0;  //蛇的位置横坐标x初始为0
	snake.src[0].y = 0;  //蛇的位置纵坐标y初始为0
	snake.ch = right;    //蛇的初始方向向右
	food.flag = 0;       //0表示需要生成食物
}

void SnakePrint()//画蛇
{
	setfillcolor(BLUE);
	solidcircle(snake.src[0].x + Size/2, snake.src[0].y + Size/2 , 10);
	//fillrectangle(snake.src[0].x, snake.src[0].y, snake.src[0].x + Size, snake.src[0].y + Size);//一个正方形代表蛇头
	setfillcolor(GREEN);

	for (int i = snake.n - 1; i > 0; i--)
		fillrectangle(snake.src[i].x, snake.src[i].y, snake.src[i].x + Size, snake.src[i].y+Size);//蛇身
}

void SnakeMove()//蛇的移动
{
	for (int i = snake.n-1; i > 0; i--)
	{
		snake.src[i].x = snake.src[i - 1].x;
		snake.src[i].y = snake.src[i - 1].y;
	}
	switch (snake.ch)
	{
	case up:
		snake.src[0].y -= Size;
		break;
	case down:
		snake.src[0].y += Size;
		break;
	case left:
		snake.src[0].x -= Size;
		break;
	case right:
		snake.src[0].x += Size;
		break;
	default:
		break;
	}
}

void ChangeSnakeCh()//控蛇的方向
{
	switch (_getch())
	{
	case 72:
		if (snake.ch != down)
			snake.ch = up;
		break;
	case 80:
		if (snake.ch != up)
			snake.ch = down;
		break;
	case 75:
		if (snake.ch != right)
			snake.ch = left;
		break;
	case 77:
		if (snake.ch != left)
			snake.ch = right;
	default:
		break;
	}
}

void FoodCoor()//生成食物坐标
{
	srand((unsigned)time(NULL));    //产生随机种子
	food.frc.x = rand() % 25 * Size;//食物x坐标
	food.frc.y = rand() % 25 * Size;//食物y坐标
	food.flag = 1;                  //已有食物了
}

void FoodPrint()//画食物
{
	setfillcolor(RED);
	solidroundrect(food.frc.x, food.frc.y, food.frc.x + Size, food.frc.y + Size,30,30);
}

void EatFood()//吃食物
{
	if (snake.src[0].x == food.frc.x && snake.src[0].y == food.frc.y)//蛇坐标和食物坐标重合
	{
		snake.n++;                                                   //蛇节数+1
		food.flag = 0;                                               //需要生成食物了
	}
}

void GameOver()
{
	if (snake.src[0].x < 0 || snake.src[0].x>480|| snake.src[0].y < 0 || snake.src[0].y>480)//蛇撞到左右墙
	{
		cleardevice();
		outtextxy(200, 200, L"Game Over");
		Sleep(3000);
		exit(0);
	}
	for(int i=snake.n-1;i>0;i--)
		if (snake.src[0].x == snake.src[i].x && snake.src[0].y == snake.src[i].y)
		{
			cleardevice();
			outtextxy(200, 200, L"Game Over");
			Sleep(3000);
			exit(0);
		}

}

int main()
{
	InitGame();
	while (1)
	{
		while (!_kbhit())
		{
			if (food.flag == 0)
				FoodCoor();
			cleardevice();
			SnakeMove();
			SnakePrint();
			FoodPrint();
			Sleep(150);
			EatFood();
			GameOver();
		}
		ChangeSnakeCh();
	}
    return 0;
}

