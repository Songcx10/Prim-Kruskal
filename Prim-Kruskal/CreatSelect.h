#pragma once
#include"MGraph.h"
#include"CreatGraph.h"
#include"creatmenu.h"
#include <graphics.h>
#include <conio.h>
#include<random>

void Select(MGraph pgraph)
{
	abcd:;
	MOUSEMSG m;
	//�˵�
	initgraph(600, 600);
	setbkcolor(WHITE);
	cleardevice();//ˢ��һ�� �Ե����Ǹ�system(cls)

	settextcolor(BLACK);
	settextstyle(45, 0, _T("����"));
	outtextxy(70, 150, _T("��ѡ�����뷽ʽ��"));

	setfillcolor(LIGHTBLUE);

	//ѡ���
	fillrectangle(200, 250, 400, 290);
	fillrectangle(200, 330, 400, 370);
	fillrectangle(200, 410, 400, 450);

	settextstyle(20, 0, _T("����"));//�������ָ�ʽ
	setbkmode(TRANSPARENT);// ȥ�����ֱ���

	outtextxy(270, 260, _T("�������"));
	outtextxy(250, 340, _T("ѡ������ʾ��"));
	outtextxy(270, 420, _T("�˳�"));


	while (1) {
		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 400 && m.y >= 250 && m.y <= 290) {
			setlinecolor(RED);
			rectangle(195, 245, 405, 295);
			//���������������
			if (m.uMsg == WM_LBUTTONDOWN) {
				wchar_t s[10];
				InputBox(s, 10, L"�����������", L"�������", NULL, 300, 150, false);
				int r = _wtoi(s);

				while (r > 6)
				{
					//HWND wnd = GetHWnd();
					MessageBox(NULL, L"��������������Ϸ�", L"��ʾ", MB_OK);
					InputBox(s, 10, L"���������������", L"�������", NULL, 300, 150, false);
					r = _wtoi(s);
				}
				int m = r * (r - 1) / 2;
			
				InputBox(s, 10, L"�����������", L"�������", NULL, 300, 150, false);
				int j = _wtoi(s);//�������ֵת��Ϊ����
				if(j > m && j < r-1)
				{
					MessageBox(NULL, L"��������������Ϸ�", L"��ʾ", MB_OK);
					InputBox(s, 10, L"���������������", L"�������", NULL, 300, 150, false);
					j = _wtoi(s);
				}
				RandGraph(&pgraph, r, j);
				creatoption(pgraph);
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 400 && m.y >= 330 && m.y <= 370) {
			setlinecolor(RED);
			rectangle(195, 325, 405, 375);
			//��������ʹ������ʾ��
			if (m.uMsg == WM_LBUTTONDOWN) {
				createGraph(&pgraph);
				creatoption(pgraph);
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 400 && m.y >= 410 && m.y <= 450) {
			setlinecolor(RED);
			rectangle(195, 405, 405, 455);
			//���������˳�
			if (m.uMsg == WM_LBUTTONDOWN) {
				closegraph();
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

void RandGraph(MGraph* pGraph,int m,int n)//��������Ķ�����ȷ����ȡ�ļ��е�ǰ���У�ÿ�д���һ�������λ��
{
	FILE* fp(fopen("RandGraph.txt", "r"));
	pGraph->vertexNum = m;
	pGraph->edgeNum = n;
	initGraph(pGraph);
	for (int i = 0; i < m; ++i)//��ȡ�����Լ�λ��
	{
		fscanf(fp, "%c,%d,%d\n", &pGraph->graphVertex[i].data, &pGraph->graphVertex[i].x, &pGraph->graphVertex[i].y);
	}
	int i, j;	
	for (int k = n; k >=0;k-- )//���������Ȩֵ
	{
		i = rand() % m;
		j = rand() % m;

		if ((i != j) && (pGraph->graphEdge[i][j]==MINFINITE)){
			 //������ɱߣ�������Ȩֵ��[1,11)֮�������
			pGraph->graphEdge[i][j] = (int)(rand() % 10 + 1);
			pGraph->graphEdge[j][i] = pGraph->graphEdge[i][j];
		}
	}
	fclose(fp);
}