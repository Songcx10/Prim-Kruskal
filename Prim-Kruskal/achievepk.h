#pragma once
#pragma once
//�����㷨��ʵ��
#include"MGraph.h"
#include<stdio.h>
#include<graphics.h>
#include <algorithm>
#include <conio.h>
using namespace std;
void Prim(MGraph pGraph)
{
	printf("PRIM�㷨��\n");
	int minWightSum = 0;
	//Ҫ�����㼯�Ϻ�ȡֵ���Ͻ�������������ǣ���vertexSet��j������j��Ȩֵ��СΪwightSet��j����
	int vertexSet[MAXVEX];//���㼯��
	int wightSet[MAXVEX];//Ȩֵ�ļ���
	vertexSet[0] = 0;
	wightSet[0] = 0;
	//ֱ�����ж��㱻����
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		//�ڿ�ʼʱ�����㼯����ֻ�е�0��
		vertexSet[i] = 0;
		//���壺�ӵ�0����i�ıߵ�ȨֵΪwightSet��i��
		wightSet[i] = pGraph.graphEdge[0][i];
	}
	int x1, x2, y1, y2;
	setlinecolor(WHITE);//����ѡ�е�������ɫ��Ϊ��ɫ

	//Ĭ�ϴӵ�һ�����㿪ʼ����һ�������Ѿ�����
	for (int i = 1; i < pGraph.vertexNum; ++i)
	{
		int minWight = MINFINITE;
		int k = 0;
		for (int j = 0; j < pGraph.vertexNum; ++j)
		{
			//�ڵ�ǰȡֵ������Ѱ����С��Ȩֵ��
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

		//�ڽ�������ط��������
		TCHAR s[100];
		_stprintf(s, _T("( %d, %d )--> %d"), vertexSet[k], k, pGraph.graphEdge[vertexSet[k]][k]);
		if (_getch())
		{
			settextstyle(25, 0, _T("����"));//�������ָ�ʽ
			line(x1, y1, x2, y2);
			outtextxy(300, 400, s);
			int i = _getch();
			if (i) {
				clearrectangle(400, 500, 600, 600);
			}

		}
		//���Ѿ�Ѱ�ҳ�·����Ȩֵ���Ϊ0����Ϊ֮��Ҫ����wightSet������Ȩֵ��Ҳ���Լ�Ϊ����������0�ȽϺô���
		wightSet[k] = 0;
		//�ڼ����µ����Ҫ���¶��㼯�Ϻ�Ȩֵ���ϡ�
		for (int j = 0; j < pGraph.vertexNum; ++j)
		{
			//Ѱ�Ҵ��¶��������δѰ�Ҷ����б�ԭ�����㵽δѰ�Ҷ���ȨֵС�ıߡ�
			if (k != j && wightSet[j] > pGraph.graphEdge[k][j])
			{
				//�¶���k��j��ȨֵС�ڴ�ԭ�����㵽j��Ȩֵ
				wightSet[j] = pGraph.graphEdge[k][j];
				vertexSet[j] = k;
			}
		}
	}
	TCHAR a[100];
	_stprintf(a, _T("��С��������ȨֵΪ��%d"), minWightSum);
	if (_getch())
	{
		outtextxy(300, 450, a);
	}
	//printf("��С��������ȨֵΪ��%d\n", minWightSum);
}

bool compare(EdgeWight edgeWight1, EdgeWight edgeWight2)
{
	return edgeWight1.wight < edgeWight2.wight;
}


int find(int* parent, int n)
{
	//�൱�ڽ��������ĵ�����һ�飬Ѱ�ҿ�����ӵı�
	while (parent[n] > -1)
	{
		n = parent[n];
	}
	return n;
}

EdgeWight* sortEdgeWight(MGraph pGraph)
{
	//����һ��WightEdge���͵�����,��СΪpGraph.edgeNum��
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
	// sort�������ڶ��Զ�����������ʱ��Ҫ���ߺ����������
	sort(wightEdge, wightEdge + pGraph.edgeNum, compare);
	return wightEdge;
}

//��³˹�ƶ����㷨���ѵ����ڣ����¼�һ����ʱ������ж��Ƿ��Ѿ����ɻ�·��
void Kruskal(MGraph pGraph)
{
	printf("Kruskal�㷨��");
	//���ձߵ�Ȩֵ�Ա߽�����������
	int wightCount = 0;
	EdgeWight* wightEdge = sortEdgeWight(pGraph);
	int parent[MAXVEX];//�ж�����ӵ����Ƿ��ܺ�ԭ����ͼ���ɻ�·
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		parent[i] = -1;
	}
	int n = -1, m = -1;
	//�Ա߰�Ȩֵ����󣬿���ֱ��ȡ����С�ı�
	int x1, y1, x2, y2;

	setlinecolor(GREEN); //��ɫΪ��ɫ
	for (int i = 0; i < pGraph.edgeNum; ++i)
	{
		n = find(parent, wightEdge[i].edgeBegin);
		m = find(parent, wightEdge[i].edgeEnd);
		//��n��=mʱ��˵������ӵĵ�û����ͼ���γɻ�·��
		if (n != m)
		{
			//���壺��n�͵�m��ɵ������Ѿ����롣
			//parentʵ�ʴ洢��ʱ�γɵġ��µ�����
			parent[n] = m;
			//printf("(%d,%d) -->%d\n", wightEdge[i].edgeBegin, wightEdge[i].edgeEnd, wightEdge[i].wight);
			wightCount += pGraph.graphEdge[wightEdge[i].edgeBegin][wightEdge[i].edgeEnd];


			x1 = pGraph.graphVertex[wightEdge[i].edgeBegin].x;
			y1 = pGraph.graphVertex[wightEdge[i].edgeBegin].y;
			x2 = pGraph.graphVertex[wightEdge[i].edgeEnd].x;
			y2 = pGraph.graphVertex[wightEdge[i].edgeEnd].y;

			//�ڽ�������ط��������
			TCHAR s[100];
			_stprintf(s, _T("( %d, %d )--> %d"), wightEdge[i].edgeBegin, wightEdge[i].edgeEnd, wightEdge[i].wight);
			if (_getch())
			{
				settextstyle(25, 0, _T("����"));
				outtextxy(400, 400, s);
				line(x1, y1, x2, y2);
			}
		}
	}
	TCHAR a[100];
	_stprintf(a, _T("��С��������ȨֵΪ��%d"), wightCount);
	if (_getch())
	{
		outtextxy(300, 450, a);
	}
	//printf("��С��������Ȩֵ��%d\n", wightCount);
	free(wightEdge);
}