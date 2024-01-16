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
	int  count = 0;//点开的个数
	int* cot = &count;
	//给定一个窗口
	HWND hwnd = initgraph(ROW * SIZE, COL * SIZE, SHOWCONSOLE);
	//加载图片
	My_loadimage();
	//定义数组
	int board[ROWS][COLS] = { 0 };
	//初始化函数
	begin(board, ROWS, COLS, 0);
	//埋雷
	setboom(board, ROW, COL, NUM);
	//找到不为雷的其它地方对应的数字
	otherdigit(board, ROW, COL);//并且在里面进行加密
	while(1)
	{
		//打印数组
		gamedraw(board, ROW, COL);
		//鼠标操作
		if (PlayGame(board,cot) == -1)
		{
			gamedraw(board, ROW, COL);
			MessageBox(hwnd, L"你输了，大笨蛋!!", L"", MB_OK);
			break;
		}
		if (ROW * COL - NUM == count)
		{
			gamedraw(board, ROW, COL);
			MessageBox(hwnd, L"你赢了，大聪明!!", L"", MB_OK);
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
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误，请重新选择\n");
			break;
		}
	} while (input);
}
int main()
{
	test();
	return 0;
}