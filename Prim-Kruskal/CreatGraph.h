#pragma once
#pragma once
#include"MGraph.h"
#include<stdio.h>
#include<string.h>
#include<graphics.h>

using namespace std;
void initGraph(MGraph* pGraph)
{

	//��ʼ���ߵľ���
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
	char a[] = "Graph2.txt";
	wchar_t s[10];
	InputBox(s, 10, L"����������Ե�������",L"��������ѡ��",NULL,300,150,false);
	int r = _wtoi(s);//�������ֵת��Ϊ����
	
	if (r > 2)
	{
		//HWND wnd = GetHWnd();
		MessageBox(NULL, L"��������������Ϸ�", L"��ʾ", MB_OK);
		InputBox(s, 10, L"��������������Ե�������", L"��������ѡ��", NULL, 300, 150, false);
		 r = _wtoi(s);//�������ֵת��Ϊ����
	}
	a[5] = char(r+'0');
	FILE* fp(fopen(a, "r"));
	//FILE* fp(fopen("Graph0.txt", "r));
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
	printf("������:%d,������%d\n�������ƣ�", pGraph.vertexNum, pGraph.edgeNum);
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		printf("%c,", pGraph.graphVertex[i].data);
	}
	puts("\n�ڽӾ���");
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