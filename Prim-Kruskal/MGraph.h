#pragma once
#pragma once
//全部函数声明
#define MAXVEX 100
#define MINFINITE 0x7FFFFFFF
typedef int EdgeType;

typedef struct//结构体定义边
{
	int edgeBegin;
	int edgeEnd;
	int wight;
}EdgeWight;

typedef struct//结构体定义顶点（值+坐标）
{
	char data;
	int x;
	int y;
}Vertex;

typedef struct //定义无向连通图
{
	Vertex graphVertex[MAXVEX];
	EdgeType graphEdge[MAXVEX][MAXVEX];
	int vertexNum;
	int edgeNum;
}MGraph;

//初始化
void initGraph(MGraph* pGraph);
//生成图
void createGraph(MGraph* pGraph);
//展示图的邻接矩阵
void showGraph(MGraph pGraph);
//画图
void drawGraphP(MGraph pGraph);
void drawGraphK(MGraph pGraph);

//普里姆算法
void Prim(MGraph pGraph);

//克鲁斯卡尔
EdgeWight* sortEdgeWight(MGraph pGraph);
void Kruskal(MGraph pGraph);
//添加选择界面
void creatoption(MGraph pGraph);