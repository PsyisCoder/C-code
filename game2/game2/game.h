#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#define ROW 10
#define COL 10
#define NUM 10
#define ROWS ROW+2
#define COLS ROW+2
#define SIZE 30
void begin(int board[ROWS][COLS], int rows, int cols,int set);//��ʼ��
void gamedraw(int board[ROWS][COLS], int row, int col);//��ӡ
void setboom(int board[ROWS][COLS], int row, int col, int boom);//����
void otherdigit(int board[ROWS][COLS], int row, int col);//�ҵ���Ϊ�׵������ط���Ӧ������
void My_loadimage();
int PlayGame(int board[][12],int* cot);
void Openzero(int r,int c,int board[][12],int* cot);