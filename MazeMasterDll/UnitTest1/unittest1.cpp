#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//methods 
__declspec(dllimport) char* GetTeam();
__declspec(dllimport) void SetMaze(const int** data, int width, int height);
__declspec(dllimport) void GetNextPosition(int& xpos, int& ypos);
__declspec(dllimport) int** GetMaze(int&& width, int&& height);
__declspec(dllimport) void SetStart(int x, int y);
__declspec(dllimport) void GetStart(int& xPos, int& yPos);
__declspec(dllimport) void SetEnd(int x, int y);
__declspec(dllimport) void GetEnd(int& xPos, int& yPos);
const int** finalMaze;


namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestGetTeam)
		{
			char* names = GetTeam();
			char* namesCorrect = "Lei McKenna and Jacob Marcovecchio";
			Assert::IsTrue(strcmp(names, namesCorrect) == 0);
		}
		TEST_METHOD(TestSetMaze)
		{
			int maze[5][5];
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					maze[i][j] = 0;
				}
			}
			finalMaze = (const int**) maze;

			SetMaze(finalMaze, 5, 5);
		}
		TEST_METHOD(TestGetMaze)
		{
			int** mazeReturn = GetMaze(5, 5);
			bool changeValue = true;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (finalMaze[i][j] != mazeReturn[i][j]) 
					{
						changeValue = false;
					}
				}
			}

			Assert::IsTrue(changeValue);
		}
		TEST_METHOD(TestGetNextPosition)
		{
			int xpos = 5;
			int ypos = 5;
			GetNextPosition(xpos, ypos);

			Assert::AreEqual(xpos, 1);
		}
		TEST_METHOD(TestSetStart)
		{
			int xpos = 1;
			int ypos = 1;
			SetStart(xpos, ypos);
		}
		TEST_METHOD(TestGetStart)
		{
			int xPos = 2;
			int yPos = 2;
			int& xPoint = xPos;
			int& yPoint = yPos;
			bool changeValue = true;

			GetStart(xPoint, yPoint);

			if (xPoint != 1 || yPoint != 1) 
			{
				changeValue = false;
			}

			Assert::IsTrue(changeValue);
		}
		TEST_METHOD(TestSetEnd)
		{
			int xpos = 3;
			int ypos = 3;
			SetEnd(xpos, ypos);
		}
		TEST_METHOD(TestGetEnd)
		{
			int xPos = 2;
			int yPos = 2;
			int& xPoint = xPos;
			int& yPoint = yPos;
			bool changeValue = true;

			GetEnd(xPoint, yPoint);

			if (xPoint != 3 || yPoint != 3)
			{
				changeValue = false;
			}

			Assert::IsTrue(changeValue);
		}

	};
}