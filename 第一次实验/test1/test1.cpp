#include<graphics.h>   // 
#include<conio.h>      // 控制台输入输出
#include<stdio.h>      // 标准输入输出
#include<math.h>

int main() 
{
	char *product[]={"computer","printer","plotter","scanner","paper","hard_disk"};	
	int color[]={RED,BLUE,YELLOW,GREEN,CYAN, MAGENTA};
	int percent[]={50,20,10,5,10,5};

	double start=0,end=0;
	int x=300,y=300,r=200;
	int h=50;//图例高度
	int r_x=550,r_y=150;	//图例左上角坐标
	int l_x=600,l_y=200;
	double rate=3.6;
	char persentStr[10];	//存储百分比字符串
	double angle;
	int tx,ty;	//文字输出坐标

	initgraph(800,600);	//初始化图形窗口
	setbkcolor(WHITE);
	cleardevice();        // 清屏，使背景色生效

	for(int i=0;i<6;++i)
	{
		end=start+percent[i]*rate;
		setfillstyle(SOLID_FILL,color[i]);
		setcolor(color[i]);   //设置边框颜色
		pieslice(x,y,start,end,r);	//绘制扇形

		angle=(start+end)/2;
		tx=x+(int)100*cos(angle*3.1415926/180);		//使用弧度
		ty=y+(int)100*sin(angle*3.1415926/180);
		setcolor(BLACK);
		sprintf(persentStr,"%d%%",percent[i]);	//格式化
		outtextxy(tx,ty,persentStr);
		setcolor(color[i]);	//恢复边框颜色
		
		setfillstyle(SOLID_FILL, color[i]);
		bar(r_x,r_y,l_x,l_y);	//实心矩形
		rectangle(r_x,r_y,l_x,l_y);		//实心矩形边框
		setcolor(BLACK);
		outtextxy(l_x+20,r_y+20,product[i]);	//图例旁边的文字
		r_y+=50;
		l_y+=50;
		start=end;
	}

	setcolor(BLACK);	//输出图标标题
	outtextxy(200,550,"Product Market Share Distribution");
	
    getch();	//暂停
    closegraph();	//关闭图形系统

    return 0;
}
