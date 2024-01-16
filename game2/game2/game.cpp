#define _CRT_SECURE_NO_WARNINGS
#include"game.h"
IMAGE img[12];  //img���12��ͼƬ
void begin(int board[ROWS][COLS], int rows, int cols,int set)//��ʼ��
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; ++i)
	{
		for (j = 0; j < cols; ++j)
		{
			board[i][j] = set;
		}
	}
}
void gamedraw(int board[ROWS][COLS], int row, int col)//��ӡ
{
	int i = 0;
	int j = 0;
	for (i = 1; i <= ROW; ++i)
	{
		for (j = 1; j <= COL; ++j)
		{
			printf("%2d ", board[i][j]);
			if (board[i][j] == -1)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[9]);
			}
			else if (board[i][j] >= 0 && board[i][j] <= 8)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[board[i][j]]);
			}
			else if (board[i][j] >= 19 && board[i][j] <= 28)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[10]);
			}
			else if (board[i][j] >= 30)
			{
				putimage((i - 1) * SIZE, (j - 1) * SIZE, &img[11]);
			}
		}
		printf("\n");
	}
}
void setboom(int board[ROWS][COLS], int row, int col, int boom)
{
	//������������
	srand((unsigned int)time(NULL));
	int n=NUM;
	//���ײ�������������
	while (n)
	{
		int r = rand() % ROW+1;//���巶Χ����Ų1��1-ROW
		int c = rand() % COL+1;//���巶Χ����Ų1��1-COL
		if (board[r][c] == 0)
		{
			board[r][c] = -1;//���׶�Ϊ-1
			n--;
		}
	}
}
void otherdigit(int board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	int m = 0;
	int n = 0;
	for (i = 1; i <= row; ++i)
	{
		for (j = 1; j <= col; ++j)
		{
			if (board[i][j] != -1)
			{
				for (m = i - 1; m <= i + 1; ++m)
				{
					for (n = j - 1; n <= j + 1; ++n)
					{
						if (board[m][n] == -1)
							board[i][j]++;
					}
				}
			}
		}
	}
	for (i = 1; i <= row; ++i)
	{
		for (j = 1; j <= col; ++j)
		{
			board[i][j] += 20;
		}
	}
}
void My_loadimage()
{
	loadimage(&img[0], L"0.png", SIZE, SIZE);
	loadimage(&img[1], L"1.png", SIZE, SIZE);
	loadimage(&img[2], L"2.png", SIZE, SIZE);
	loadimage(&img[3], L"3.png", SIZE, SIZE);
	loadimage(&img[4], L"4.png", SIZE, SIZE);
	loadimage(&img[5], L"5.png", SIZE, SIZE);
	loadimage(&img[6], L"6.png", SIZE, SIZE);
	loadimage(&img[7], L"7.png", SIZE, SIZE);
	loadimage(&img[8], L"8.png", SIZE, SIZE);
	loadimage(&img[9], L"9.png", SIZE, SIZE);
	loadimage(&img[10], L"10.png", SIZE, SIZE);
	loadimage(&img[11], L"11.png", SIZE, SIZE);
}
int  PlayGame(int board[][12],int* cot)
{
	MOUSEMSG msg = { 0 };  //����һ�������Ϣ
	int r, c;
	while(1)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN://����һ������
			r = msg.x / 30 + 1;
			c = msg.y / 30 + 1;
			if (board[r][c] >= 19 && board[r][c] <= 28)
			{
				if (board[r][c] == 20)//����㿪��0
				{
					Openzero(r,c,board,cot);
				}
				else
				{
					board[r][c] -= 20;
					(*cot)++;
				}
			}
			return board[r][c];
			break;
		case WM_RBUTTONDOWN://���һ�����棬ȡ�����һ������
			r = msg.x / 30 + 1;
			c = msg.y / 30 + 1;
			if (board[r][c] >= 19 && board[r][c] <= 28)
			{
				board[r][c] += 50;
			}
			else if(board[r][c]>30)
			{
				board[r][c] -= 50;
			}
			return board[r][c];
			break;
		}
	}
}
void Openzero(int r,int c,int board[][12],int* cot)
{
	board[r][c] -= 20;
	(*cot)++;
	for (int m = r - 1; m < r + 1; ++m)
	{
		for (int n = c - 1; n < c + 1; ++n)//�����Ź���
		{
			if(m>=1&&m<=ROW&&n>=1&&n<=COL)//��������Ϸ����
			{
				if (board[m][n] >= 19 && board[m][n] <= 28)//�հ�
				{
					if (board[m][n] != 20)
					{
						board[m][n] -= 20;
						(*cot)++;
					}
					else
					{
						Openzero(m, n, board, cot);
					}
				}
			}
		}
	}
}