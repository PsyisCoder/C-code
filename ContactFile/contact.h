#define _CRT_SECURE_NO_WARNINGS 1
#define DEFAULT_SIZE 3
#define EVERY_ADD_SZ 2
#define MAX_NAME 20
#define MAX_SEX 5
#define MAX_TELE 12
#define MAX_ADDR 30
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum Option
{
	EXIT,	//0
	ADD,	//1
	DEL,	//2
	SEARCH,	//3
	MODIFY,	//4
	SHOW,	//5
	SORT,	//6
	SAVE
};
struct PeoInfo//个人信息
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};
struct Contact//创建通讯录，并包含了大小size
{
	struct PeoInfo* data;
	int size;
	int capacity;
};
//初始化通讯录
void InitContact(struct Contact* ps);

//添加联系人信息
void Add_Contact(struct Contact* ps);

//显示联系人信息
void ShowContact(const struct Contact* ps);

//删除联系人信息
void DelContact(struct Contact* ps);

//查找联系人信息
void SearchContact(const struct Contact* ps);

//修改联系人信息
void ModifyContact(struct Contact* ps);

//按名字排序
void SortContact(struct Contact* ps);

//保存
void SaveContact(struct Contact* ps);