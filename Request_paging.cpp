# include<stdio.h>
# include<string.h>
# include<stdlib.h>
#include<math.h>
# include<iostream.h>
# define N 1000

struct zhiling//ָ��
{
    char caozuo[50];//����
	int yehao1;//ҳ��
	int yeneidizhi;//ҳ�ڱ�־
}zhiling[N]={{"+",0,70},{"-",1,50},{"*",2,15},{"��",3,21},{"ȡ",0,56},{"-",6,40},{"��λ",4,53},{"+",5,23},{"��",1,37},{"ȡ",2,78},{"+",4,1},{"��",6,84}};
 
struct yebiao//ҳ��
{
	int yehao;//ҳ��
	int biaozhi;//��־
	int yejiahao;//ҳ�ܺ�
	int xiugaibiaozhi;//�޸ı�־
	int cipanweizhi;//����λ��
}yebiao[N];
int p[4]={0,1,2,3};//װ�������ҳ��(������װ�룩

void init()//ҳ��ĳ�ֵ��
{
	int i;
	for(i=0;i<4;i++)
	{
		yebiao[i].yehao=i;
		yebiao[i].biaozhi=1;
		yebiao[i].xiugaibiaozhi=0;
	}//��־ǰ�ĸ�ҳ�������浱�н���־��Ϊ1,�޸ı�־Ϊ0��
	for(i=4;i<8;i++)
	{
		yebiao[i].yehao=i;
		yebiao[i].biaozhi=0;
		yebiao[i].xiugaibiaozhi=0;
	}//��־��������ҳ�Ų������浱�н���־��Ϊ0���޸ı�־Ϊ0��
	yebiao[0].yejiahao=5;
    yebiao[1].yejiahao=8;
    yebiao[2].yejiahao=9;
    yebiao[3].yejiahao=1;//��0��3��ҳ���趨ҳ�ܺţ���(�趨ҳ���������λ�ã�
	yebiao[4].yejiahao=-1;
	yebiao[5].yejiahao=-1;
	yebiao[6].yejiahao=-1;//��û���趨ҳ�ܺŵ�ҳ�ܺŶ��趨Ϊ-1�����ں���Ľ���
	yebiao[0].cipanweizhi=11;
    yebiao[1].cipanweizhi=12;
    yebiao[2].cipanweizhi=13;
    yebiao[3].cipanweizhi=21;
    yebiao[4].cipanweizhi=22;
    yebiao[5].cipanweizhi=23;
    yebiao[6].cipanweizhi=21;//����0��6��ҳ�ŵĴ���λ�ø�ֵ���趨ҳ���ڸ��浱�е�λ�ã�
}

void print1()//���ҳ��
{
	cout<<"*********************��ҵ��ҳ��**********************************"<<endl;
	int i;
	for(i=0;i<7;i++)
	{
		cout<<"  ҳ��  "<<yebiao[i].yehao;
		cout<<"   ҳ�ڱ�־  "<<yebiao[i].biaozhi;
		cout<<"   ҳ�ܺ�  "<<yebiao[i].yejiahao;
		cout<<"	�޸ı�־  "<<yebiao[i].xiugaibiaozhi;
		cout<<"  ����λ��  "<<yebiao[i].cipanweizhi;
		cout<<endl;
	}
}
void print2()//���ִ�е�ָ��
{
		cout<<"*********************��ҵ��ִ��ָ��*********************"<<endl;
	int i;
	for(i=0;i<12;i++)
	{
		cout<<" ����  "<<zhiling[i].caozuo;
		cout<<"		ҳ��  "<<zhiling[i].yehao1;
		cout<<"		ҳ�ڱ�־  "<<zhiling[i].yeneidizhi;
		cout<<endl;
	}
}

void zhuanhuan()//�����ҵִ�е����㷨�������ȳ��㷨
{
	cout<<"*********************��ҵ��ִ��*********************"<<endl;
	int i;
    int biaozhi1,
		jiaohuanyehao,
		yehao3,xiugaibiaozhi1;//����һ����ʱ�ı�������־������ҳ�ţ�ҳ��
    int k=0;//���������ͷ
    int m=4;//��������ĳ���
    long jueduidizhi;
    for(i=0;i<12;i++)//��ҵִ��ָ������,12��
	{
      yehao3=zhiling[i].yehao1;//yehao3����ָ������Ե�ҳ��
      biaozhi1=yebiao[yehao3].biaozhi;//biaozhi1��yehao3��Ӧ�ı�־��־�Ƿ����ڴ�
	  cout<<"����Ϊ "<<zhiling[i].caozuo<<"	ҳ��Ϊ  "<<zhiling[i].yehao1<<"	ҳ�ڱ�־Ϊ  "<<zhiling[i].yeneidizhi<<endl;//ִ�е�ָ������Ϊ
	  cout<<"		ҳ��"<<yehao3<<"ִ����"<<endl;//yehao3ִ��
      if(biaozhi1==1)//�����־����1��֤�����ڴ浱���γɾ��Ե�ַ
	  {
		  jueduidizhi=yebiao[yehao3].yejiahao*1024+zhiling[i].yeneidizhi;//���Ե�ַ=�ڴ�ҳ�ܺ�*ҳ�ܵĴ�С+ҳ�ڵ�ַ
		 
		  if(zhiling[i].caozuo=="cun")//�ж��Ƿ��Ǵ�ָ��
		  {
			  yebiao[yehao3].xiugaibiaozhi=1;//�����޸ı�־��Ϊ1
			  cout<<"		���Ե�ַ��   "<<jueduidizhi<<endl;//������Ե�ַ

		  }
		  else
		  {
			   cout<<"		���Ե�ַ��  "<<jueduidizhi<<endl;//������ֱ��������Ե�ַ   
		  }

	  }
	  if(biaozhi1==0)//�����־λ����1��ʱ��ֱ�����*ҳ��
	  {
		  cout<<"		ҳ�� *"<<yehao3<<endl;//���ҳ�Ų�������鵱�����*ҳ�ű�ʾ�������ж�
		  jiaohuanyehao=p[k];//���е�ͷָ�룻
		  cout<<"		��ҳ��Ϊ  "<<jiaohuanyehao<<" ��ҳ���û�"<<endl;
		  xiugaibiaozhi1=yebiao[jiaohuanyehao].xiugaibiaozhi;
		  if(xiugaibiaozhi1==1)//ִ��ָ���ҳ�ŵ��޸�λ�ж�
		  {
			  cout<<"		������ҳ��Ϊ  "<<jiaohuanyehao<<endl;//�޸�λ��1���Ҫ�û���ҳ��
			  cout<<"		Ҫװ�����ҳҳ��  "<<yehao3<<endl;
			  cout<<endl;
		  }
		  else
		  {
			  cout<<"		Ҫװ�����ҳҳ��  "<<yehao3<<endl;//�޸�λ��0,���Ҫ������µ�ҳ��
			  cout<<endl;
		  }
		                            
		  yebiao[yehao3].biaozhi=yebiao[jiaohuanyehao].biaozhi;  //������־�Ƿ������浱��
		  yebiao[yehao3].yejiahao=yebiao[jiaohuanyehao].yejiahao;
	      yebiao[jiaohuanyehao].yejiahao=-1;
		  yebiao[jiaohuanyehao].biaozhi=0;
          p[k]=yehao3;
	      k=(k+1)%m;//���������ǰ��
		  yebiao[jiaohuanyehao].xiugaibiaozhi=0;
		  yebiao[yehao3].xiugaibiaozhi=1;
	  }
	}
}
     
void main()
{
    init();
    //init2();
	print1();
	print2();
	zhuanhuan();
}

