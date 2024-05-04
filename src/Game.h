#pragma once

#include <SFML/Graphics.hpp>
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
	sf::Font font;

	const float spacingX = 22.0;
	const float spacingY = 22.0;

	float positionX = 0;
	float positionY = 0;

	void Init() {
		srand((unsigned)time(NULL));
		GenerateMines();
		GenerateBoard();

		if (!font.loadFromFile("arial.ttf")) {
			std::cout << "Error loading font.";
		}

	}

	std::vector<std::vector<Tile>> GetGrid() {
		return grid;
	}

	void DrawBoard(std::vector<sf::RectangleShape>& squares, std::vector<sf::Text>& texts) {
		const float spacingX = 22.0;
		const float spacingY = 22.0;

		float positionX = 0;
		float positionY = 0;

		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[i].size(); j++) {
				sf::RectangleShape square(sf::Vector2f(20.f, 20.f));
				square.setPosition(positionX, positionY);
				/*  square.setOutlineThickness(2.f);
				  square.setOutlineColor(sf::Color::Black);*/


				sf::Text text;
				text.setFont(font);
				text.setFillColor(sf::Color::Black);
				text.setCharacterSize(12);
				text.setPosition(positionX + 4, positionY + 3);

				if (grid[i][j].value == "*") {
					square.setFillColor(sf::Color(255, 41, 41));
					text.setString(grid[i][j].value);
				}
				else if (grid[i][j].discovered) {
					square.setFillColor(sf::Color(247, 206, 92));
					text.setString(grid[i][j].value);
				}
				else {
					square.setFillColor(sf::Color(252, 186, 3));
					text.setString("");
				}

				squares.push_back(square);
				texts.push_back(text);

				positionX += spacingX;
			}
			positionY += spacingY;
			positionX = 0;
		}
	}

	// User input
	void LeftClick(sf::Vector2i coord) {
		Tile selectedTile = grid[coord.y][coord.x];

		if (!selectedTile.discovered) {
			grid[coord.y][coord.x].discovered = true;
		}

		std::cout << grid[coord.y][coord.x].discovered << "\n";
	}

	void RightClick(sf::Vector2i coord) {
		//
	}

private:
	bool DEBUG_MODE = false;
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

