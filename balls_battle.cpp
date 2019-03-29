#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib") 
//���÷���Ľṹ��
struct FX
{
	int x;//ˮƽ ����
	int y;//�� ����
};

//������Ľṹ��
struct Ball
{
	int x,y;//����
	int radius;//�뾶
	COLORREF color;//��ɫ
	FX   fx;//����
};



COLORREF colors[7]={BROWN,BLUE,GREEN,RED,MAGENTA,YELLOW,LIGHTRED};//��ɫ

//����ȫ�ֱ���
Ball myBall;
Ball enemyBalls[20];
HWND g_hWnd;
//�Լ����Ƿ���
bool IsLive = true;
//ͳ�ƳԵ��˶��ٸ���
int count = 0;
//��ʼ����Ϸ ׼������
void initGame()
{
	//1.1����  GUI  ����Щwin32 MFC QT openGL openCV
	g_hWnd=initgraph(600,500);//��ʱ��ʱ���
	//initgraph(600,500);//F12//���߹��߲���
	
	//1.2׼����
	//1.2.1�Լ���
	myBall.x = 600;
	myBall.y = 0;
	myBall.radius = 10;
	myBall.color = LIGHTMAGENTA;
	
	//������������� ����λ������ʱ��仯
	srand(time(0));//�����

	//�Ÿ�����
	mciSendString("open 2.mp3",NULL,NULL,NULL);
    mciSendString("play 2.mp3",NULL,0,NULL);
	
	//1.2.2������
	for (int i=0;i<20;i++)
	{
	      //����
		  enemyBalls[i].x=20;
		  enemyBalls[i].y=500-20;

		  //��ɫ
		  enemyBalls[i].color=colors[rand()%7];//��������ӹ̶��б���
		  //��С
		  enemyBalls[i].radius=rand()%50+1;
	      //����
		  enemyBalls[i].fx.x=rand()%10+1;
          enemyBalls[i].fx.y=rand()%10+1;
	}
}

//��Ϸ����Ļ���
void drawGame()
{
	//�����˸//��ʼǰ���
	BeginBatchDraw();
	//2.0�Ȳ�����Ļ�ϵĻ���
	cleardevice();

	//2.1������

	//2.2����

	//2.2.1���Լ���
	    //����Բ����ɫ ���� ��ˢ

	     setfillcolor(myBall.color);//�����ɫ
	     //�����Բ
	     solidcircle(myBall.x,myBall.y,myBall.radius);//Ĭ�ϰ�ɫ
	//2.2.2��������
     for (int i=0;i<20;i++)
	 {
	 	 setfillcolor(enemyBalls[i].color);//�����ɫ	    
	     solidcircle(enemyBalls[i].x,enemyBalls[i].y,enemyBalls[i].radius);
	 }
	//2.3����
	 char temp[256] ={0};
	 sprintf(temp,"��ǰ������%d",count);
	 settextcolor(RED);
     outtextxy(400,30,temp);
     EndBatchDraw();//��ֹ��˸
}

//������Ϸ

void controlGame()
{
    MOUSEMSG msg;
     //������
	while (1){
	//3.1�õ������Ϣ
	msg = GetMouseMsg();
    //3.2���������Ϣ��������
	myBall.x=msg.x;
	myBall.y=msg.y;
	
	}
	

}
//�������ƶ�
void move()
{
	int x,y;

	//һֱ�ڲ�ͣ�ػ�
	//ÿ��һ��ʱ�����һ��move�������ı�������λ��
	for (int i=0;i<20;i++)
	{
	enemyBalls[i].x+=enemyBalls[i].fx.x;
	enemyBalls[i].y-=enemyBalls[i].fx.y;//������ ����
	}
	//����Ƿ����
	for(int i=0;i<20;i++)
	{
		if( (enemyBalls[i].x  > (600 + enemyBalls[i].radius)) ||			
			(enemyBalls[i].y < (0 - enemyBalls[i].radius))	)
		{
		  //����
		  enemyBalls[i].x=20;
		  enemyBalls[i].y=500-20;

		  //��ɫ
		  enemyBalls[i].color=colors[rand()%7];//��������ӹ̶��б���
		  //��С
		  enemyBalls[i].radius=rand()%50+1;
	      //����
		  enemyBalls[i].fx.x=rand()%10+1;
          enemyBalls[i].fx.y=rand()%10+1;		
		}
		//��ײ���
		//��õ�������Լ���x�᷽��ľ���
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
				  //����
		  enemyBalls[i].x=20;
		  enemyBalls[i].y=500-20;

		  //��ɫ
		  enemyBalls[i].color=colors[rand()%7];//��������ӹ̶��б���
		  //��С
		  enemyBalls[i].radius=rand()%50+1;
	      //����
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

//��ײ��� 


int main()
{
	initGame();

	//����һ���߳�
	//CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)thread2,NULL,NULL,NULL);
	//��������ʱ��,���ô��ڵľ��
	//          ���   ��ʱ��id ���ʱ�� ��ʱ������
	SetTimer(g_hWnd,10086,50,(TIMERPROC)move);

	//��������߳�
	CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)controlGame,NULL,NULL,NULL);

	while(IsLive)
	{
	drawGame();
	}

	settextcolor(RED);
	outtextxy(300, 150, "Game Over");// ��ָ��λ������ַ���
	while(1);
	return 0;
}