#pragma once
class vertex
{
public:
	vertex();
	~vertex();
	int yPos;				// Y
	int xPos;				// X
	int dataType;			// Date Type of Vertex -- Use as the weight of the value
	int f_Priority;			// Score / Priority Level
	int g_Movement;			// Start to Current Location
	int h_Estimate;			// Estimated Value
	vertex* parentVertex;	// Parent Vertext this came from
};

