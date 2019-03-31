#pragma once
class vertex
{
public:
	vertex(int xPosition, int yPosition);
	~vertex();
	int xPos;
	int yPos;
	int heuristic;
	int lowestCost;
	bool visited;
};

