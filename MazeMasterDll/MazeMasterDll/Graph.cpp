#include "stdafx.h"
#include "Graph.h"
#include "vertex.h"


Graph::Graph()
{
}

Graph::Graph(const int** mazedata, int mazeWidth, int mazeHeight)
{
	int total = 0;

	for (int w = 0; w < mazeWidth; w++)
	{
		for (int h = 0; h < mazeHeight; h++)
		{
			if (mazedata[w][h] == 0)
			{
				total += 1;
				
			}
			//std::cout << w << ',' << h << "complete";
		}
		//std::cout << "w " << i << " complete";
	}

	// need to define the verticy array then connect verticy to verticy's.
	// was looking at this to help. may not be neccessary yet though https://www.geeksforgeeks.org/graph-and-its-representations/
}


void addEdge(int a, int b)
{
	
}

Graph::~Graph()
{
}
