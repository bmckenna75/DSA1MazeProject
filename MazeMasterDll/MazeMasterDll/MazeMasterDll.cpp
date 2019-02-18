// MazeMasterDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

int** maze;
int mazeWidth;
int mazeHeight;
int xpositions[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int ypositions[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int nextPosIndex = 0;
int playerXpos;
int playerYpos;

///Returns Our Names
__declspec(dllexport) char* GetTeam() 
{
	char namesToReturn[50] = "Lei McKenna and Jacob Marcovecchio";
	return namesToReturn;
}

///Sets maze based on the passed in values
__declspec(dllexport) void SetMaze(const int** data, int width, int height)
{
	mazeWidth = width;
	mazeHeight = height;

	maze[width][height] = { };

	//loops through to assign maze vars
	for (int w = 0; w < width; w++)
	{
		for (int h = 0; h < height; h++)
		{
			maze[w][h] = data[w][h];
			//std::cout << w << ',' << h << "complete";
		}
		//std::cout << "w " << i << " complete";
	}
}

///Sets xpos and ypos then ends
__declspec(dllexport) void GetNextPosition(int& xpos, int& ypos)
{
	//Goes to next point then uses modulus to determine if it needs to loop
	nextPosIndex++;
	nextPosIndex = nextPosIndex % 10;

	xpos = xpositions[nextPosIndex];
	ypos = ypositions[nextPosIndex];
}

__declspec(dllexport) int** GetMaze(int&& width, int&& height)
{
	width = mazeWidth;
	height = mazeHeight;
	return maze;
}

///Sets the starting location for the player - Saves the X and Y values
__declspec(dllexport) void SetStart(int x, int y)
{
	playerXpos = x;
	playerYpos = y;
}

///Sets the starting location for the player. Return the saved x and y start locations.
///If x and y locations have not been saved, return -1 for both
__declspec(dllexport) void GetStart(int& xPos, int& yPos)
{
	xPos = playerXpos;
	yPos = playerYpos;

	// References the global address of the players specific X & Y pos;
	if (playerXpos == NULL || playerXpos <= 0) {
		xPos = -1;
	}
	// References the global address of the players specific X & Y pos;
	if (playerYpos == NULL || playerYpos <= 0) {
		yPos = -1;
	}
}

///Sets the end location for the player - Saves the X and Y values
__declspec(dllexport) void SetEnd(int x, int y)
{
	playerXpos = x;
	playerYpos = y;
}

///Sets the ending location for the player. Return the saved x and y end locations.
///If x and y locations have not been saved, return -1 for both
__declspec(dllexport) void GetEnd(int& xPos, int& yPos)
{
	xPos = playerXpos;
	yPos = playerYpos;

	// References the global address of the players specific X & Y pos;
	if (playerXpos == NULL || playerXpos <= 0) {
		xPos = -1;
	}
	// References the global address of the players specific X & Y pos;
	if (playerYpos == NULL || playerYpos <= 0) {
		yPos = -1;
	}
}