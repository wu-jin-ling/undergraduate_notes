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

void Bresenham_line(int x0, int y0, int x1, int y1)		// Bresenham算法画直线		//Bresenham全程基于整数，区别于DDA（依赖浮点数）的核心特征
{
	int x=x0,y=y0;
    int k=(y1-y0)/(x1-x0);
	int t=2*k-1;
	int steps=x1-x0;
	int xinc=1;
	int yinc;

	for(int i=0;i<=steps;++i)
	{
		putpixel(round(x),round(y),BLUE);	
		if(t>=0)
			t+=2*k-2;
		else 
			t+=2*k;

		if(t>0)
			yinc=1;
		else
			yinc=0;
		x+=xinc;
		y+=yinc;
	}
	
}

int main()
{
		
	initgraph(800,600);
	setbkcolor(WHITE);
	cleardevice();

	DDA_line(20,20,500,500);
	Bresenham_line(20, 30, 500, 530);  

	getch();              
    closegraph();

	return 0;   
}
