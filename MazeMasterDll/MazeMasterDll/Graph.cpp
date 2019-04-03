#include "stdafx.h"
#include "Graph.h"
#include "vertex.h"


Graph::Graph()
{
}

Graph::Graph(const int** mazedata, int mazeWidth, int mazeHeight)
{
	vMaze = new vertex*[mazeWidth];

	for (int w = 0; w < mazeWidth; w++)
	{
		vMaze[w] = new vertex[mazeHeight];

		for (int h = 0; h < mazeHeight; h++)
		{
			vMaze[w][h].dataType = mazedata[w][h];
			vMaze[w][h].xPos = w;
			vMaze[w][h].yPos = h;
		}

	}

	// need to define the verticy array then connect verticy to verticy's.
	// was looking at this to help. may not be neccessary yet though https://www.geeksforgeeks.org/graph-and-its-representations/
}

int ComputeHScore()
{
	return 0;
}

Graph::~Graph()
{
}
