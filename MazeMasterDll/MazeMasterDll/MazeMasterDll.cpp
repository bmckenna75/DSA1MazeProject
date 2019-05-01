// MazeMasterDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Graph.h"
#include "vertex.h"

Graph vertexGraph;
int** maze;
int mazeWidth;
int mazeHeight;
int xpositions[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int ypositions[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int nextPosIndex = 0;
int playerXpos;
int playerYpos;
int startXpos;
int startYpos;
int endXpos;
int endYpos;

///Returns Our Names - Milestone 2 Check
extern "C" __declspec(dllexport) char* GetTeam()
{
	char* namesToReturn = (char*) "Lei McKenna and Jacob Marcovecchio";
	return namesToReturn;
}

///Sets maze based on the passed in values - Milestone 2 Incomplete
extern "C" __declspec(dllexport) bool SetMaze(const int** data, int width, int height)
{
	//Conditions of which the data does not load in correctly. 
	if (width <= 0 || height <= 0)
	{
		//std::cout << "Enter in a width and height that is greater than or equal to 1 \n";
		return false;
	}

	mazeWidth = width;
	mazeHeight = height;

	// Build int data set

	maze = new int* [mazeWidth];

	//loops through to assign maze vars
	for (int w = 0; w < mazeWidth; w++)
	{
		maze[w] = new int[mazeHeight];

		for (int h = 0; h < mazeHeight; h++)
		{
			maze[w][h] = data[w][h];
			//std::cout << w << ',' << h << "complete";
		}
		//std::cout << "w " << i << " complete";
	}

	// Builds Graph
	vertexGraph = Graph(data, width, height);

	return true;
}

///Sets xpos and ypos then ends
///Milestone 2 - Incomplete
extern "C" __declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos)
{
	// If the path from the start to the end has not been found yet...
	if (vertexGraph.isPathFound == false)
	{
		// Create the path!
		vertexGraph.StaticPathFind(startXpos, startYpos, endXpos, endYpos);
	}

	//Sets the x and y pos to the current vertex in the static path
	xpos = vertexGraph.staticPath[nextPosIndex].xPos;
	ypos = vertexGraph.staticPath[nextPosIndex].yPos;

	if (nextPosIndex == vertexGraph.pathSize)
	{
		return true;
	}

	// Increment so the next position is the next in the set path of verticies!
	nextPosIndex++;

	return false;


	// Milestone 1 Way of completing things
	
	/*------------------------
	
	//Goes to next point then uses modulus to determine if it needs to loop
	nextPosIndex++;
	nextPosIndex = nextPosIndex % 10;

	//----------------------	*/
}

///Returns information about the maze - Milestone 2 Test
extern "C" __declspec(dllexport) int** GetMaze(int& width, int& height)
{
	// Conditions of which the maze has not been set. 
	if (mazeWidth == NULL || mazeHeight == NULL)
	{
		return nullptr;
	}
	width = mazeWidth;
	height = mazeHeight;
	return maze;
}

///Sets the starting location for the player - Saves the X and Y values
///Milestone 2 Test
extern "C" __declspec(dllexport) bool SetStart(int x, int y)
{
	// False Condition 1 - mazeWidth and Height failed to be set.
	if (mazeWidth == NULL || mazeHeight == NULL)
		return false;

	// False Confition 2 - x starting value is out of bounds.
	if (x < 0 || x >= mazeWidth)
		return false;

	// False Condition 3 - y starting value is out of bounds.
	if (y < 0 || y >= mazeHeight)
		return false;

	//sets start position for later reference
	startXpos = x;
	startYpos = y;

	//sets player position
	playerXpos = x;
	playerYpos = y;

	return true;
}

///Sets the starting location for the player. Return the saved x and y start locations.
///If x and y locations have not been saved, return nothing
///Milestone 2 - Incomplete
extern "C" __declspec(dllexport) bool GetStart(int& xPos, int& yPos)
{
	// References the global address of the players specific X & Y pos;
	if (startXpos == NULL || startXpos <= 0)
		return false;

	// References the global address of the players specific X & Y pos;
	if (startYpos == NULL || startYpos <= 0)
		return false;

	// If the data is not invalid, then set the X and Y position and return true.
	xPos = startXpos;
	yPos = startYpos;
	return true;

	/*
	// References the global address of the players specific X & Y pos;
	if (playerXpos == NULL || playerXpos <= 0) {
		xPos = -1;
	}
	// References the global address of the players specific X & Y pos;
	if (playerYpos == NULL || playerYpos <= 0) {
		yPos = -1;
	}
	*/
}

///Sets the end location for the player - Saves the X and Y values
///Milestone 2 - Test
extern "C" __declspec(dllexport) bool SetEnd(int x, int y)
{
	// False Condition 1 - mazeWidth and Height failed to be set.
	if (mazeWidth == NULL || mazeHeight == NULL)
		return false;

	// False Confition 2 - x starting value is out of bounds.
	if (x < 0 || x >= mazeWidth)
		return false;

	// False Condition 3 - y starting value is out of bounds.
	if (y < 0 || y >= mazeHeight)
		return false;

	// If the false conditions do not apply, then the data being saved must be valid.
	endXpos = x;
	endYpos = y;
	return true;
}

///Sets the ending location for the player. Return the saved x and y end locations.
///If x and y locations have not been saved, return -1 for both
/// Milestone 2 - Test
extern "C" __declspec(dllexport) bool GetEnd(int& xPos, int& yPos)
{
	// References the global address of the players specific X & Y pos;
	if (endXpos == NULL || endXpos <= 0)
		return false;

	// References the global address of the players specific X & Y pos;
	if (endYpos == NULL || endYpos <= 0)
		return false;

	// If the data is not invalid, then set the X and Y position and return true.
	xPos = endXpos;
	yPos = endYpos;
	return true;
}

///Moves player back to starting position
extern "C" __declspec(dllexport) bool Restart()
{
	if ((startXpos == NULL || startXpos <= 0) || (startYpos == NULL || startYpos <= 0))
		return false;

	// Reset the 
	vertexGraph.StaticResetPath();
	nextPosIndex = 0;
	SetStart(startXpos, startYpos);
	return true;

}

///Need to implement the return function