#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>

void Dot_text(int x0,int y0)
{
	int text[16]={0x0000,0x0000,0x0000,0x1FF8,0X0080,0x0080,0X0288,0X0490,0X0AA8,0X11C4,0X0080,0X0080,0X1FF8,0X0000,0X0000,0X0000};
	int mask[16]={0x8000,0x4000,0x2000,0x1000,0x0800,0x0400,0x0200,0x0100,0x0080,0x0040,0x0020,0x0010,0x0008,0x0004,0x0002,0x0001};
	int i,j;
	for(i=0;i<16;++i)
	{
		for(j=0;j<16;++j)
		{
			if((text[i]&mask[j])!=0)	//得加括号
			{
				putpixel(x0+j,y0+i,BLACK);
			}
		}
	}
}

void SL_text()
{
	int text[]={100,100,700,100,100,500,700,500,400,100,400,500,300,200,200,400,250,300,300,400,600,200,500,400,550,300,600,400};
	int len=sizeof(text)/sizeof(text[0]);
	int i;
	for(i=0;i<len;i+=4)
	{
		moveto(text[i],text[i+1]);
		lineto(text[i+2],text[i+3]);
	}
}

void Direct_text()
{
	int model[8][2]={{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
	int direct[7][16]={
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
		{5,5,5,5,5,5,5,-1,-1,-1,-1,-1,-1,-1,-1,-1},		//无效方向要用-1标记，避免多余绘制
		{7,7,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{5,5,5,5,5,5,5,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{7,7,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	int starts[7][2]={{100,100},{180,100},{160,130},{127,167},{260,130},{223,167},{100,260}};
	int pen_count=7;  // 笔顺总数
    int size=10;      // 步长缩放
	for(int i=0;i<pen_count;++i)
	{
		// 移动到当前笔顺的起始位置
        int start_x =starts[i][0];
        int start_y =starts[i][1];
        moveto(start_x, start_y);
		
		//绘制当前笔顺的所有方向步骤
        int step_count = sizeof(direct[i]) / sizeof(direct[i][0]);  // 每笔的步数
		for(int j=0;j<step_count;++j)
		{
			int idx = direct[i][j];		// 获取model的行索引
			if(idx >= 0 && idx < 8)		// 确保索引有效（防止越界）
			{ 
				int dx = model[idx][0] * size;		// 计算x方向增量
				int dy = model[idx][1] * size;		// 计算y方向增量
				linerel(dx, dy); 
			}
		}
	}
}

int main()
{
	initgraph(800,600);
	setbkcolor(WHITE);
	setcolor(BLACK);	//SL_text要用
	cleardevice();

	Dot_text(200,200);
	SL_text();
	Direct_text();

	getch();              
    closegraph();

	return 0;   
}
