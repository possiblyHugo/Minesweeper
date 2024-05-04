#pragma once
#include <cstdlib>
#include <iostream>

/*
* Possibe tile values:
* m = mine,
* [0-x] = tile,
*/

struct Tile 
{
	bool discovered = false;
	char value = '?';
};

class Game
{
public:

private:
	int sizeX = 16;
	int sizeY = 30;
	Tile grid[16][30];

	void GenerateMines(int mines) { // Recursive Function
		srand((unsigned) time(NULL));

		int randX = rand() % sizeX;
		int randY = rand() % sizeY;

		if (grid[randX][randY].value != 'm') {
			grid[randX][randY].value = 'm';
			GenerateMines(mines - 1); 
		}
		else {
			GenerateMines(mines);
		}

	}
};

