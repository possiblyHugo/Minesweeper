#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

/*
* Possibe tile values:
* m = mine,
* [0-x] = tile,
*/

struct Tile 
{
	bool discovered = false;
	std::string value = "?";
};

class Game
{
public:
	void Init() {
		srand((unsigned)time(NULL));
		GenerateMines();
		GenerateBoard();
	}

	std::vector<std::vector<Tile>> GetGrid() {
		return grid;
	}
private:
	int sizeX = 16;
	int sizeY = 30;
	//Tile grid[16][30];
	std::vector<std::vector<Tile>> grid = InitializeGrid();

	std::vector<std::vector<Tile>> InitializeGrid() {
		Tile newTile;
		return std::vector<std::vector<Tile>>(sizeX, std::vector<Tile>(sizeY, newTile));
	}

	void GenerateMines() { // Recursive Function

		int randX;
		int randY;
		int mines = 99;

		while (mines >= 0) {
			randX = rand() % (sizeX - 1);
			randY = rand() % (sizeY - 1);

			if (grid[randX][randY].value == "m") {
				continue;
			}
			else {
				grid[randX][randY].value = "m";
				mines--;
			}
		}
		
	}

	void GenerateBoard() {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				int mineCount = 0;

				if (grid[i][j].value == "m") {
					continue;
				}

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
				grid[i][j].value = std::to_string(mineCount);
			}
		}
	}

	bool CheckForMine(int x, int y) {
		if ((x < 0 || x > sizeX - 1) || (y < 0 || y > sizeY - 1)) { // Check for bounds
			return false;
		}
		else if (grid[x][y].value == "m") {
			return true;
		}
		else {
			return false;
		}
	}


};

