#include "stdafx.h"
#include "Graph.h"
#include "vertex.h"
#include <cmath>  

// Only Constructor needed
Graph::Graph(const int** mazedata, int mazeWidth, int mazeHeight)
{
	// Sets maze width and height
	this->mazeHeight = mazeHeight;
	this->mazeWidth = mazeWidth;

	// Sets internal value for path size, checking if path is built, and x/y pos
	pathSize = 15;
	isPathFound = false;
	xPathPos = 0;
	yPathPos = 0;

	// Builds the map in the form of vertex

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

//Builds a path 

void Graph::StaticPathFind(int startPosX, int startPosY, int endPosX, int endPosY)
{

}

void Graph::StaticResetPath()
{
	// Resets isPathFound to false
	pathSize = 15;
	xPathPos = 0;
	yPathPos = 0;
	isPathFound = false;

	// Resets static path
	delete[] staticPath;
	staticPath = new vertex[pathSize];
}

int Graph::ComputeHScore(int x, int y, int targetX, int targetY)
{
	return abs(targetX - x) + abs(targetY - y);
}


// Function that takes in an array and the size of the known array, doubles the size & creates a newly sized array
vertex* Graph::IncreaseArraySize(vertex* oldArray, int &oldArraySize)
{
	// Creates a temparary array
	vertex* tempArray = new vertex[(oldArraySize*2)];

	for (int i = 0; i < oldArraySize; i++)
	{
		// Copies Data Over
		tempArray[i] = oldArray[i];
	}

	// Deletes the array currently stored to prevent memory leaks
	delete[] oldArray;

	// Sets the past in array as the newly created temp array
	oldArray = tempArray;

	// doubles the size of the array
	oldArraySize = oldArraySize * 2;

	// returns the array
	return oldArray;
}

Graph::~Graph()
{
}
