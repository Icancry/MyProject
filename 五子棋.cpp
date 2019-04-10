// ������.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<graphics.h>
#include<stdio.h>
#include<windows.h>


void InitGame();
void PlayChess();
int GameOver(int a,int b);

int flag = 0;                   //�ж��º��廹�ǰ���ı�־
int arr[20][20] = { 0 };		//0����û����������

void InitGame()                 //��Ϸ��ʼ��
{
	initgraph(500, 500);        //��������
	loadimage(NULL,L"����.jpg");//������ͼƬ
	setlinecolor(BLACK);        //����������Ϊ��ɫ
	for (int i = 1; i < 20; i++)
	{
		line(i * 25, 10, i * 25, 490);//������
		line(10, i * 25, 490, i * 25);//������
	}
}
void PlayChess()
{
	MOUSEMSG m;
	int a = 0, b = 0,x=0,y=0;
	while (1)
	{
		m = GetMouseMsg();//���������Ϣ
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
		if (m.uMsg == WM_LBUTTONDOWN)   //���������
		{
			if (arr[a][b] != 0)			//�жϴ�λ���Ƿ�Ϊ�գ�������������˳�ѭ�����������ѡ��
			{
				continue;
			}
			if (flag % 2 == 0)			//flagȡ�࣬˫���ֵ������£�����������
			{
				setfillcolor(BLACK);	//����������ɫΪ��ɫ
				solidcircle(x, y, 10);	//��ԲȦ�������ӣ�Բ������(x��y),�뾶10
				arr[a][b] = 1;
			}
			else
			{
				setfillcolor(WHITE);	//������ɫ��ɫ
				solidcircle(x, y, 10);	//ͬ��
				arr[a][b] = 2;
			}
			flag++;
		}
		if (GameOver(a, b))//�����������ߵ�����
		{
			if (flag % 2 == 1)
			{
				setbkmode(0);
				outtextxy(200, 200, L"����Ӯ��");
				Sleep(3000);
				exit(0);
			}
			else
			{
				setbkmode(0);
				outtextxy(200, 200, L"����Ӯ��");
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
	for (i = a - 4, j = b; i <= a; i++)//�жϺᣬ��������
		if (i >= 1 && i <= 15 && t == arr[i][j] && t == arr[i + 1][j] && t == arr[i + 2][j] && t == arr[i + 3][j] && t == arr[i + 4][j])
			return 1;
	for (j = b - 4, i = a; j <= b; j++)//�ж���
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

