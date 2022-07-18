#pragma once
#include"MGraph.h"
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<iostream>
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
				pGraph->graphEdge[i][j] = 10000;
				pGraph->graphEdge[j][i] = 10000;
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
	char a[] = "Graph2.txt";
	wchar_t s[10];
	InputBox(s, 10, L"请输入想测试的用例：",L"测试用例选择",NULL,300,150,false);
	int r = _wtoi(s);//将输入的值转化为整数

	while (r > 5)
	{
		MessageBox(NULL, L"您输入的用例不合法", L"提示", MB_OK);
		InputBox(s, 10, L"请重新输入想测试的用例：", L"测试用例选择", NULL, 300, 150, false);
		r=_wtoi(s);
	}
	a[5] = char(r+'0');
	FILE* fp(fopen(a, "r"));

	fscanf(fp, "%d,%d\n", &pGraph->vertexNum, &pGraph->edgeNum);
	cout << "顶点数：" << pGraph->vertexNum << ",边数：" << pGraph->edgeNum << endl;
	
	initGraph(pGraph);
	for (int i = 0; i < pGraph->vertexNum; ++i)
	{
		fscanf(fp, "%c,%d,%d\n", &pGraph->graphVertex[i].data, &pGraph->graphVertex[i].x, &pGraph->graphVertex[i].y);
	}
	cout << "顶点名称：";
	for (int i = 0; i < pGraph->vertexNum; ++i)
	{
		printf("%c,", pGraph->graphVertex[i].data);
	}
	cout << endl;

	//提取边以及权值
	int i, j, wight;
	for (int k = 0; k < pGraph->edgeNum; ++k)
	{
		int l=fscanf(fp, "%d,%d,%d\n", &i, &j, &wight);
		pGraph->graphEdge[i][j] = wight;
		pGraph->graphEdge[j][i] = wight;
	}

	cout << "邻接矩阵：" << endl;
	for (int i = 0; i < pGraph->vertexNum; ++i)
	{
		for (int j = 0; j < pGraph->vertexNum; ++j)
		{
			if (pGraph->graphEdge[i][j] == 10000)
			{
				printf("*  ");
			}
			else
			{
				printf("%-3d", pGraph->graphEdge[i][j]);
			}
		}
		cout << endl;
	}
	fclose(fp);
}
