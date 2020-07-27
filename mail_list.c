#include <stdio.h>
#include<getch.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

static int count=0;//当前有效联系人数量
static char name[100][20];
static char sex[100];
static char tel[100][12];

void anykey_continue(void)
{
	stdin->_IO_read_ptr=stdin->_IO_read_end;
	printf("任意键继续...");
	getch();
}

void show_msg(const char* msg,float sec)
{
	printf("%s",msg);
	fflush(stdout);
	usleep(sec*1000000);
}

void add(void)
{
	if(count>=100)
	{
		printf("系统正在升级，请等待……\n");
		return ;
	}

	int i=0;
	while(sex[i]) i++;
	printf("请输入姓名 性别 电话：");
	scanf("%s %c %s",name[i],sex+i,tel[i]);
	count++;
	show_msg("添加联系人成功!\n",0.5);
}

void del(void)
{
	char i=0;
	char key[20]={};
	
	printf("请输入要删除的姓名或电话：");
	scanf("%s",key);
	
	do{
		if(sex[i])
		{
			if(isdigit(key[0]))
			{
				if(0 == strcmp(tel[i],key)) break;
			}
			else
			{
				if(0 == strcmp(name[i],key)) break;
			}
		}
	}while(++i<100);
	if(i<100)
	{
		printf("删除 %s %s %s 联系人成功！\n",name[i],'w'==sex[i]?"女":"男",tel[i]);
		sex[i]=0;
		count--;
	}
	else
	{
		printf("没有找到联系人，检查查询条件：%s\n",key);
	}
	show_msg("",1.5);
}

void modify(void)
{
	char key[20]={};
	printf("请输入要修改的联系人姓名：");
	scanf("%s",key);
	for(int i=0;i<100;i++)
	{
		if(sex[i] && 0 == strcmp(name[i],key))
		{
			printf("请重新输入联系人姓名 性别 电话：");
			scanf("%s %c %s",name[i],sex+i,tel[i]);
			show_msg("修改联系人成功！\n",1.5);
			return ;
		}
	}

	show_msg("未找到该联系人！\n",1.5);
}

void find(void)
{
	char key[20]={};
	printf("请输入要查询的关键字：");
	scanf("%s",key);

	for(int i=0;i<100;i++)
	{
		if(sex[i] && (strstr(name[i],key) || strstr(tel[i],key)))
		{
			printf("%s %s %s\n",name[i],'w'==sex[i]?"女":"男",tel[i]);
		}
	}
	anykey_continue();
}

void list(void)
{
	for(int i=0;i<100;i++)
	{
		if(sex[i])
		{
			printf("%s %s %s\n",name[i],'w'==sex[i]?"女":"男",tel[i]);
		}
	}
	anykey_continue();
}



char menu(void)
{
	for(;;)
	{
		system("clear");
		printf("欢迎使用通讯录！\n");
		printf("*********************\n");
		printf("1、添加联系人       *\n");
		printf("2、删除联系人       *\n");
		printf("3、修改联系人信息   *\n");
		printf("4、查找联系人       *\n");
		printf("5、显示所有联系人   *\n");
		printf("6、退出             *\n");
		printf("*********************\n");
		printf("请输入指令：\n");
		char cmd=getch();
		printf("%c\n",cmd);
		return cmd;
	}
}
int main()
{
	for(;;)
	{
		switch(menu())
		{
			case '1':add();break;
			case '2':del();break;
			case '3':modify();break;
			case '4':find();break;
			case '5':list();break;
			case '6':return 0;
		}
	}
}
