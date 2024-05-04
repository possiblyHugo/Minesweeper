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

	void GenerateBoard() {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				int mineCount = 0;

				// top, bottom, left, right
				if ( CheckForMine(i, j + 1) ) { // Top
					mineCount++;
				}

				if (CheckForMine(i, j - 1)) { // Bottom
					mineCount++;
				} 

				if (CheckForMine(i - 1, j)) { // Left
					mineCount++;
				}

				if (CheckForMine(i + 1, j)) { // Right
					mineCount++;
				}

				if (CheckForMine(i - 1, j + 1)) { // Top Left
					mineCount++;
				}

				if (CheckForMine(i + 1, j + 1)) { // Top Right
					mineCount++;
				}

				if (CheckForMine(i - 1, j - 1)) { // Bottom Left
					mineCount++;
				}

				if (CheckForMine(i + 1, j - 1)) { // Bottom Right
					mineCount++;
				}
				
				grid[i][j].value = char(mineCount);
			}
		}
	}

	bool CheckForMine(int x, int y) {
		if ((x < 0 || x > sizeX - 1) || (y < 0 || y > sizeY)) { // Check for bounds
			return false;
		}
		else if (grid[x][y].value == 'm') {
			return true;
		}
		else {
			return false;
		}
	}


};

