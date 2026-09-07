#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#define PI 3.1415926
#define x0 300
#define y0 300

typedef struct		//定义了一个结构体类型
{
	double x,y;
}Point;

typedef double matrix[3][3];	//定义了一个矩阵类型

void init(matrix m)		//初始化变换矩阵为单位矩阵
{
	for(int i=0;i<3;++i)
	{
		for(int j=0;j<3;++j)
		{
			if(i==j)
				m[i][j]=1.0;
			else
				m[i][j]=0.0;
		}
	}
}

void creat_xz(matrix m,double angle)		//旋转变换
{
	double rad=angle*PI/180.0;
	init(m);
	m[0][0]=cos(rad);
	m[0][1]=sin(rad);
	m[1][0]=-sin(rad);
	m[1][1]=cos(rad);
}

void creat_py(matrix m,double tx,double ty)		//平移变换
{
	init(m);
	m[2][0]=tx;
	m[2][1]=ty;
}

void creat_sf(matrix m,double sx,double sy)		//缩放变换
{
	init(m);
	m[0][0]=sx;
	m[1][1]=sy;
}

void creat_cq(matrix m,double angle)	//错切变换，沿x方向
{
	double rad=angle*PI/180.0;
	init(m);
	m[1][0]=tan(rad);
}

void draw_xy()		//画坐标轴
{
	setcolor(GREEN);
	line(x0,600,x0,0);
	line(0,y0,800,y0);
	
	 // 绘制坐标轴标记
    outtextxy(x0+5, y0+5, "O");		//在指定位置输出字符串
    outtextxy(700, y0+5, "X");
    outtextxy(x0+5,50, "Y");
}

void draw_W(Point points[])
{
	setcolor(RED);
	for(int i=0;i<4;i++)
	{
		line(points[i].x,points[i].y,points[i+1].x,points[i+1].y);
	}
}

void matrixMultiply(matrix a,matrix b,matrix result)		//矩阵乘法，组合变换时使用
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			result[i][j]=0;
			for(int k=0;k<3;++k)
			{
				result[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}

void copyPoints(Point o[],Point c[])	//拷贝坐标点
{
	for(int i=0;i<5;++i)
	{
		c[i]=o[i];
	}
}

void transformPoints(Point points[],matrix m)		//应用变换，坐标点和变换矩阵相乘
{
	for(int i=0;i<5;++i)
	{
		double x=points[i].x;
		double y=points[i].y;
		
		//转换为相对于坐标原点的数学坐标
		double math_x=x-x0;
		double math_y=y0-y;		//屏幕坐标y轴向下

		//应用变换
		double new_x=math_x*m[0][0]+math_y*m[1][0]+m[2][0];
		double new_y=math_x*m[0][1]+math_y*m[1][1]+m[2][1];

		//转换为屏幕左边
		points[i].x=new_x+x0;
		points[i].y=y0-new_y;
	}
}

void rotateAroundPoint(Point points[],double angle,double px,double py)
{
	matrix T1,R,T2,temp,result;

	//第一步：平移到原点
	creat_py(T1,-px,-py);

	//第二步：旋转
	creat_xz(R,angle);

	//第三步：平移回原位置
	creat_py(T2,px,py);

	//组合变换
	matrixMultiply(R,T1,temp);
	matrixMultiply(T2,temp,result);

	//应用变换
	transformPoints(points,result);
}

int main()
{
	initgraph(800,600);
	setbkcolor(WHITE);
	cleardevice();
	
	Point originalW[]={{300,200},{350,300},{400,200},{450,300},{500,200}};
	
	Point currentW[5];		//用于拷贝初始W坐标
	
	//绘制初始图形
	draw_xy();
	draw_W(originalW);
	
	//绕原点逆时针旋转75度
	matrix m1;
    creat_xz(m1, 75);
	copyPoints(originalW, currentW);	//拷贝W
	transformPoints(currentW,m1);
	draw_W(currentW);
	
	//将原图形平移（x方向52，y方向60）
	matrix m2;
    creat_py(m2,52,60);
	copyPoints(originalW, currentW);
	transformPoints(currentW, m2);
	draw_W(currentW);

	//将原图放大为2倍
	matrix m3;
    creat_sf(m3,2.0,2.0);
	copyPoints(originalW, currentW);
	transformPoints(currentW, m3);
	draw_W(currentW);

	//将原图缩小为0.5
	matrix m4;
    creat_sf(m4,0.5,0.5);
	copyPoints(originalW, currentW);
	transformPoints(currentW, m4);
	draw_W(currentW);

	//将原图形沿着X方向错切15度
	matrix m5;
    creat_cq(m5,25);
	copyPoints(originalW, currentW);
	transformPoints(currentW, m5);
	draw_W(currentW);

	//实现关于任意一点例如（10，15）点旋转90度
	copyPoints(originalW, currentW);
	rotateAroundPoint(currentW, 90, 10, 15);
	draw_W(currentW);

	getch();              
    closegraph();

	return 0;   
}