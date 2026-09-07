#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#define pi 3.1415926

int round(double temp)
{	
	if(temp>=0)
		return int(temp+0.5);
	else
		return int(temp-0.5);
}
void DDA_line(double x_start,double y_start,double x_end,double y_end)		//微分法画直线
{
	double x=x_start,y=y_start;
	double dx=x_end-x_start,dy=y_end-y_start;
	double steps=fabs(dx)>fabs(dy)?fabs(dx):fabs(dy);
	double xinc=dx/steps;
	double yinc=dy/steps;

	for(int i=0;i<=steps;i++)
	{
		putpixel(round(x),round(y),RED);	//点亮坐标上的一个点
		x+=xinc;
		y+=yinc;
	}
}


void DDA_circle()	//微分法画圆
{
	initgraph(600,600);
	setbkcolor(WHITE);
	cleardevice();

	double x_c=300,y_c=300;
	double r=100;
	double x_start,y_start;
	double x_end,y_end;
	int n=100;		//控制多边形的边数
	double o=360.0/n;
	double rad=o*pi/180;

	x_start=x_c+r*cos(0);
	y_start=y_c+r*sin(0);
	for(int i=1;i<=n;++i)
	{
		x_end=x_c+r*cos(i*rad);
		y_end=y_c+r*sin(i*rad);
		DDA_line(x_start,y_start,x_end,y_end);
		x_start=x_end;
		y_start=y_end;
	}

	getch();
	closegraph();
}


void pwx()
{
	initgraph(800,600);
	setbkcolor(WHITE);
	cleardevice();

	int center_x=400;
	int center_y=400;
	int x_start_x=100,x_start_y=400;
	int x_end_x=700,x_end_y=400;
	int y_start_x=400,y_start_y=500;
	int y_end_x=400,y_end_y=100;
	setcolor(BLUE);
	line(x_start_x,x_start_y,x_end_x,x_end_y);	//坐标轴
	line(y_start_x,y_start_y,y_end_x,y_end_y);
	double x,y;
	int p=20;
	for(x=-300;x<=300;x+=0.5)	//抛物线
	{
		y=(x*x)/(4*p);
		double screen_x=x+400;
		double screen_y=400-y;
		if(screen_y>=100)
			putpixel(screen_x,screen_y,BLUE);
	}

	getch();
	closegraph();
}

int main()
{
	//DDA_circle();
	pwx();
	return 0;
}
