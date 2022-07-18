#pragma once
#include"MGraph.h"
#include"CreatGraph.h"
#include"creatmenu.h"
#include <graphics.h>
#include <conio.h>
#include<random>
#include<time.h>

void Select(MGraph pgraph)
{
	abcd:;
	MOUSEMSG m;
	//菜单
	initgraph(600, 600);
	setbkcolor(WHITE);
	cleardevice();//刷新一次 略等于那个system(cls)

	settextcolor(BLACK);
	settextstyle(45, 0, _T("楷体"));
	outtextxy(100, 150, _T("请选择输入方式："));

	setfillcolor(LIGHTBLUE);

	//选择框
	fillrectangle(200, 250, 400, 290);
	fillrectangle(200, 330, 400, 370);
	fillrectangle(200, 410, 400, 450);

	settextstyle(20, 0, _T("楷体"));//设置文字格式
	setbkmode(TRANSPARENT);// 去掉文字背景

	outtextxy(270, 260, _T("随机输入"));
	outtextxy(250, 340, _T("选择现有示例"));
	outtextxy(270, 420, _T("退出"));


	while (1) {
		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 400 && m.y >= 250 && m.y <= 290) {
			setlinecolor(RED);
			rectangle(195, 245, 405, 295);
			//如果点击了随机输入
			if (m.uMsg == WM_LBUTTONDOWN) {
				//自定义输入点数
				wchar_t s[10];
				InputBox(s, 10, L"请输入点数：", L"随机定义", NULL, 300, 150, false);

				int r = _wtoi(s);
				while (r > 8)
				{
					MessageBox(NULL, L"您输入的用例不合法", L"提示", MB_OK);
					InputBox(s, 10, L"请重新输入点数：", L"随机定义", NULL, 300, 150, false);
					r = _wtoi(s);
				}
				int m = r * (r - 1) / 2;

				//自定义输入边数
				wchar_t s1[5];
				InputBox(s1, 5, L"请输入边数：", L"随机定义", NULL, 300, 150, false);
				int j = _wtoi(s1);//将输入的值转化为整数
				while (j > m || j < r - 1)
				{
					MessageBox(NULL, L"您输入的用例不合法", L"提示", MB_OK);
					InputBox(s1, 5, L"请重新输入边数：", L"随机定义", NULL, 300, 150, false);
					j = _wtoi(s1);
				}
				RandGraph(&pgraph, r, j);
				creatoption(pgraph);
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 400 && m.y >= 330 && m.y <= 370) {
			setlinecolor(RED);
			rectangle(195, 325, 405, 375);
			//如果点击了使用现有示例
			if (m.uMsg == WM_LBUTTONDOWN) {
				createGraph(&pgraph);
				creatoption(pgraph);
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 400 && m.y >= 410 && m.y <= 450) {
			setlinecolor(RED);
			rectangle(195, 405, 405, 455);
			//如果点击了退出
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

void RandGraph(MGraph* pGraph, int m, int n)//根据输入的顶点数确定提取文件中的前几行，每行代表一个顶点的位置
{
	FILE* fp(fopen("RandGraph.txt", "r"));
	pGraph->vertexNum = m;
	pGraph->edgeNum = n;
	cout << "顶点数:" << m << ",边数:" << n << endl;
	srand((unsigned)time(NULL));
	initGraph(pGraph);
	for (int i = 0; i < m; ++i)//提取顶点以及位置
	{
		fscanf(fp, "%c,%d,%d\n", &pGraph->graphVertex[i].data, &pGraph->graphVertex[i].x, &pGraph->graphVertex[i].y);
	}
	for (int a = 0; a < m - 1; a++)
	{
		if (pGraph->graphEdge[a][a + 1] == 10000) {
			pGraph->graphEdge[a][a + 1] = rand() % 28 + 1;
			pGraph->graphEdge[a + 1][a] = pGraph->graphEdge[a][a + 1];
		}
	}//此时就会有m-1条边，还差n-m+1条
	int c, v;
	for (int k = 0; k < n - m + 1; )//随机创建边权值
	{
		c = rand() % m;
		v = rand() % m;
		if ((c != v) && (pGraph->graphEdge[c][v] == 10000) && (c != v + 1) && (c != v - 1))
		{
			//随机生成边，即生成权值（[1,28)之间的数）
			pGraph->graphEdge[c][v] = rand() % 28 + 1;
			pGraph->graphEdge[v][c] = pGraph->graphEdge[c][v];
			k++;
		}
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