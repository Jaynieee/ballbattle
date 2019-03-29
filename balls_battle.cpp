#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib") 
//设置方向的结构体
struct FX
{
	int x;//水平 向右
	int y;//行 向上
};

//设置球的结构体
struct Ball
{
	int x,y;//坐标
	int radius;//半径
	COLORREF color;//颜色
	FX   fx;//方向
};



COLORREF colors[7]={BROWN,BLUE,GREEN,RED,MAGENTA,YELLOW,LIGHTRED};//颜色

//定义全局变量
Ball myBall;
Ball enemyBalls[20];
HWND g_hWnd;
//自己球是否存货
bool IsLive = true;
//统计吃掉了多少个球
int count = 0;
//初始化游戏 准备工作
void initGame()
{
	//1.1窗口  GUI  有这些win32 MFC QT openGL openCV
	g_hWnd=initgraph(600,500);//定时器时语句
	//initgraph(600,500);//F12//或者工具查找
	
	//1.2准备球
	//1.2.1自己球
	myBall.x = 600;
	myBall.y = 0;
	myBall.radius = 10;
	myBall.color = LIGHTMAGENTA;
	
	//设置随机数种子 拿数位置随着时间变化
	srand(time(0));//真随机

	//放个音乐
	mciSendString("open 2.mp3",NULL,NULL,NULL);
    mciSendString("play 2.mp3",NULL,0,NULL);
	
	//1.2.2敌人球
	for (int i=0;i<20;i++)
	{
	      //坐标
		  enemyBalls[i].x=20;
		  enemyBalls[i].y=500-20;

		  //颜色
		  enemyBalls[i].color=colors[rand()%7];//假随机，从固定列表拿
		  //大小
		  enemyBalls[i].radius=rand()%50+1;
	      //方向
		  enemyBalls[i].fx.x=rand()%10+1;
          enemyBalls[i].fx.y=rand()%10+1;
	}
}

//游戏界面的绘制
void drawGame()
{
	//解决闪烁//开始前添加
	BeginBatchDraw();
	//2.0先擦除屏幕上的画面
	cleardevice();

	//2.1画背景

	//2.2画球

	//2.2.1画自己球
	    //设置圆的颜色 画笔 画刷

	     setfillcolor(myBall.color);//填充颜色
	     //画填充圆
	     solidcircle(myBall.x,myBall.y,myBall.radius);//默认白色
	//2.2.2画敌人球
     for (int i=0;i<20;i++)
	 {
	 	 setfillcolor(enemyBalls[i].color);//填充颜色	    
	     solidcircle(enemyBalls[i].x,enemyBalls[i].y,enemyBalls[i].radius);
	 }
	//2.3分数
	 char temp[256] ={0};
	 sprintf(temp,"当前分数：%d",count);
	 settextcolor(RED);
     outtextxy(400,30,temp);
     EndBatchDraw();//防止闪烁
}

//控制游戏

void controlGame()
{
    MOUSEMSG msg;
     //鼠标控制
	while (1){
	//3.1拿到鼠标信息
	msg = GetMouseMsg();
    //3.2根据鼠标信息来控制球
	myBall.x=msg.x;
	myBall.y=msg.y;
	
	}
	

}
//敌人球移动
void move()
{
	int x,y;

	//一直在不停地画
	//每隔一段时间调用一次move函数来改变敌人球的位置
	for (int i=0;i<20;i++)
	{
	enemyBalls[i].x+=enemyBalls[i].fx.x;
	enemyBalls[i].y-=enemyBalls[i].fx.y;//往上走 减法
	}
	//检查是否出界
	for(int i=0;i<20;i++)
	{
		if( (enemyBalls[i].x  > (600 + enemyBalls[i].radius)) ||			
			(enemyBalls[i].y < (0 - enemyBalls[i].radius))	)
		{
		  //坐标
		  enemyBalls[i].x=20;
		  enemyBalls[i].y=500-20;

		  //颜色
		  enemyBalls[i].color=colors[rand()%7];//假随机，从固定列表拿
		  //大小
		  enemyBalls[i].radius=rand()%50+1;
	      //方向
		  enemyBalls[i].fx.x=rand()%10+1;
          enemyBalls[i].fx.y=rand()%10+1;		
		}
		//碰撞检测
		//获得敌人球和自己球x轴方向的距离
		x= ((enemyBalls[i].x>myBall.x)?(enemyBalls[i].x-myBall.x) :(myBall.x-enemyBalls[i].x)) ;
		y= ((enemyBalls[i].y>myBall.y)?(enemyBalls[i].y-myBall.y) :(myBall.y-enemyBalls[i].y)) ;
		if((x*x+y*y)<=(enemyBalls[i].radius+myBall.radius)*(enemyBalls[i].radius+myBall.radius))
		{
		      if(enemyBalls[i].radius>myBall.radius)
			  {
			    IsLive = false;
			  }
			  else
			  {
				  myBall.radius += 2;
				  count++;
				  //坐标
		  enemyBalls[i].x=20;
		  enemyBalls[i].y=500-20;

		  //颜色
		  enemyBalls[i].color=colors[rand()%7];//假随机，从固定列表拿
		  //大小
		  enemyBalls[i].radius=rand()%50+1;
	      //方向
		  enemyBalls[i].fx.x=rand()%10+1;
          enemyBalls[i].fx.y=rand()%10+1;	
			  }
		}
	}
}

void thread2()
{
	while(1)
	{
	move();
	Sleep(50);
	}
}

//碰撞检测 


int main()
{
	initGame();

	//方法一用线程
	//CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)thread2,NULL,NULL,NULL);
	//方法二定时器,利用窗口的句柄
	//          句柄   定时器id 间隔时间 定时器函数
	SetTimer(g_hWnd,10086,50,(TIMERPROC)move);

	//控制球的线程
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)controlGame,NULL,NULL,NULL);

	while(IsLive)
	{
	drawGame();
	}

	settextcolor(RED);
	outtextxy(300, 150, "Game Over");// 在指定位置输出字符串
	while(1);
	return 0;
}