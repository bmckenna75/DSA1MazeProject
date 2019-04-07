#pragma once
#include "vertex.h"

class Graph
{
public:

	// Constructors
	Graph(const int** mazedata, int mazeWidth, int mazeHeight);
	~Graph();

	// Variables
	vertex** vMaze;		// Unique Set of Vertex used to define the graph
	vertex* staticPath;	// Unique list of Verticies that create the path

	bool isPathFound;	// Checks to see if the path has been built already.
	int xPathPos;		// Returns the xPosistion of the next place to navigate on the map
	int yPathPos;		// Returns the yPosition of the next place to navigate on the map


	// Methods
	void StaticPathFind(int startPosX, int startPosY, int endPosX, int endPosY);	// Finds the whole path once
	void StaticResetPath();	// Resets the path fewwfw
private:

	// Variables
	int mazeWidth;		// stores maze Width 
	int mazeHeight;		// stores maze Height
	int pathSize;		// determines the Size of the Path Size

	vertex* IncreaseArraySize(vertex* oldArray, int &oldArraySize);	// Helper function that increases the size of a passed in array

	int ComputeHScore(int x, int y, int targetX, int targetY);	// Computes the H Score of the compares two Vertex based on sent in values
	
};

