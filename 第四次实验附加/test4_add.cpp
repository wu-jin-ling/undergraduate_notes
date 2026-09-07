#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>

// 模式切换宏：1=生成字模文件，0=显示汉字
#define GENERATE_FONT_FILES 0  

int text[16]={0x0000,0x0000,0x0000,0x1FF8,0X0080,0x0080,0X0288,0X0490,0X0AA8,0X11C4,0X0080,0X0080,0X1FF8,0X0000,0X0000,0X0000};

// 字模文件写入函数
void writeFontToFile(const char* filename, int font[16]) 
{
    FILE* fp = fopen(filename, "wb");  // 二进制写入，避免数据损坏
    if (fp) 
	{
        fwrite(font, sizeof(int), 16, fp);  // 写入16行点阵数据
        fclose(fp);
        printf("字模文件 %s 生成成功！请将GENERATE_FONT_FILES改为0后重新运行\n", filename);
    } 
	else 
	{
        printf("字模文件生成失败！请检查权限或路径\n");
    }
}

// 字模文件读取函数（显示时调用）
bool readFontFromFile(const char* filename, int font[16]) 
{
    FILE* fp = fopen(filename, "rb");  // 二进制读取
    if (!fp) return false;
    fread(font, sizeof(int), 16, fp);  // 读取16行点阵数据
    fclose(fp);
    return true;
}

// 点阵汉字显示函数
void Dot_text(int x0, int y0, int text[16]) {
    int mask[16] = {0x8000, 0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200, 0x0100,0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001};
    int i, j;
    for (i = 0; i < 16; ++i) 
	{
        int rowData = text[i] & 0xFFFF;  // 屏蔽32位int的高位，只保留低16位有效数据
        for (j = 0; j < 16; ++j) 
		{
            if ((rowData & mask[j]) != 0) 
			{  // 对应位为1则绘制像素
                putpixel(x0 + j, y0 + i, BLACK);
            }
        }
    }
}

int main() 
{
    //生成字模文件（仅需执行一次）
#if GENERATE_FONT_FILES
    writeFontToFile("巫.dat", text);
    return 0;  // 生成后直接退出，避免执行后续显示代码
#endif

    //显示汉字（GENERATE_FONT_FILES=0时执行）
    initgraph(800, 600);
    setbkcolor(WHITE);    
    setcolor(BLACK);     
    cleardevice();       

    // 读取字模文件
    if (!readFontFromFile("巫.dat", text)) 
	{
        printf("读取字模文件失败！请检查：\n1. 是否已生成巫.dat文件\n2. 文件是否在程序运行目录下\n");
        closegraph();
        return 1;
    }

    Dot_text(200, 200, text);

    getch();
    closegraph();
    return 0;
}