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
struct PeoInfo//������Ϣ
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};
struct Contact//����ͨѶ¼���������˴�Сsize
{
	struct PeoInfo* data;
	int size;
	int capacity;
};
//��ʼ��ͨѶ¼
void InitContact(struct Contact* ps);

//�����ϵ����Ϣ
void Add_Contact(struct Contact* ps);

//��ʾ��ϵ����Ϣ
void ShowContact(const struct Contact* ps);

//ɾ����ϵ����Ϣ
void DelContact(struct Contact* ps);

//������ϵ����Ϣ
void SearchContact(const struct Contact* ps);

//�޸���ϵ����Ϣ
void ModifyContact(struct Contact* ps);

//����������
void SortContact(struct Contact* ps);

//����
void SaveContact(struct Contact* ps);