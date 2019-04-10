// ̰����.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<stdio.h>
#include<time.h>
#include"conio.h"
#include"graphics.h"

void InitGame();		//��Ϸ��ʼ��
void SnakeMove();	    //�ߵ��ƶ�
void SnakePrint();      //����
void ChangeSnakeCh();   //�ı��ߵķ���
void EatFood();         //�Ե�ʳ��
void FoodCoor();        //����ʳ��λ��
void FoodPrint();       //��ʳ��
void GameOver();        //��Ϸ����

#define MAX 1000        //�ߵ�������
#define Size 20         //��һ�ڵĳߴ�
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
	int n;        //�ߵĽ���
	COOR src[MAX];//�ߵ�����
	CH ch;      //�ߵķ���
}snake;
struct FOOD
{
	COOR frc;//ʳ�������
	int flag;//����ʳ��ı�־
}food;

void InitGame()//��Ϸ��ʼ��
{
	initgraph(500, 500); //���ڳߴ�
	snake.n = 1;         //�ߵĽ�����ʼΪ1
	snake.src[0].x = 0;  //�ߵ�λ�ú�����x��ʼΪ0
	snake.src[0].y = 0;  //�ߵ�λ��������y��ʼΪ0
	snake.ch = right;    //�ߵĳ�ʼ��������
	food.flag = 0;       //0��ʾ��Ҫ����ʳ��
}

void SnakePrint()//����
{
	setfillcolor(BLUE);
	solidcircle(snake.src[0].x + Size/2, snake.src[0].y + Size/2 , 10);
	//fillrectangle(snake.src[0].x, snake.src[0].y, snake.src[0].x + Size, snake.src[0].y + Size);//һ�������δ�����ͷ
	setfillcolor(GREEN);

	for (int i = snake.n - 1; i > 0; i--)
		fillrectangle(snake.src[i].x, snake.src[i].y, snake.src[i].x + Size, snake.src[i].y+Size);//����
}

void SnakeMove()//�ߵ��ƶ�
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

void ChangeSnakeCh()//���ߵķ���
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

void FoodCoor()//����ʳ������
{
	srand((unsigned)time(NULL));    //�����������
	food.frc.x = rand() % 25 * Size;//ʳ��x����
	food.frc.y = rand() % 25 * Size;//ʳ��y����
	food.flag = 1;                  //����ʳ����
}

void FoodPrint()//��ʳ��
{
	setfillcolor(RED);
	solidroundrect(food.frc.x, food.frc.y, food.frc.x + Size, food.frc.y + Size,30,30);
}

void EatFood()//��ʳ��
{
	if (snake.src[0].x == food.frc.x && snake.src[0].y == food.frc.y)//�������ʳ�������غ�
	{
		snake.n++;                                                   //�߽���+1
		food.flag = 0;                                               //��Ҫ����ʳ����
	}
}

void GameOver()
{
	if (snake.src[0].x < 0 || snake.src[0].x>480|| snake.src[0].y < 0 || snake.src[0].y>480)//��ײ������ǽ
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

