#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct PCB{
	int ID;			//���̱�ʶ��
	int PRIORITY;	//����������
	int CPUTIME;	//������ռ�õ�CPUʱ��
	int NEEDTIME;	//���̻���ռ�õ�CPUʱ��
	enum state STATE;//����״̬	
	struct PCB *next;
}Node,*LinkList;

enum state{Ready,Runned,Blocked};//����һ��ö������
char *state[]={"Ready","Runned","Blocked"};//�����������״̬������

void InitPCB(PCB *pcb);
void InitList(LinkList *L);
void CreatFromHead(LinkList L,int n);
void PRIORITY_ARRAY(LinkList L,int *n);
int Ready_is_null(LinkList L);
int ToRunned(LinkList L,int *n);
void PRIORITY_CHANGE(LinkList L);
void show_PCB(LinkList L);

void InitPCB(PCB *pcb)					//��ʼ��PCB	
{
	pcb->CPUTIME=0;
	pcb->STATE=Ready;
	pcb->next=NULL;
}
void InitList(LinkList *L)				//��ʼ��������
{
	*L=(LinkList)malloc(sizeof(PCB));	//����ͷ���
	(*L)->next=NULL;					//�����յĵ�����L
}

void CreatFromHead(LinkList L,int n)	//ͷ�巨������������������
{
	PCB *pcb;							//����һ��ָ��PCB����ָ��
	printf("������������̵ı�ʶ��������������ռ�õ�CPUʱ�䣺\n");
	for(int i=0;i<n;i++)
	{
		pcb=(Node *)malloc(sizeof(PCB));
		InitPCB(pcb);					//��ʼ��PCB
		scanf("%d %d %d",&pcb->ID,&pcb->PRIORITY,&pcb->NEEDTIME);//���������Ϣ
		pcb->next=L->next;
		L->next=pcb;
	}
	printf("-------------------------------------------------------------------------------\n");
}

void PRIORITY_ARRAY(LinkList L,int *n)	//ð������:���ȼ����Ӹߵ�������
{
	PCB *r,*s,*t;
	int change=TRUE;
	for(int i=1;i<=(*n)-1&&change;i++)		//����n-1��
	{
		r=L;
		s=r->next;
		t=s->next;
		change=FALSE;
		for(int j=1;j<=(*n)-1;j++)			//ð��n-i��
			if(s->PRIORITY<t->PRIORITY)
			{
				r->next=t;				//����
				if(t->next!=NULL){s->next=t->next;t->next=s;}
				else {t->next=s,s->next=NULL;}
				r=r->next;				//����r,s,t��˳�����ɨ��
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

int Ready_is_null(LinkList L)	//�жϾ��������Ƿ�Ϊ��
{
	if(L->next==NULL)
	{
		printf("��������Ϊ�գ�\n");
		return TRUE;	//���򷵻�1
	}
	else return FALSE;	//�����򷵻�0
}

int ToRunned(LinkList L,int *n)	//Ͷ������
{
if(Ready_is_null(L)) return 0;
	PCB *s;
	s=L->next;
	s->STATE=Runned;		//Ͷ������
	s->CPUTIME+=1;
	s->NEEDTIME-=1;
	if(s->NEEDTIME==0)
	{
		printf("���н�����ռ��CPUʱ���Ѵﵽ�������е�ʱ�䡣�ѳ������̣�����%d��\n",s->ID);
		L->next=s->next;
		free(s);(*n)-=1;
		PRIORITY_CHANGE(L);		//�������ȼ����ı�
	}
	else 
	{
		PRIORITY_CHANGE(L);		//�������ȼ����ı�
		s->STATE=Ready;
	}
	show_PCB(L);	//ÿ������һ��ʱ��Ƭ�����������״̬
	PRIORITY_ARRAY(L,n);
	if(Ready_is_null(L)) return 0;
	else return 1;
}


void PRIORITY_CHANGE(LinkList L)			//���ȼ����ı�
{
	PCB *t;
	t=L->next;
	while(t!=NULL)
	{
		if(t->STATE==1){t->PRIORITY-=3;t=t->next;}//���������ж����д�һ��ʱ��Ƭ����������3
		if(t!=NULL&&t->STATE==0)
		{
			t=t->next;
		}
	}
}
void show_PCB(LinkList L)					//��ǰ���н���״̬��ʾ
{
	PCB *r;
	r=L->next;
	while(r!=NULL)
	{
		printf("���̱�ʶ����%d����������%d,��ռCPUʱ�䣺%d������ռ��CPUʱ�䣺%d����ǰ״̬Ϊ��%s\n",r->ID,r->PRIORITY,r->CPUTIME,r->NEEDTIME,state[r->STATE]);
		r=r->next;
	}
	printf("-------------------------------------------------------------------------------\n");
}

int main()
{
	LinkList L;
	InitList(&L);
	int n;
	printf("�������������\n");
	scanf("%d",&n);
	CreatFromHead(L,n);
	PRIORITY_ARRAY(L,&n);
	while(ToRunned(L,&n));
	return 0;
}
