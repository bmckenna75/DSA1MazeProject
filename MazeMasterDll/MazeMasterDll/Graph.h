#pragma once
#include "vertex.h"

class Graph
{
public:
	Graph();
	Graph(const int** mazedata, int mazeWidth, int mazeHeight);
	~Graph();

	void addEdge(int a, int b);

	vertex* adjList;



};

