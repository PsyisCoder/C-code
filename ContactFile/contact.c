#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
void ReadContact(struct Contact* ps);
void InitContact(struct Contact* ps)
{
	ps->data = (struct PeoInfo*)malloc(DEFAULT_SIZE * sizeof(struct PeoInfo));
	if (ps->data==NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SIZE;
	//读信息把已有的信息加载到通讯录上
	ReadContact(ps);
}
void CheckCapacity(struct Contact* ps);
void ReadContact(struct Contact* ps)//一开始忘记了最后的关闭文件
{									//一定要记住
	struct PeoInfo tmp = { 0 };
	FILE* buf = fopen("Contact.dat", "rb");
	if (buf == NULL)
	{
		printf("ReadContact::%s", strerror(errno));
		return;
	}
	while (fread(&tmp, sizeof(struct PeoInfo), 1, buf))
	{		//fread返回的是真实读到元素的个数
			//在此循环中返回0就是读完了，则跳出循环
		//检查增容
		CheckCapacity(ps);
		ps->data[ps->size] = tmp;
		ps->size++;
	}
	fclose(buf);
	buf = NULL;
}
void CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		struct PeoInfo* tmp = (struct PeoInfo*)realloc(ps->data, (ps->capacity + EVERY_ADD_SZ) * sizeof(struct PeoInfo));
		if(tmp!=NULL)
		{
			ps->data = tmp;
			ps->capacity += EVERY_ADD_SZ;
			printf("增容成功\n");
		}
		else
		{
			printf("增容失败\n");
		}
	}
}
void Add_Contact(struct Contact* ps)
{
	//检查空间
	//1.如果满了，增加容量
	//2.如果没满，不做处理
	CheckCapacity(ps);
	printf("请输入姓名:>");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入年龄:>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("请输入性别:>");
	scanf("%s", ps->data[ps->size].sex);
	printf("请输入电话:>");
	scanf("%s", ps->data[ps->size].tele);
	printf("请输入地址:>");
	scanf("%s", ps->data[ps->size].addr);
	ps->size++;
	printf("添加成功\n");
}
void ShowContact(struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		int i = 0;
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-30s\n", "姓名", "年龄", "性别", "电话", "地址");
		for (i = 0; i < ps->size; ++i)
		{
			printf("%-20s\t%-4d\t%-5s\t%-12s\t%-30s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].addr);
		}
	}
}
//内部函数，加上static修饰防止与外界发生冲突
static int FindByName(const struct Contact* ps,char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < ps->size; ++i)
	{
		if (strcmp(ps->data[i].name, name) == 0)
			return i;//找到返回下标
	}
	return -1;//找不到返回-1
}
void DelContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入要删除联系人的名字:>");
	scanf("%s", name);
	//查找要删除的人
	int ret = FindByName(ps, name);
	//判断是否找到了
	if (ret==-1)//没找到
	{
		printf("您要删除的联系人不存在\n");
	}
	else//找到了，删除
	{
		int j = 0;
		for (j = ret; j < ps->size - 1; ++j)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;//确保访问不到后面的值
		printf("删除成功\n");
	}
}
void SearchContact(const struct Contact* ps)
{
	char name[MAX_NAME];
	printf("输入要查找联系人姓名:>");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("您要查找的联系人不存在\n");
	}
	else
	{
		printf("查找成功 :\n");
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-30s\n", "姓名", "年龄", "性别", "电话", "地址");
			printf("%-20s\t%-4d\t%-5s\t%-12s\t%-30s\n",
				ps->data[pos].name,
				ps->data[pos].age,
				ps->data[pos].sex,
				ps->data[pos].tele,
				ps->data[pos].addr);
	}
}
void ModifyContact(struct Contact* ps)
{
	printf("请输入要修改联系人的姓名:>");
	char name[MAX_NAME];
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("要修改联系人的信息不存在\n");
	}
	else
	{
		printf("请输入姓名:>");
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄:>");
		scanf("%d", &(ps->data[pos].age));
		printf("请输入性别:>");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话:>");
		scanf("%s", ps->data[pos].tele);
		printf("请输入地址:>");
		scanf("%s", ps->data[pos].addr);
		printf("修改成功\n");
	}
}
void SortContact(struct Contact* ps)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ps->size - 1; ++i)
	{
		for (j = 0; j < ps->size - 1 - i; ++j)
		{
			if (strcmp(ps->data[j].name, ps->data[j + 1].name) > 0)
			{
				struct PeoInfo tmp = ps->data[j];
				ps->data[j] = ps->data[j + 1];
				ps->data[j + 1] = tmp;
			}
		}
	}
	printf("排序成功\n");
}
void DestroyContact(struct Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}
void SaveContact(struct Contact* ps)
{
	//以二进制写的方式打开文件
	FILE* buf = fopen("Contact.dat", "wb");
	if (buf == NULL)
	{
		printf("SaveContact::%s", strerror(errno));
		return;
	}
	//写文件
	for(int i=0;i<ps->size;++i)
	{
		fwrite(&(ps->data[i]), sizeof(struct PeoInfo), 1, buf);
	}
	fclose(buf);
	buf = NULL;
}