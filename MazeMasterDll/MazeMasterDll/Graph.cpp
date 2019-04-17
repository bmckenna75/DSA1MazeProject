#include "stdafx.h"
#include "Graph.h"
#include "vertex.h"
#include <cmath>  
#include <vector>
#include <algorithm>

// Defualt Constructor
Graph::Graph()
{

}

// Constructor
Graph::Graph(const int** mazedata, int mazeWidth, int mazeHeight)
{
	// Sets maze width and height
	this->mazeHeight = mazeHeight;
	this->mazeWidth = mazeWidth;

	// Sets internal value for path size, checking if path is built, and x/y pos
	isPathFound = false;
	pathSize = 0;
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

//Builds a static path which the main DLL will only need to increment index to navigate and gather infromation from
void Graph::StaticPathFind(int startPosX, int startPosY, int endPosX, int endPosY)
{
	using namespace std;

	// Pointer to the current vertex being checked
	vertex current;

	// Set the start position and target position
	vertex start(startPosX, startPosY);
	vertex target(endPosX, endPosY);

	// Create the open vectors and closed list vectors
	vector<vertex> openList;
	vector<vertex> closeList;

	// Create the g value;
	int g = 0;

	// Start by adding the orginal 
	openList.push_back(start);

	while (openList.size() > 0)
	{

		//Get the vertex with the lowest F score
		int lowestFScorePlace = FScorePosition(openList);
		current = openList.at(lowestFScorePlace);

		// Add the current vertex to the closed list - infering it's now been checked
		closeList.push_back(current);

		// Remove it from the open vertex
		openList.erase(openList.begin() + lowestFScorePlace -1);

		// Check to see if the item is the destination
		if (closeList.back().xPos == target.xPos && closeList.back().yPos == target.yPos)
			break;

		// Gets the location of any adjSquares to the path
		vector<vertex> adjSqaures = AdjacentWalkableSquares(current.xPos, current.yPos);
		g++;

		for (int i = 0; i < adjSqaures.size(); i++)
		{
			// If the object is already in the closed list, ignore it.
			if (NotInList(closeList, adjSqaures.at(i)) == false)
				continue;

			// If the vertex is not in the open list
			if (NotInList(openList, adjSqaures.at(i)) == true)
			{
				// Set all it's values
				adjSqaures.at(i).g_Movement = g;
				adjSqaures.at(i).h_Estimate = ComputeHScore(adjSqaures.at(i).xPos, adjSqaures.at(i).yPos, target.xPos, target.yPos);
				adjSqaures.at(i).f_Priority = adjSqaures.at(i).g_Movement + adjSqaures.at(i).h_Estimate;
				adjSqaures.at(i).parentVertex = &current;

				// and add it to the beginning of the open list
				openList.insert(openList.begin(), adjSqaures.at(i));
			}
			else
			{
				// test if using the current G score makes the adjacent square's F score
				// lower, if yes update the parent because it means it's a better path
				if (g + adjSqaures.at(i).h_Estimate < adjSqaures.at(i).f_Priority)
				{
					adjSqaures.at(i).g_Movement = g;
					adjSqaures.at(i).f_Priority = adjSqaures.at(i).g_Movement + adjSqaures.at(i).h_Estimate;
					adjSqaures.at(i).parentVertex = &current;
				}
			}

		}
	}

	// Deletes whatever the previous static path was holding
	delete[] staticPath;
	// Creates a new Static Path That will be filled with the locations of where the objects needs to navigate
	staticPath = new vertex[closeList.size()];

	// Fills the path based on the vector being used & increments the path size to tell the DLL when no more data needs to be recieved.
	for (int i = 0; i < closeList.size(); i++)
	{
		staticPath[i].xPos = closeList.at(i).xPos;
		staticPath[i].yPos = closeList.at(i).yPos;
		pathSize++;
	}

	// Adjusts the path size to function from an array
	pathSize = pathSize - 1;
}

// Resets all neccessary Values
void Graph::StaticResetPath()
{
	// Reset Values as needed
	xPathPos = 0;
	yPathPos = 0;
	pathSize = 0;
	isPathFound = false;
	
	/*
	// Resets static path
	delete[] staticPath;
	staticPath = new vertex[pathSize];
	*/
}

// Helper Function for the A* Calculation that calculates the H score
int Graph::ComputeHScore(int x, int y, int targetX, int targetY)
{
	return abs(targetX - x) + abs(targetY - y);
}

// Returns true if the point is not in the Vector / Returns False if it is already in 
bool Graph::NotInList(std::vector<vertex> thisList, vertex thisVertex)
{
	using namespace std;

	for (int i = 0; i < thisList.size(); i++)
	{
		if(thisList.at(i).xPos == thisVertex.xPos && 
			thisList.at(i).yPos == thisVertex.yPos)
			return false;
	}

	return true;
}

// Returns the position of the vertex with the lowest F Score in the vector
int Graph::FScorePosition(std::vector<vertex> thisList)
{
	using namespace std;

	// Set's Dummy Values as the maximum in a min and a negative position
	int fScoreMin = INT_MAX;
	int position = -1;

	// Loops through and keeps track of where the lowest value is 
	for (int i = 0; i < thisList.size(); i++)
	{
		if (position = -1)
		{
			fScoreMin = thisList.at(i).f_Priority;
			position = 0;
		}
		else
		{
			if (thisList.at(i).f_Priority <= fScoreMin)
			{
				fScoreMin = thisList.at(i).f_Priority;
				position = i;
			}
		}
	}

	// Returns where the lowest value is
	return position;
}

// Gets the adjacent Walkable Squares which should have it's next values checked. 
// Checks if positionns and datatype are both valid.
std::vector<vertex> Graph::AdjacentWalkableSquares(int x, int y)
{
	using namespace std;
		vector<vertex> adj;
	// If the next value is valid
	if (y - 1 >= 0)
	{ 
		// If the value is not a wall
		if (vMaze[x][y - 1].dataType != 0)
		{
			adj.push_back(vMaze[x][y - 1]);
		}
	}

	// If the next value is valid
	if (y + 1 < mazeHeight)
	{
		// If the value is not a wall
		if (vMaze[x][y + 1].dataType != 0)
		{
			adj.push_back(vMaze[x][y + 1]);
		}
	}

	// If the next value is valid
	if (x - 1 >= 0)
	{
		// If the value is not a wall
		if (vMaze[x-1][y].dataType != 0)
		{
			adj.push_back(vMaze[x-1][y]);
		}
	}

	// If the next value is valid
	if (x + 1 < mazeWidth)
	{
		// If the value is not a wall
		if (vMaze[x + 1][y].dataType != 0)
		{
			adj.push_back(vMaze[x + 1][y]);
		}
	}
	return adj;
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

// Deconstructor
Graph::~Graph()
{
	//delete[] staticPath;
}
