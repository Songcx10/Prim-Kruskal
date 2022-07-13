#pragma once
#pragma once
//ȫ����������
#define MAXVEX 100
#define MINFINITE 0x7FFFFFFF
typedef int EdgeType;

typedef struct//�ṹ�嶨���
{
	int edgeBegin;
	int edgeEnd;
	int wight;
}EdgeWight;

typedef struct//�ṹ�嶨�嶥�㣨ֵ+���꣩
{
	char data;
	int x;
	int y;
}Vertex;

typedef struct //����������ͨͼ
{
	Vertex graphVertex[MAXVEX];
	EdgeType graphEdge[MAXVEX][MAXVEX];
	int vertexNum;
	int edgeNum;
}MGraph;

//��ʼ��
void initGraph(MGraph* pGraph);
//����ͼ
void createGraph(MGraph* pGraph);
//չʾͼ���ڽӾ���
void showGraph(MGraph pGraph);
//��ͼ
void drawGraphP(MGraph pGraph);
void drawGraphK(MGraph pGraph);

//����ķ�㷨
void Prim(MGraph pGraph);

//��³˹����
EdgeWight* sortEdgeWight(MGraph pGraph);
void Kruskal(MGraph pGraph);
//���ѡ�����
void creatoption(MGraph pGraph);