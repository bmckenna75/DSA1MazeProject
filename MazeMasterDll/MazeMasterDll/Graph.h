#pragma once
#include "vertex.h"
#include <list> 
#include <vector>

class Graph
{
public:

	// Constructors
	Graph();
	Graph(const int** mazedata, int mazeWidth, int mazeHeight);
	~Graph();

	// Variables
	vertex** vMaze;		// Unique Set of Vertex used to define the graph
	vertex* staticPath;	// Unique list of Verticies that create the path - outdated


	bool isPathFound;	// Checks to see if the path has been built already.
	int xPathPos;		// Returns the xPosistion of the next place to navigate on the map
	int yPathPos;		// Returns the yPosition of the next place to navigate on the map


	// Methods
	void StaticPathFind(int startPosX, int startPosY, int endPosX, int endPosY);	// Finds the whole path once
	void StaticResetPath();	// Resets the path fewwfw
	int pathSize;		// Keeps track of the Size of the Path Size
private:

	// Variables
	int mazeWidth;		// stores maze Width 
	int mazeHeight;		// stores maze Height

	int AllocateMemory(int length);									// Allocates Memory for the Static Stack - Returns Int of new size
	std::vector<vertex>AdjacentWalkableSquares(int x, int y);		// Get's Adjacent Squars
	int FScorePosition(std::vector<vertex> thisList);				// Get's the position of the lowest fValue in the list
	bool NotInList(std::vector<vertex> thisList, vertex thisVertex);

	int ComputeHScore(int x, int y, int targetX, int targetY, int terrainValue);	// Computes the H Score of the compares two Vertex based on sent in values
	
};

