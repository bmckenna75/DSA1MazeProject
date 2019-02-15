// MazeMasterDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

int** maze;
int mazeWidth;
int mazeHeight;
int xpositions[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int ypositions[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int nextPosIndex = 0;

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