#pragma once
#pragma once
//两种算法的实现
#include"MGraph.h"
#include<stdio.h>
#include<graphics.h>
#include <algorithm>
#include <conio.h>
using namespace std;
void Prim(MGraph pGraph)
{
	printf("PRIM算法：\n");
	int minWightSum = 0;
	//要将顶点集合和取值集合结合起来，含义是：点vertexSet【j】到点j的权值大小为wightSet【j】。
	int vertexSet[MAXVEX];//顶点集合
	int wightSet[MAXVEX];//权值的集合
	vertexSet[0] = 0;
	wightSet[0] = 0;
	//直到所有顶点被访问
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		//在开始时，顶点集合中只有点0。
		vertexSet[i] = 0;
		//含义：从点0到点i的边的权值为wightSet【i】
		wightSet[i] = pGraph.graphEdge[0][i];
	}
	int x1, x2, y1, y2;
	setlinecolor(WHITE);//将被选中的线条颜色变为白色

	//默认从第一个顶点开始，第一个顶点已经加入
	for (int i = 1; i < pGraph.vertexNum; ++i)
	{
		int minWight = MINFINITE;
		int k = 0;
		for (int j = 0; j < pGraph.vertexNum; ++j)
		{
			//在当前取值集合中寻找最小的权值。
			if (wightSet[j] != 0 && wightSet[j] < minWight)
			{
				minWight = wightSet[j];
				k = j;
			}
		}
		//printf("(%d,%d)-->%d\n", vertexSet[k], k, pGraph.graphEdge[vertexSet[k]][k]);
		minWightSum += pGraph.graphEdge[vertexSet[k]][k];

		x1 = pGraph.graphVertex[vertexSet[k]].x;
		y1 = pGraph.graphVertex[vertexSet[k]].y;
		x2 = pGraph.graphVertex[k].x;
		y2 = pGraph.graphVertex[k].y;

		//在界面其余地方输出过程
		TCHAR s[100];
		_stprintf(s, _T("( %d, %d )--> %d"), vertexSet[k], k, pGraph.graphEdge[vertexSet[k]][k]);
		if (_getch())
		{
			settextstyle(25, 0, _T("楷体"));//设置文字格式
			line(x1, y1, x2, y2);
			outtextxy(300, 400, s);
			int i = _getch();
			if (i) {
				clearrectangle(400, 500, 600, 600);
			}

		}
		//将已经寻找出路径的权值标记为0。因为之后还要更新wightSet的内容权值。也可以记为其他，不过0比较好处理。
		wightSet[k] = 0;
		//在加入新点后，需要更新顶点集合和权值集合。
		for (int j = 0; j < pGraph.vertexNum; ++j)
		{
			//寻找从新顶点出发到未寻找顶点中比原来顶点到未寻找顶点权值小的边。
			if (k != j && wightSet[j] > pGraph.graphEdge[k][j])
			{
				//新顶点k到j的权值小于从原来顶点到j的权值
				wightSet[j] = pGraph.graphEdge[k][j];
				vertexSet[j] = k;
			}
		}
	}
	TCHAR a[100];
	_stprintf(a, _T("最小生成树的权值为：%d"), minWightSum);
	if (_getch())
	{
		outtextxy(300, 450, a);
	}
	//printf("最小生成树的权值为：%d\n", minWightSum);
}

bool compare(EdgeWight edgeWight1, EdgeWight edgeWight2)
{
	return edgeWight1.wight < edgeWight2.wight;
}


int find(int* parent, int n)
{
	//相当于将存在这点的岛走了一遍，寻找可以添加的边
	while (parent[n] > -1)
	{
		n = parent[n];
	}
	return n;
}

EdgeWight* sortEdgeWight(MGraph pGraph)
{
	//申请一个WightEdge类型的数组,大小为pGraph.edgeNum。
	//EdgeWight* wightEdge = (EdgeWight*)malloc(sizeof(EdgeWight) * (pGraph.edgeNum));
	EdgeWight* wightEdge = (EdgeWight*)malloc(1000);
	int k = 0;
	for (int i = 1; i < pGraph.vertexNum; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (pGraph.graphEdge[i][j] != MINFINITE)
			{
				wightEdge[k].edgeBegin = i;
				wightEdge[k].edgeEnd = j;
				wightEdge[k].wight = pGraph.graphEdge[i][j];
				++k;
			}
		}
	}
	// sort函数，在对自定义类型排序时需要告诉函数如何排序。
	sort(wightEdge, wightEdge + pGraph.edgeNum, compare);
	return wightEdge;
}

//克鲁斯科尔的算法的难点在于：当新加一条边时，如何判断是否已经构成回路。
void Kruskal(MGraph pGraph)
{
	printf("Kruskal算法：");
	//按照边的权值对边进行升序排序。
	int wightCount = 0;
	EdgeWight* wightEdge = sortEdgeWight(pGraph);
	int parent[MAXVEX];//判断新添加的线是否能和原来的图构成回路
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		parent[i] = -1;
	}
	int n = -1, m = -1;
	//对边按权值排序后，可以直接取出最小的边
	int x1, y1, x2, y2;

	setlinecolor(GREEN); //颜色为绿色
	for (int i = 0; i < pGraph.edgeNum; ++i)
	{
		n = find(parent, wightEdge[i].edgeBegin);
		m = find(parent, wightEdge[i].edgeEnd);
		//当n！=m时，说明新添加的点没有在图中形成回路。
		if (n != m)
		{
			//含义：点n和点m组成的连线已经加入。
			//parent实际存储的时形成的“孤岛”。
			parent[n] = m;
			//printf("(%d,%d) -->%d\n", wightEdge[i].edgeBegin, wightEdge[i].edgeEnd, wightEdge[i].wight);
			wightCount += pGraph.graphEdge[wightEdge[i].edgeBegin][wightEdge[i].edgeEnd];


			x1 = pGraph.graphVertex[wightEdge[i].edgeBegin].x;
			y1 = pGraph.graphVertex[wightEdge[i].edgeBegin].y;
			x2 = pGraph.graphVertex[wightEdge[i].edgeEnd].x;
			y2 = pGraph.graphVertex[wightEdge[i].edgeEnd].y;

			//在界面其余地方输出过程
			TCHAR s[100];
			_stprintf(s, _T("( %d, %d )--> %d"), wightEdge[i].edgeBegin, wightEdge[i].edgeEnd, wightEdge[i].wight);
			if (_getch())
			{
				settextstyle(25, 0, _T("楷体"));
				outtextxy(400, 400, s);
				line(x1, y1, x2, y2);
			}
		}
	}
	TCHAR a[100];
	_stprintf(a, _T("最小生成树的权值为：%d"), wightCount);
	if (_getch())
	{
		outtextxy(300, 450, a);
	}
	//printf("最小生成树的权值：%d\n", wightCount);
	free(wightEdge);
}