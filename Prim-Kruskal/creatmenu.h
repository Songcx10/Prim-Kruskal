#pragma once
#include"MGraph.h"
#include"achievepk.h"
#include"creatmenu.h"
#include <graphics.h>
#include<conio.h>

//������ʾ�ʼ���ֵ�ѡ�����
void creatoption(MGraph pGraph)
{
	abcd:;
	MOUSEMSG m;
	//�˵�
	initgraph(600, 600);
	setbkcolor(WHITE);
	cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)

	settextcolor(BLACK);
	settextstyle(45, 0, _T("����"));
	outtextxy(50, 150, _T("��ѡ������Ҫʹ�õ��㷨��"));

	setfillcolor(LIGHTBLUE);

	//ѡ���
	fillrectangle(200, 250, 400, 290);
	fillrectangle(200, 330, 400, 370);
	fillrectangle(200, 410, 400, 450);

	settextstyle(20, 0, _T("����"));//�������ָ�ʽ
	setbkmode(TRANSPARENT);// ȥ�����ֱ���

	outtextxy(270, 260, _T("Prim�㷨"));
	outtextxy(260, 340, _T("Kruskal�㷨"));
	outtextxy(270, 420, _T("�˳�"));

	while (1) {

		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 400 && m.y >= 250 && m.y <= 290) {
			setlinecolor(RED);
			rectangle(195, 245, 405, 295);
			//��������Prim�㷨
			if (m.uMsg == WM_LBUTTONDOWN) {//�����걻����
				drawGraphP(pGraph);
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 400 && m.y >= 330 && m.y <= 370) {
			setlinecolor(RED);
			rectangle(195, 325, 405, 375);
			//��������Kruskal�㷨
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawGraphK(pGraph);
				creatoption(pGraph);
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 400 && m.y >= 410 && m.y <= 450) {
			setlinecolor(RED);
			rectangle(195, 405, 405, 455);
			//���������˳�
			if (m.uMsg == WM_LBUTTONDOWN) {
				//closegraph();
				exit(0);
				//goto abcd;
			}
		}
		else {
			setlinecolor(WHITE);
			rectangle(195, 245, 405, 295);
			rectangle(195, 325, 405, 375);
			rectangle(195, 405, 405, 455);
		}
	}
	_getch();
	closegraph();
}

void drawGraphP(MGraph pGraph)
{
	initgraph(600, 500);
	settextcolor(WHITE); //�޸��ı�����ɫ
	int x1, y1, x2, y2;
	setlinecolor(WHITE);     //���û����Լ�ԲȦ����ɫ����ʼ�İ�ɫ
	wchar_t str[100];
	for (int i = 1; i < pGraph.vertexNum; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (pGraph.graphEdge[i][j] > 0 && pGraph.graphEdge[i][j] < MINFINITE)
			{
				x1 = pGraph.graphVertex[i].x;
				y1 = pGraph.graphVertex[i].y;
				x2 = pGraph.graphVertex[j].x;
				y2 = pGraph.graphVertex[j].y;
				line(x1, y1, x2, y2);
				swprintf(str, _T("%d"), pGraph.graphEdge[i][j]);
				outtextxy((x1 + x2 - 10) / 2, (y1 + y2 - 20) / 2, (LPCTSTR)str);
			}
		}
	}
	setfillcolor(BLACK);//Բ�ο�����ɫ
	int radio = 22;
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		fillcircle(pGraph.graphVertex[i].x, pGraph.graphVertex[i].y, radio);
		outtextxy(pGraph.graphVertex[i].x - 5, pGraph.graphVertex[i].y - 5, pGraph.graphVertex[i].data);
	}
	//settextstyle(20, 0, _T("����")); 

	Prim(pGraph);
	_getch();
	closegraph();
}

void drawGraphK(MGraph pGraph)
{
	initgraph(600, 500);
	settextcolor(WHITE); //�޸��ı�����ɫ
	int x1, y1, x2, y2;
	setlinecolor(WHITE);     //���û����Լ�ԲȦ����ɫ����ʼ�ĺ�ɫ
	wchar_t str[100];
	for (int i = 1; i < pGraph.vertexNum; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (pGraph.graphEdge[i][j] > 0 && pGraph.graphEdge[i][j] < MINFINITE)
			{
				x1 = pGraph.graphVertex[i].x;
				y1 = pGraph.graphVertex[i].y;
				x2 = pGraph.graphVertex[j].x;
				y2 = pGraph.graphVertex[j].y;
				line(x1, y1, x2, y2);
				swprintf(str, _T("%d"), pGraph.graphEdge[i][j]);
				outtextxy((x1 + x2 - 10) / 2, (y1 + y2 - 20) / 2, (LPCTSTR)str);
			}
		}
	}
	setfillcolor(BLACK);//Բ�ο�����ɫ
	int radio = 22;
	for (int i = 0; i < pGraph.vertexNum; ++i)
	{
		fillcircle(pGraph.graphVertex[i].x, pGraph.graphVertex[i].y, radio);
		outtextxy(pGraph.graphVertex[i].x - 5, pGraph.graphVertex[i].y - 5, pGraph.graphVertex[i].data);
	}

	Kruskal(pGraph);
	_getch();
	closegraph();
}
