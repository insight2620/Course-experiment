#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct PCB{
	int ID;			//进程标识数
	int PRIORITY;	//进程优先数
	int CPUTIME;	//进程已占用的CPU时间
	int NEEDTIME;	//进程还需占用的CPU时间
	enum state STATE;//进程状态	
	struct PCB *next;
}Node,*LinkList;

enum state{Ready,Runned,Blocked};//定义一个枚举类型
char *state[]={"Ready","Runned","Blocked"};//方便输出进程状态的名称

void InitPCB(PCB *pcb);
void InitList(LinkList *L);
void CreatFromHead(LinkList L,int n);
void PRIORITY_ARRAY(LinkList L,int *n);
int Ready_is_null(LinkList L);
int ToRunned(LinkList L,int *n);
void PRIORITY_CHANGE(LinkList L);
void show_PCB(LinkList L);

void InitPCB(PCB *pcb)					//初始化PCB	
{
	pcb->CPUTIME=0;
	pcb->STATE=Ready;
	pcb->next=NULL;
}
void InitList(LinkList *L)				//初始化单链表
{
	*L=(LinkList)malloc(sizeof(PCB));	//建立头结点
	(*L)->next=NULL;					//建立空的单链表L
}

void CreatFromHead(LinkList L,int n)	//头插法创建单链表（就绪链表）
{
	PCB *pcb;							//定义一个指向PCB结点的指针
	printf("请输入各个进程的标识数，优先数，需占用的CPU时间：\n");
	for(int i=0;i<n;i++)
	{
		pcb=(Node *)malloc(sizeof(PCB));
		InitPCB(pcb);					//初始化PCB
		scanf("%d %d %d",&pcb->ID,&pcb->PRIORITY,&pcb->NEEDTIME);//输入进程信息
		pcb->next=L->next;
		L->next=pcb;
	}
	printf("-------------------------------------------------------------------------------\n");
}

void PRIORITY_ARRAY(LinkList L,int *n)	//冒泡排序:优先级数从高到低排序
{
	PCB *r,*s,*t;
	int change=TRUE;
	for(int i=1;i<=(*n)-1&&change;i++)		//排序n-1趟
	{
		r=L;
		s=r->next;
		t=s->next;
		change=FALSE;
		for(int j=1;j<=(*n)-1;j++)			//冒泡n-i遍
			if(s->PRIORITY<t->PRIORITY)
			{
				r->next=t;				//排序
				if(t->next!=NULL){s->next=t->next;t->next=s;}
				else {t->next=s,s->next=NULL;}
				r=r->next;				//保持r,s,t的顺序继续扫描
				t=s->next;
				change=TRUE;
			}
			else if(s->PRIORITY>t->PRIORITY)
			{
				r=r->next;
				s=s->next;
				t=t->next;
			}
	}
}

int Ready_is_null(LinkList L)	//判断就绪队列是否为空
{
	if(L->next==NULL)
	{
		printf("就绪队列为空！\n");
		return TRUE;	//空则返回1
	}
	else return FALSE;	//不空则返回0
}

int ToRunned(LinkList L,int *n)	//投入运行
{
if(Ready_is_null(L)) return 0;
	PCB *s;
	s=L->next;
	s->STATE=Runned;		//投入运行
	s->CPUTIME+=1;
	s->NEEDTIME-=1;
	if(s->NEEDTIME==0)
	{
		printf("运行进程已占用CPU时间已达到所需运行的时间。已撤销进程：进程%d！\n",s->ID);
		L->next=s->next;
		free(s);(*n)-=1;
		PRIORITY_CHANGE(L);		//调用优先级数改变
	}
	else 
	{
		PRIORITY_CHANGE(L);		//调用优先级数改变
		s->STATE=Ready;
	}
	show_PCB(L);	//每运行完一个时间片后，输出各进程状态
	PRIORITY_ARRAY(L,n);
	if(Ready_is_null(L)) return 0;
	else return 1;
}


void PRIORITY_CHANGE(LinkList L)			//优先级数改变
{
	PCB *t;
	t=L->next;
	while(t!=NULL)
	{
		if(t->STATE==1){t->PRIORITY-=3;t=t->next;}//进程在运行队列中呆一个时间片，优先数减3
		if(t!=NULL&&t->STATE==0)
		{
			t=t->next;
		}
	}
}
void show_PCB(LinkList L)					//当前所有进程状态显示
{
	PCB *r;
	r=L->next;
	while(r!=NULL)
	{
		printf("进程标识符：%d，优先数：%d,已占CPU时间：%d，还需占用CPU时间：%d，当前状态为：%s\n",r->ID,r->PRIORITY,r->CPUTIME,r->NEEDTIME,state[r->STATE]);
		r=r->next;
	}
	printf("-------------------------------------------------------------------------------\n");
}

int main()
{
	LinkList L;
	InitList(&L);
	int n;
	printf("请输入进程数：\n");
	scanf("%d",&n);
	CreatFromHead(L,n);
	PRIORITY_ARRAY(L,&n);
	while(ToRunned(L,&n));
	return 0;
}
