#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define PI 3.1415926

// 定义三维点结构体
typedef struct 
{
    double x, y, z;
} Point3D;

// 定义立方体的8个顶点
Point3D cube[8] = 
{
    {-25,-25,-25},  
    {25,-25,-25},
    {25,25,-25},
    {-25,25,-25},
    {-25,-25,25},
    {25,-25,25},
    {25,25,25},
    {-25,25,25}
};

// 透视投影函数
void projectPoint(Point3D p3d, int* x2d, int* y2d, double d) 
{
    double z = p3d.z;
    *x2d = (int)(p3d.x * d / (d - z));
    *y2d = (int)(p3d.y * d / (d - z));
}

// 绘制立方体的边
void drawCube(Point3D vertices[8], double d, int offsetX, int offsetY) 
{
    int x2d[8], y2d[8];

    // 投影所有顶点到2D
    for (int i = 0; i < 8; i++) 
    {
        projectPoint(vertices[i], &x2d[i], &y2d[i], d);
        x2d[i] += offsetX;
        y2d[i] += offsetY;
    }

    // 绘制前面的四边形 (0-1-2-3)
    moveto(x2d[0], y2d[0]);
    lineto(x2d[1], y2d[1]);
    lineto(x2d[2], y2d[2]);
    lineto(x2d[3], y2d[3]);
    lineto(x2d[0], y2d[0]);

    // 绘制后面的四边形 (4-5-6-7)
    moveto(x2d[4], y2d[4]);
    lineto(x2d[5], y2d[5]);
    lineto(x2d[6], y2d[6]);
    lineto(x2d[7], y2d[7]);
    lineto(x2d[4], y2d[4]);

    // 连接前后两个面的边
    lineto(x2d[0], y2d[0]);
    moveto(x2d[1], y2d[1]);
    lineto(x2d[5], y2d[5]);
    moveto(x2d[2], y2d[2]);
    lineto(x2d[6], y2d[6]);
    moveto(x2d[3], y2d[3]);
    lineto(x2d[7], y2d[7]);
}

// 绕x轴旋转
void rotateX(Point3D* p, double angle) 
{
    double rad = angle * PI / 180.0;
    double y = p->y;
    double z = p->z;
    p->y = y * cos(rad) - z * sin(rad);
    p->z = y * sin(rad) + z * cos(rad);
}

// 缩放立方体
void scaleCube(Point3D* vertices, double scale) 
{
    for (int i = 0; i < 8; i++)
    {
        vertices[i].x *= scale;
        vertices[i].y *= scale;
        vertices[i].z *= scale;
    }
}

// 平移立方体
void translateCube(Point3D* vertices, double tx, double ty, double tz) 
{
    for (int i = 0; i < 8; i++)
    {
        vertices[i].x += tx;
        vertices[i].y += ty;
        vertices[i].z += tz;
    }
}

// 复制立方体顶点
void copyCube(Point3D source[8], Point3D dest[8]) 
{
    for (int i = 0; i < 8; i++) 
    {
        dest[i] = source[i];
    }
}

int main() 
{
    initgraph(800, 600);
    setbkcolor(WHITE);
    setcolor(BLACK);
    cleardevice();

    double d = 300;  // 视点距离

    // (1) 原始立方体的透视图
    setcolor(BLACK);
    drawCube(cube, d, 200, 150);

    // (2) 放大两倍后的立方体
    setcolor(RED);
    Point3D scaledCube[8];
    copyCube(cube, scaledCube);
    scaleCube(scaledCube, 2.0);
    drawCube(scaledCube, d, 500, 150);

    // (3) 绕x轴旋转60度后的立方体
    setcolor(BLUE);
    Point3D rotatedCube[8];
    copyCube(cube, rotatedCube);
    for (int i = 0; i < 8; i++) 
    {
        rotateX(&rotatedCube[i], 60.0);
    }
    drawCube(rotatedCube, d, 200, 400);

    // (4) 平移后的立方体
    setcolor(GREEN);
    Point3D translatedCube[8];
    copyCube(cube, translatedCube);
    translateCube(translatedCube, 20.0, 20.0, 20.0);
    drawCube(translatedCube, d, 500, 400);

    // 添加说明文字
    setcolor(BLACK);

    getch();
    closegraph();

    return 0;
}