#pragma once
#pragma once
#include"MGraph.h"
#include<stdio.h>
using namespace std;
void initGraph(MGraph* pGraph)
{
	//初始化边的矩阵
	for (int i = 0; i < pGraph->vertexNum; ++i)
	{
		for (int j = 0; j < pGraph->vertexNum; ++j)
		{
			if (i != j)
			{
				pGraph->graphEdge[i][j] = MINFINITE;
			}
			else
			{
				pGraph->graphEdge[i][j] = 0;
			}
		}
	}
}

void createGraph(MGraph* pGraph)
{

	FILE* fp(fopen("Graph1.txt", "r"));
	fscanf(fp, "%d,%d\n", &pGraph->vertexNum, &pGraph->edgeNum);
	initGraph(pGraph);
	for (int i = 0; i < pGraph->vertexNum; ++i)
	{
		fscanf(fp, "%c,%d,%d\n", &pGraph->graphVertex[i].data, &pGraph->graphVertex[i].x, &pGraph->graphVertex[i].y);
	}
	int i, j, wight;
	for (int k = 0; k < pGraph->edgeNum; ++k)
	{
		fscanf(fp, "%d,%d,%d\n", &i, &j, &wight);
		pGraph->graphEdge[i][j] = wight;
		pGraph->graphEdge[j][i] = wight;
		printf("%d,%d,%d\n", i, j, wight);
	}
	fclose(fp);
}

void showGraph(MGraph pGraph)
{
	printf("顶点数:%d,边数：%d\n顶点名称：", pGraph.vertexNum, pGraph.edgeNum);
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		printf("%c,", pGraph.graphVertex[i]);
	}
	puts("\n邻接矩阵：");
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		for (int j = 0; j < pGraph.vertexNum; ++j)
		{
			if (pGraph.graphEdge[i][j] == MINFINITE)
			{
				printf("*  ");
			}
			else
			{
				printf("%-3d", pGraph.graphEdge[i][j]);
			}
		}
		puts("");
	}
}