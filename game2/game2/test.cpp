#define _CRT_SECURE_NO_WARNINGS
#include"game.h"
void menu()
{
	printf("****************************\n");
	printf("*********1.   play**********\n");
	printf("*********0.   exit**********\n");
	printf("****************************\n");
}
void game()
{
	int  count = 0;//�㿪�ĸ���
	int* cot = &count;
	//����һ������
	HWND hwnd = initgraph(ROW * SIZE, COL * SIZE, SHOWCONSOLE);
	//����ͼƬ
	My_loadimage();
	//��������
	int board[ROWS][COLS] = { 0 };
	//��ʼ������
	begin(board, ROWS, COLS, 0);
	//����
	setboom(board, ROW, COL, NUM);
	//�ҵ���Ϊ�׵������ط���Ӧ������
	otherdigit(board, ROW, COL);//������������м���
	while(1)
	{
		//��ӡ����
		gamedraw(board, ROW, COL);
		//������
		if (PlayGame(board,cot) == -1)
		{
			gamedraw(board, ROW, COL);
			MessageBox(hwnd, L"�����ˣ��󱿵�!!", L"", MB_OK);
			break;
		}
		if (ROW * COL - NUM == count)
		{
			gamedraw(board, ROW, COL);
			MessageBox(hwnd, L"��Ӯ�ˣ������!!", L"", MB_OK);
			break;
		}
	}
	closegraph();
}
void test()
{
	int input = 0;
	menu();
	do
	{
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);
}
int main()
{
	test();
	return 0;
}