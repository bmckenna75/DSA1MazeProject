#pragma once
#include "vertex.h"

class Graph
{
public:

	// Constructors
	Graph();
	Graph(const int** mazedata, int mazeWidth, int mazeHeight);
	~Graph();

	// Variables
	vertex** vMaze;		// Unique Set of Vertex used to define the graph

	// Methods

private:
	int ComputeHScore();
	
};

