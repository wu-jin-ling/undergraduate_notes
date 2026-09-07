#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_POINTS 20
#define MAX_EDGES 50

typedef struct 
{
    int x, y;
} Point;

// 定义边表项的结构体
typedef struct 
{
    int y_max;      // 边的最大y值
    float x;        // 当前扫描线与边交点的x坐标
    float dx;       // 边的斜率的倒数
    struct EdgeNode* next;
} EdgeNode;

// 活动边表
EdgeNode* AET = NULL;

// 边表
EdgeNode* ET[600] = { NULL };

// 多边形顶点
Point polygon[] = 
{
    {500, 500},
    {2000, 1000},
    {1500, 2000},
    {1000, 1500},
    {500, 500}   
};
int n = 5;  // 顶点数


void swap(int* a, int* b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 插入边到边表
void insertEdge(int x1, int y1, int x2, int y2) 
{

    if (y1 > y2) 
    {
        swap(&x1, &x2);
        swap(&y1, &y2);
    }

    EdgeNode* newEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
    newEdge->y_max = y2;
    newEdge->x = (float)x1;
    newEdge->dx = (float)(x2 - x1) / (float)(y2 - y1);
    newEdge->next = NULL;

    if (ET[y1] == NULL) 
    {
        ET[y1] = newEdge;
    }
    else 
    {
        EdgeNode* current = ET[y1];
        EdgeNode* prev = NULL;

        while (current != NULL && current->x < newEdge->x) 
        {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) 
        {
            newEdge->next = ET[y1];
            ET[y1] = newEdge;
        }
        else
        {
            newEdge->next = current;
            prev->next = newEdge;
        }
    }
}

// 构建边表
void buildEdgeTable() 
{
    int i;
    for (i = 0; i < 600; i++)
    {
        ET[i] = NULL;
    }

    for (i = 0; i < n - 1; i++)
    {
        insertEdge(polygon[i].x, polygon[i].y, polygon[i + 1].x, polygon[i + 1].y);
    }
}

// 插入边到活动边表
void insertAET(EdgeNode* edge)
{
    EdgeNode* newEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
    newEdge->y_max = edge->y_max;
    newEdge->x = edge->x;
    newEdge->dx = edge->dx;
    newEdge->next = NULL;

    if (AET == NULL) 
    {
        AET = newEdge;
    }
    else 
    {
        EdgeNode* current = AET;
        EdgeNode* prev = NULL;

        while (current != NULL && current->x < newEdge->x)
        {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) 
        {
            newEdge->next = AET;
            AET = newEdge;
        }
        else 
        {
            newEdge->next = current;
            prev->next = newEdge;
        }
    }
}

// 更新活动边表
void updateAET(int scanline) 
{
    EdgeNode* current = AET;
    EdgeNode* prev = NULL;

    while (current != NULL)
    {
        if (current->y_max == scanline) 
        {
            EdgeNode* toDelete = current;
            if (prev == NULL) 
            {
                AET = current->next;
                current = AET;
            }
            else 
            {
                prev->next = current->next;
                current = current->next;
            }
            free(toDelete);
        }
        else 
        {
            current->x += current->dx;
            prev = current;
            current = current->next;
        }
    }
}

// 扫描线填充算法
void scanlineFill() 
{
    int scanline;

    AET = NULL;

    for (scanline = 0; scanline < 600; scanline++) 
    {
        if (ET[scanline] != NULL) 
        {
            EdgeNode* current = ET[scanline];
            while (current != NULL)
            {
                insertAET(current);
                current = current->next;
            }
        }

        EdgeNode* current = AET;
        while (current != NULL && current->next != NULL)
        {
            int x1 = (int)current->x;
            int x2 = (int)current->next->x;

            if (x1 < x2)
            {
                for (int x = x1; x <= x2; x++) 
                {
                    putpixel(x / 4, scanline / 4, RED);  
                }
            }

            current = current->next->next;
        }

        updateAET(scanline);

        if (AET != NULL) 
        {
            int swapped;
            do
            {
                swapped = 0;
                EdgeNode* ptr1 = AET;
                while (ptr1->next != NULL)
                {
                    if (ptr1->x > ptr1->next->x)
                    {
                        // 交换数据
                        float temp_x = ptr1->x;
                        float temp_dx = ptr1->dx;
                        int temp_y_max = ptr1->y_max;

                        ptr1->x = ptr1->next->x;
                        ptr1->dx = ptr1->next->dx;
                        ptr1->y_max = ptr1->next->y_max;

                        ptr1->next->x = temp_x;
                        ptr1->next->dx = temp_dx;
                        ptr1->next->y_max = temp_y_max;

                        swapped = 1;
                    }
                    ptr1 = ptr1->next;
                }
            } while (swapped);
        }
    }
}

// 绘制多边形边界
void drawPolygon() 
{
    setcolor(WHITE);
    for (int i = 0; i < n - 1; i++) 
    {
        line(polygon[i].x / 4, polygon[i].y / 4,
            polygon[i + 1].x / 4, polygon[i + 1].y / 4);
    }
}

int main() 
{
    initgraph(800, 600);
    setbkcolor(WHITE);
    cleardevice();

    drawPolygon();

    getch();  

    buildEdgeTable();
    scanlineFill();

    getch();
    closegraph();

    return 0;
}