#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
void menu()
{
	printf("***************************************\n");
	printf("*******1. add         2. del    *******\n");
	printf("*******3. search      4. modify *******\n");
	printf("*******5. show        6. sort   *******\n");
	printf("*******7. save        0. exit   *******\n");
	printf("***************************************\n");
}
int main()
{
	int input = 0;
	//创建通讯录
	struct Contact con;//创建一个通讯录，存放1000个人和size
	//初始化通讯录
	InitContact(&con);
	do
	{
		menu();
		printf("请输入:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			Add_Contact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case EXIT:
			SaveContact(&con);
			DestroyContact(&con);
			printf("您已退出通讯录\n");
			break;
		case SAVE:
			SaveContact(&con);
			printf("保存成功\n");
			break;
		default:
			printf("输入错误，请重新输入:>\n");
			break;
		}
	} while (input);
	return 0;
}