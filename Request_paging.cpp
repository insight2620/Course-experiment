# include<stdio.h>
# include<string.h>
# include<stdlib.h>
#include<math.h>
# include<iostream.h>
# define N 1000

struct zhiling//指令
{
    char caozuo[50];//操作
	int yehao1;//页号
	int yeneidizhi;//页内标志
}zhiling[N]={{"+",0,70},{"-",1,50},{"*",2,15},{"存",3,21},{"取",0,56},{"-",6,40},{"移位",4,53},{"+",5,23},{"存",1,37},{"取",2,78},{"+",4,1},{"存",6,84}};
 
struct yebiao//页表
{
	int yehao;//页号
	int biaozhi;//标志
	int yejiahao;//页架号
	int xiugaibiaozhi;//修改标志
	int cipanweizhi;//磁盘位置
}yebiao[N];
int p[4]={0,1,2,3};//装入主存的页号(用数组装入）

void init()//页表的初值化
{
	int i;
	for(i=0;i<4;i++)
	{
		yebiao[i].yehao=i;
		yebiao[i].biaozhi=1;
		yebiao[i].xiugaibiaozhi=0;
	}//标志前四个页号在主存当中将标志置为1,修改标志为0；
	for(i=4;i<8;i++)
	{
		yebiao[i].yehao=i;
		yebiao[i].biaozhi=0;
		yebiao[i].xiugaibiaozhi=0;
	}//标志后三个的页号不在主存当中将标志置为0，修改标志为0；
	yebiao[0].yejiahao=5;
    yebiao[1].yejiahao=8;
    yebiao[2].yejiahao=9;
    yebiao[3].yejiahao=1;//对0—3的页号设定页架号，即(设定页表在主存的位置）
	yebiao[4].yejiahao=-1;
	yebiao[5].yejiahao=-1;
	yebiao[6].yejiahao=-1;//将没有设定页架号的页架号都设定为-1，便于后面的交换
	yebiao[0].cipanweizhi=11;
    yebiao[1].cipanweizhi=12;
    yebiao[2].cipanweizhi=13;
    yebiao[3].cipanweizhi=21;
    yebiao[4].cipanweizhi=22;
    yebiao[5].cipanweizhi=23;
    yebiao[6].cipanweizhi=21;//对于0—6的页号的磁盘位置赋值（设定页表在辅存当中的位置）
}

void print1()//输出页表
{
	cout<<"*********************作业的页表**********************************"<<endl;
	int i;
	for(i=0;i<7;i++)
	{
		cout<<"  页号  "<<yebiao[i].yehao;
		cout<<"   页内标志  "<<yebiao[i].biaozhi;
		cout<<"   页架号  "<<yebiao[i].yejiahao;
		cout<<"	修改标志  "<<yebiao[i].xiugaibiaozhi;
		cout<<"  磁盘位置  "<<yebiao[i].cipanweizhi;
		cout<<endl;
	}
}
void print2()//输出执行的指令
{
		cout<<"*********************作业的执行指令*********************"<<endl;
	int i;
	for(i=0;i<12;i++)
	{
		cout<<" 操作  "<<zhiling[i].caozuo;
		cout<<"		页号  "<<zhiling[i].yehao1;
		cout<<"		页内标志  "<<zhiling[i].yeneidizhi;
		cout<<endl;
	}
}

void zhuanhuan()//输出作业执行调度算法，先入先出算法
{
	cout<<"*********************作业的执行*********************"<<endl;
	int i;
    int biaozhi1,
		jiaohuanyehao,
		yehao3,xiugaibiaozhi1;//定义一个临时的变量，标志，交换页号，页号
    int k=0;//定义数组的头
    int m=4;//定义数组的长度
    long jueduidizhi;
    for(i=0;i<12;i++)//作业执行指令序列,12个
	{
      yehao3=zhiling[i].yehao1;//yehao3等于指令操作对的页号
      biaozhi1=yebiao[yehao3].biaozhi;//biaozhi1是yehao3对应的标志标志是否在内存
	  cout<<"操作为 "<<zhiling[i].caozuo<<"	页号为  "<<zhiling[i].yehao1<<"	页内标志为  "<<zhiling[i].yeneidizhi<<endl;//执行的指令序列为
	  cout<<"		页号"<<yehao3<<"执行中"<<endl;//yehao3执行
      if(biaozhi1==1)//如果标志等于1则证明在内存当中形成绝对地址
	  {
		  jueduidizhi=yebiao[yehao3].yejiahao*1024+zhiling[i].yeneidizhi;//绝对地址=内存页架号*页架的大小+页内地址
		 
		  if(zhiling[i].caozuo=="cun")//判断是否是存指令
		  {
			  yebiao[yehao3].xiugaibiaozhi=1;//是则修改标志置为1
			  cout<<"		绝对地址是   "<<jueduidizhi<<endl;//输出绝对地址

		  }
		  else
		  {
			   cout<<"		绝对地址是  "<<jueduidizhi<<endl;//不是则直接输出绝对地址   
		  }

	  }
	  if(biaozhi1==0)//如果标志位不是1的时候直接输出*页号
	  {
		  cout<<"		页号 *"<<yehao3<<endl;//如果页号不在主存块当中输出*页号表示发生了中断
		  jiaohuanyehao=p[k];//队列的头指针；
		  cout<<"		将页号为  "<<jiaohuanyehao<<" 的页面置换"<<endl;
		  xiugaibiaozhi1=yebiao[jiaohuanyehao].xiugaibiaozhi;
		  if(xiugaibiaozhi1==1)//执行指令的页号的修改位判断
		  {
			  cout<<"		调出的页号为  "<<jiaohuanyehao<<endl;//修改位是1输出要置换的页号
			  cout<<"		要装入的新页页号  "<<yehao3<<endl;
			  cout<<endl;
		  }
		  else
		  {
			  cout<<"		要装入的新页页号  "<<yehao3<<endl;//修改位是0,输出要进入的新的页表
			  cout<<endl;
		  }
		                            
		  yebiao[yehao3].biaozhi=yebiao[jiaohuanyehao].biaozhi;  //交换标志是否在主存当中
		  yebiao[yehao3].yejiahao=yebiao[jiaohuanyehao].yejiahao;
	      yebiao[jiaohuanyehao].yejiahao=-1;
		  yebiao[jiaohuanyehao].biaozhi=0;
          p[k]=yehao3;
	      k=(k+1)%m;//数组队列向前走
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

