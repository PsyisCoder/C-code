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
void begin(int board[ROWS][COLS], int rows, int cols,int set);//初始化
void gamedraw(int board[ROWS][COLS], int row, int col);//打印
void setboom(int board[ROWS][COLS], int row, int col, int boom);//埋雷
void otherdigit(int board[ROWS][COLS], int row, int col);//找到不为雷的其它地方对应的数字
void My_loadimage();
int PlayGame(int board[][12],int* cot);
void Openzero(int r,int c,int board[][12],int* cot);