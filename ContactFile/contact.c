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
	//����Ϣ�����е���Ϣ���ص�ͨѶ¼��
	ReadContact(ps);
}
void CheckCapacity(struct Contact* ps);
void ReadContact(struct Contact* ps)//һ��ʼ���������Ĺر��ļ�
{									//һ��Ҫ��ס
	struct PeoInfo tmp = { 0 };
	FILE* buf = fopen("Contact.dat", "rb");
	if (buf == NULL)
	{
		printf("ReadContact::%s", strerror(errno));
		return;
	}
	while (fread(&tmp, sizeof(struct PeoInfo), 1, buf))
	{		//fread���ص�����ʵ����Ԫ�صĸ���
			//�ڴ�ѭ���з���0���Ƕ����ˣ�������ѭ��
		//�������
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
			printf("���ݳɹ�\n");
		}
		else
		{
			printf("����ʧ��\n");
		}
	}
}
void Add_Contact(struct Contact* ps)
{
	//���ռ�
	//1.������ˣ���������
	//2.���û������������
	CheckCapacity(ps);
	printf("����������:>");
	scanf("%s", ps->data[ps->size].name);
	printf("����������:>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("�������Ա�:>");
	scanf("%s", ps->data[ps->size].sex);
	printf("������绰:>");
	scanf("%s", ps->data[ps->size].tele);
	printf("�������ַ:>");
	scanf("%s", ps->data[ps->size].addr);
	ps->size++;
	printf("��ӳɹ�\n");
}
void ShowContact(struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		int i = 0;
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-30s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
//�ڲ�����������static���η�ֹ����緢����ͻ
static int FindByName(const struct Contact* ps,char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < ps->size; ++i)
	{
		if (strcmp(ps->data[i].name, name) == 0)
			return i;//�ҵ������±�
	}
	return -1;//�Ҳ�������-1
}
void DelContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("������Ҫɾ����ϵ�˵�����:>");
	scanf("%s", name);
	//����Ҫɾ������
	int ret = FindByName(ps, name);
	//�ж��Ƿ��ҵ���
	if (ret==-1)//û�ҵ�
	{
		printf("��Ҫɾ������ϵ�˲�����\n");
	}
	else//�ҵ��ˣ�ɾ��
	{
		int j = 0;
		for (j = ret; j < ps->size - 1; ++j)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;//ȷ�����ʲ��������ֵ
		printf("ɾ���ɹ�\n");
	}
}
void SearchContact(const struct Contact* ps)
{
	char name[MAX_NAME];
	printf("����Ҫ������ϵ������:>");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("��Ҫ���ҵ���ϵ�˲�����\n");
	}
	else
	{
		printf("���ҳɹ� :\n");
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-30s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	printf("������Ҫ�޸���ϵ�˵�����:>");
	char name[MAX_NAME];
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("Ҫ�޸���ϵ�˵���Ϣ������\n");
	}
	else
	{
		printf("����������:>");
		scanf("%s", ps->data[pos].name);
		printf("����������:>");
		scanf("%d", &(ps->data[pos].age));
		printf("�������Ա�:>");
		scanf("%s", ps->data[pos].sex);
		printf("������绰:>");
		scanf("%s", ps->data[pos].tele);
		printf("�������ַ:>");
		scanf("%s", ps->data[pos].addr);
		printf("�޸ĳɹ�\n");
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
	printf("����ɹ�\n");
}
void DestroyContact(struct Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}
void SaveContact(struct Contact* ps)
{
	//�Զ�����д�ķ�ʽ���ļ�
	FILE* buf = fopen("Contact.dat", "wb");
	if (buf == NULL)
	{
		printf("SaveContact::%s", strerror(errno));
		return;
	}
	//д�ļ�
	for(int i=0;i<ps->size;++i)
	{
		fwrite(&(ps->data[i]), sizeof(struct PeoInfo), 1, buf);
	}
	fclose(buf);
	buf = NULL;
}