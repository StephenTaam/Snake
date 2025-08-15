//顺序:移动->生成食粮->检查是否吃到自己?(结束)->检查是否吃了?(生成,加入,加分)->继续移动
#include<easyx.h>
#include<iostream.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <windows.h>
#include <mmsystem.h>		//播放音乐头文件
#pragma comment(lib, "winmm.lib")	//导入winmm.lib库,它才可以支持对windows多媒体的编程.
typedef struct a
{
	int x;int y;//之前的坐标
	int z; int j;//现在的坐标
	struct a*next;
}data;

int cou,bt=10,dv=0;//用于加分的变量
int ig=0;//计算历史成绩用的
char gk;//选择难度用的
int distance=70000000;//每次移动一个单位的时候循环的量,用来控制蛇移动的快慢,默认有一个值
char g='w';//决定移动的方向
data *p;//链表地址
int a,b;//蛇头坐标
int f1=0;int a1,b1;//控制蛇粮的变量

void file()//打开文件获得历史最好分数
{
	FILE *p1;char s[10];
    p1=fopen("data.txt","r");
	fgets(s,10,p1);
	ig=atoi (s);//字符串转化成数字
	fclose(p1);
}
void save()//保存分数
{
   if(cou>ig)
   {
     FILE *p1;
     p1=fopen("data.txt","w");
	 char s[10];
     sprintf(s, "%d", cou);//将整形转换成字符串
	 fputs(s,p1);
	 fclose(p1);
   }
}
void init()//初始化链表以及生成蛇,确定第一个节点
{
	a=300;b=300;
	p=(data*)malloc(sizeof(data));
	p->next=NULL;
	p->z=a;//之前的坐标不赋值
	p->j=b;
	solidcircle(a, b, 10);
}
void count()//用于计算分数的函数
{
  char s[2];
  if(dv==1) 
  {
	  dv=0;
	  cou=cou+bt;
      sprintf(s, "%d", cou);//将整形a转换成字符串
      outtextxy(5, 5, s);//将字符串输出到界面上
	  sprintf(s, "%d", ig);//输出纪录分数
	  outtextxy(5, 20, s);
  }
  else//防止被蛇覆盖掉数字
  {   
   	  sprintf(s, "%d", cou);//将整形a转换成字符串
      outtextxy(5, 5, s);}//将字符串输出到界面上
	  sprintf(s, "%d", ig);//输出纪录分数
	  outtextxy(5, 20, s);
}
void eat()//生成蛇粮
{
	int a2,b2;//存以前的蛇粮坐标,用于抹掉
    srand(time(NULL));
   if(f1==0)//图中没有蛇粮f就会等于0,有就等于1,没有会自己加入
   {
	   setfillcolor(BLUE);//蛇粮颜色
	   a2=a1;//以前的坐标存好
	   b2=b1;
	   a1=rand()%685+8;//随机更新现在的坐标
	   b1=rand()%465+8;
	   f1=1;
	   clearcircle(a2,b2,5);//抹掉和生成新的食粮
       solidcircle(a1, b1, 5);
	   setfillcolor(RED);//填充颜色变回红色
   }
   else//这一步是为了防止食物被蛇身抹掉
   {
	   setfillcolor(BLUE);//蛇粮颜色
       solidcircle(a1, b1, 5);
	   setfillcolor(RED);//填充颜色变回红色
   }
}
void add()//加入新结点
{
	int x,y;//记录最后一个结点之前的位置,用来帮助新结点插入
	data*p1=p;
	while(p1->next!=NULL)//找到最后一个结点
		p1=p1->next;
	x=p1->x;//记录
	y=p1->y;
	p1->next=(data*)malloc(sizeof(data));//生成新结点
	p1=p1->next;//指着新生成的节点;
    p1->next=NULL;
	p1->z=x;
	p1->j=y;
    solidcircle(x, y,10);
}
int cheakeat()//检查有没有吃到蛇粮
{
	int i;double k;
	k=sqrt((a-a1)*(a-a1)+(b-b1)*(b-b1));
	if(k<=15)i=1;
	else i=0;
	return (i);
}
int cheakeatmyself()//检查有没有吃到自己
{
	int i=0;double k;
	data*p1=p->next;
	while(p1!=NULL)
	{
		k=sqrt((p1->z-a)*(p1->z-a)+(p1->j-b)*(p1->j-b));
		if(k<10){i=1;break;}
		p1=p1->next;
	}
	return (i);
}
void w()//向上移动
{
	int i,f=0;//用于控制移动速度和确定是否跳出循环
	int t;//检查是否吃了或者吃到自己;
	for(;f==0&&b>=10;)//是否改变运动方向和是否撞墙决定是否跳出循环
	{
		for(i=0;i!=distance;i++){}//控制移动快慢的关键
	    int x,y;//用来存放数据,在交换数据的时候用得上
	    data*p1=p;
	    p->x=p->z;//现在要有新的坐标啦,所以之前的现在变成现在的之前
	    p->y=p->j;
	    p->j=p->j-10;//向上移动所以横坐标不变纵坐标-10    ******为什么距离是10呢?移动的距离要和蛇本身加入的时候的理想间距一样,不然蛇会压缩在一起
	    x=p->x;//把现在的之前放入,待会要交换
	    y=p->y;
	    clearcircle(p->x,p->y,10);//原来的圆要清空
        solidcircle(p->z, p->j,10);//生成一个圆
		a=p->z;//控制蛇头的全局坐标a,b也要改变
		b=p->j;
	    p1=p1->next;
	    while(p1!=NULL)//如果有一个以上的结点,一个一个来变换坐标和移动
		{
		p1->x=p1->z;//现在要有新的坐标啦,所以之前的现在变成现在的之前
		p1->y=p1->j;
		p1->z=x;//把刚才放入的前一个结点的之前的坐标放入现在的位置
		p1->j=y;
		x=p1->x;//我的之前的坐标也要留给下一个结点
		y=p1->y;
		clearcircle(p1->x,p1->y,10);//原来的圆要清空
        solidcircle(p1->z, p1->j,10);//生成一个圆
		p1=p1->next;
		}
		eat();//生成食粮
		count();//防止被覆盖
		t=cheakeatmyself();//检查是否吃了自己
		if(t==1)b=0;
		t=cheakeat();//检查是否吃了
		if(t==1){f1=0;dv=1;count();add();eat();}
		f=kbhit();//检查键盘是否有动作
		if(f!=0)//如果有动作
		{
			g=getch();
			if(g!='a'&&g!='d')//收集动作并检查是什么,如果是不向其他方向运动,就不跳出循环
				f=0;
		}
	}
}
void s()//向下移动
{
	int i,f=0;//用于控制移动速度和确定是否跳出循环
	int t;//检查是否吃了或者吃到自己;
	for(;f==0&&b<=470;)//是否改变运动方向和是否撞墙决定是否跳出循环
	{
		for(i=0;i!=distance;i++){}//控制移动快慢的关键
	    int x,y;//用来存放数据,在交换数据的时候用得上
	    data*p1=p;
	    p->x=p->z;//现在要有新的坐标啦,所以之前的现在变成现在的之前
	    p->y=p->j;
	    p->j=p->j+10;//向上移动所以横坐标不变纵坐标+10    ******为什么距离是10呢?移动的距离要和蛇本身加入的时候的理想间距一样,不然蛇会压缩在一起
	    x=p->x;//把现在的之前放入,待会要交换
	    y=p->y;
	    clearcircle(p->x,p->y,10);//原来的圆要清空
        solidcircle(p->z, p->j,10);//生成一个圆
		a=p->z;//控制蛇头的全局坐标a,b也要改变
		b=p->j;
	    p1=p1->next;
	    while(p1!=NULL)//如果有一个以上的结点,一个一个来变换坐标和移动
		{
		p1->x=p1->z;//现在要有新的坐标啦,所以之前的现在变成现在的之前
		p1->y=p1->j;
		p1->z=x;//把刚才放入的前一个结点的之前的坐标放入现在的位置
		p1->j=y;
		x=p1->x;//我的之前的坐标也要留给下一个结点
		y=p1->y;
		clearcircle(p1->x,p1->y,10);//原来的圆要清空
        solidcircle(p1->z, p1->j,10);//生成一个圆
		p1=p1->next;
		}
		eat();//生成食粮
		count();//防止分数被蛇覆盖
		t=cheakeatmyself();//检查是否吃了自己
		if(t==1)b=480;
		t=cheakeat();//检查是否吃了
		if(t==1){f1=0;dv=1;count();add();eat();}
		f=kbhit();//检查键盘是否有动作
		if(f!=0)//如果有动作
		{
			g=getch();
			if(g!='a'&&g!='d')//收集动作并检查是什么,如果是不向其他方向运动,就不跳出循环
				f=0;
		}
	}
}
void aa()//向左移动
{
	int i,f=0;//用于控制移动速度和确定是否跳出循环
	int t;//检查是否吃了或者吃到自己;
	for(;f==0&&a>=10;)//是否改变运动方向和是否撞墙决定是否跳出循环
	{
		for(i=0;i!=distance;i++){}//控制移动快慢的关键
	    int x,y;//用来存放数据,在交换数据的时候用得上
	    data*p1=p;
	    p->x=p->z;//现在要有新的坐标啦,所以之前的现在变成现在的之前
	    p->y=p->j;
	    p->z=p->z-10;//向左移动所以纵坐标不变横坐标-10    ******为什么距离是10呢?移动的距离要和蛇本身加入的时候的理想间距一样,不然蛇会压缩在一起
	    x=p->x;//把现在的之前放入,待会要交换
	    y=p->y;
	    clearcircle(p->x,p->y,10);//原来的圆要清空
        solidcircle(p->z, p->j,10);//生成一个圆
		a=p->z;//控制蛇头的全局坐标a,b也要改变
		b=p->j;
	    p1=p1->next;
	    while(p1!=NULL)//如果有一个以上的结点,一个一个来变换坐标和移动
		{
		p1->x=p1->z;//现在要有新的坐标啦,所以之前的现在变成现在的之前
		p1->y=p1->j;
		p1->z=x;//把刚才放入的前一个结点的之前的坐标放入现在的位置
		p1->j=y;
		x=p1->x;//我的之前的坐标也要留给下一个结点
		y=p1->y;
		clearcircle(p1->x,p1->y,10);//原来的圆要清空
        solidcircle(p1->z, p1->j,10);//生成一个圆
		p1=p1->next;
		}
		eat();//生成食粮
		count();
		t=cheakeatmyself();//检查是否吃了自己
		if(t==1)a=0;
		t=cheakeat();//检查是否吃了
		if(t==1){f1=0;dv=1;count();add();eat();}
		f=kbhit();//检查键盘是否有动作
		if(f!=0)//如果有动作
		{
			g=getch();
			if(g!='w'&&g!='s')//收集动作并检查是什么,如果是不向其他方向运动,就不跳出循环
				f=0;
		}
	}
}
void d()//向右移动
{
	int i,f=0;//用于控制移动速度和确定是否跳出循环
	int t;//检查是否吃了或者吃到自己;
	for(;f==0&&a<=690;)//是否改变运动方向和是否撞墙决定是否跳出循环
	{
		for(i=0;i!=distance;i++){}//控制移动快慢的关键
	    int x,y;//用来存放数据,在交换数据的时候用得上
	    data*p1=p;
	    p->x=p->z;//现在要有新的坐标啦,所以之前的现在变成现在的之前
	    p->y=p->j;
	    p->z=p->z+10;//向右移动所以纵坐标不变横坐标+10    ******为什么距离是10呢?移动的距离要和蛇本身加入的时候的理想间距一样,不然蛇会压缩在一起
	    x=p->x;//把现在的之前放入,待会要交换
	    y=p->y;
	    clearcircle(p->x,p->y,10);//原来的圆要清空
        solidcircle(p->z, p->j,10);//生成一个圆
		a=p->z;//控制蛇头的全局坐标a,b也要改变
		b=p->j;
	    p1=p1->next;
	    while(p1!=NULL)//如果有一个以上的结点,一个一个来变换坐标和移动
		{
		p1->x=p1->z;//现在要有新的坐标啦,所以之前的现在变成现在的之前
		p1->y=p1->j;
		p1->z=x;//把刚才放入的前一个结点的之前的坐标放入现在的位置
		p1->j=y;
		x=p1->x;//我的之前的坐标也要留给下一个结点
		y=p1->y;
		clearcircle(p1->x,p1->y,10);//原来的圆要清空
        solidcircle(p1->z, p1->j,10);//生成一个圆
		p1=p1->next;
		}
		eat();//生成食粮
		count();
		t=cheakeatmyself();//检查是否吃了自己
		if(t==1)a=700;
		t=cheakeat();//检查是否吃了
		if(t==1){f1=0;dv=1;count();add();eat();}
		f=kbhit();//检查键盘是否有动作
		if(f!=0)//如果有动作
		{
			g=getch();
			if(g!='w'&&g!='s')//收集动作并检查是什么,如果是不向其他方向运动,就不跳出循环
				f=0;
		}
	}
}
int main()
{
	mciSendString("play music.wav", NULL, 0, NULL);//打开音乐
	int i=1,j=1;char o;//用于控制main函数的循环
	initgraph(700, 480);//初始化
	setbkcolor(RGB(0,200,200));
	setfillcolor(RED);
	cleardevice();
	outtextxy(300,10,"贪吃蛇小游戏");
	outtextxy(10,50,"规则");
	outtextxy(50,70,"1:按w s a d移动蛇蛇");
	outtextxy(50,90,"2:撞到边界也是game over");
	outtextxy(50,110,"3:蛇蛇不可以直接向后退");
	outtextxy(310,180,"--希望给你无聊的假期带来一丝乐趣：）按任意键继续");
	_getch();
for(;i==1;)	
{
	file();//打开历史成绩文件
	cleardevice();
    outtextxy(10,50,"选择游戏难度");
	outtextxy(50,70,"a.超慢");
	outtextxy(50,90,"b.简单");
	outtextxy(50,110,"c.普通（若不选,按回车则默认为普通难度或刚才结束时候的难度）");
	outtextxy(50,130,"d.难");
	outtextxy(50,150,"e.无敌快速");
	char sb[5];
	sprintf(sb, "%d", ig);
    outtextxy(50,200,"历史最好成绩:");
	outtextxy(150,200,sb);
	char gk=getch();//选择难度
	if(gk=='c'){distance=70000000;bt=10;}
	else if(gk=='a'){distance=110000000;bt=3;}
	else if(gk=='b'){distance=90000000;bt=7;}
    else if(gk=='d'){distance=50000000;bt=15;}
	else if(gk=='e'){distance=30000000;bt=20;}
	cou=0;//分数清0
	g='w';
	j=1;
	cleardevice();
	init();//生成蛇
	for(;j==1;)
	{
	  if(a==0||a==700||b==0||b==480)//撞墙等失败后...
	  {
		  save();//保存
		  char s[2];
		  outtextxy(300,300,"游戏结束，一共");
		  sprintf(s, "%d", cou);//将整形a转换成字符串
          outtextxy(420, 300, s);//将字符串输出到界面上
          outtextxy(465, 300,"分");
		  outtextxy(300, 320,"历史记录是");
		  outtextxy(380, 320,sb);
		  outtextxy(430, 320,"分");
		  outtextxy(300,360,"y.重新来一次");
		  outtextxy(300,380,"n.退出");
		  j=0;
		  do
          {
			  o=getch();
		      if(o=='n')i=0;
		  }while(o!='y'&&o!='n');
	  }
	  else
	  {
	    if(g=='w')w();
	    else if(g=='s')s();
	    else if(g=='a')aa();
	    else if(g=='d')d();
	  }
	}
}
       closegraph();
	   printf("谢谢游玩!\n");
        _getch();
	    return 1;
}