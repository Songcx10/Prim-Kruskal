//.cppÎÄ¼þ
#pragma warning(disable : 4996)

#pragma warning(disable : 6031)
#include "MGraph.h"
#include "creatmenu.h"
#include "CreatGraph.h"
#include "achievepk.h"
#include <stdio.h>
using namespace std;


int main()
{
	MGraph graph;	createGraph(&graph);

	creatoption(graph);
	showGraph(graph);
	return 0;
}