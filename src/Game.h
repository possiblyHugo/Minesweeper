#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

/*
* Possibe tile values:
* m = mine,
* [0-x] = tile,
*/

struct Tile 
{
	bool flagged = false;
	bool discovered = false;
	std::string value = "?";
};

class Game
{
public:
	sf::Font font;

	void Init() {
		srand((unsigned)time(NULL));

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

				if (DEBUG_MODE) {
					text.setString(grid[i][j].value);
					square.setFillColor(sf::Color(252, 186, 3));
				}
				else if (grid[i][j].flagged) {
					square.setFillColor(sf::Color(255, 41, 41));
					text.setString("*");
				}
				else if (grid[i][j].discovered) {

					if (grid[i][j].value == "m") {
						square.setFillColor(sf::Color(255, 0, 34));
						text.setString(grid[i][j].value);
					}
					else if (grid[i][j].value == "0") {
						square.setFillColor(sf::Color(186, 175, 52));
						text.setString("");
					}
					else {
						square.setFillColor(sf::Color(255, 239, 66));
						text.setString(grid[i][j].value);
					}
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

	void ClearBoard(std::vector<sf::RectangleShape>& squares, std::vector<sf::Text>& texts) {
		squares.clear();
		texts.clear();
	}

	// User input
	void LeftClick(sf::Vector2i coord) {

		Tile selectedTile = grid[coord.y][coord.x];

		if (!selectedTile.discovered && !selectedTile.flagged && !gameOver) {

			if (firstPlay) {
				MarkReserved(coord.x, coord.y); // Middle
				
				MarkReserved(coord.x - 1, coord.y); // Left
				MarkReserved(coord.x + 1, coord.y); // Right
				MarkReserved(coord.x, coord.y - 1); // Top
				MarkReserved(coord.x, coord.y + 1); // Bottom

				MarkReserved(coord.x - 1, coord.y - 1); // Top Left
				MarkReserved(coord.x + 1, coord.y - 1); // Top Right
				MarkReserved(coord.x - 1, coord.y + 1); // Top Left
				MarkReserved(coord.x + 1, coord.y + 1); // Top Right

				// generate board AFTER the first click
				GenerateMines();
				GenerateBoard();
				ZeroTileReveal(sf::Vector2i(coord.x, coord.y));
				firstPlay = false;
			}
			else if (selectedTile.value == "0") {
				grid[coord.y][coord.x].discovered = true;
				ZeroTileReveal(coord);
			}
			else if (selectedTile.value == "m" ) {
				grid[coord.y][coord.x].discovered = true;
				gameOver = true;
				std::cout << "Game over";
			}
			else {
				grid[coord.y][coord.x].discovered = true;
			}
		}
	}

	void RightClick(sf::Vector2i coord) {
		Tile selectedTile = grid[coord.y][coord.x];

		if (!selectedTile.discovered && !gameOver) {

			if (selectedTile.flagged) {
				grid[coord.y][coord.x].flagged = false;
			}
			else {
				grid[coord.y][coord.x].flagged = true;
			}

		}
	}

	bool IsGameOver() {
		return gameOver;
	}

	void GameOverStart(sf::RenderWindow& window) {
		gameOver = true;
		sf::Text text;
		text.setFont(font);
		text.setPosition(50, 100);
		text.setString("Game Over!");
		text.setFillColor(sf::Color::Red);
		text.setCharacterSize(100);
		text.setStyle(sf::Text::Bold);

		window.draw(text);
	}

private:
	bool DEBUG_MODE = false;
	const int sizeY = 16;
	const int sizeX = 30;
	bool gameOver = false;
	bool firstPlay = true;

	//Tile grid[16][30];
	std::vector<std::vector<Tile>> grid = InitializeGrid();

	std::vector<std::vector<Tile>> InitializeGrid() {
		Tile newTile;
		return std::vector<std::vector<Tile>>(sizeY, std::vector<Tile>(sizeX, newTile));
	}

	void GenerateMines() { // Recursive Function

		int randX;
		int randY;
		int mines = 99;

		while (mines >= 0) {
			randX = rand() % (sizeX - 1);
			randY = rand() % (sizeY - 1);

			if (grid[randY][randX].value == "m" || grid[randY][randX].value == "r") {
				continue;
			}
			else {
				grid[randY][randX].value = "m";
				mines--;
			}
		}
		
	}

	void GenerateBoard() {
		for (int i = 0; i < sizeX; i++) {
			for (int j = 0; j < sizeY; j++) {
				int mineCount = 0;

			
				if (grid[j][i].value == "m") {
					continue;
				}
				// top, bottom, left, right
				if ( CheckForMine(j - 1, i) ) { // Top
					mineCount++;
				}

				if (CheckForMine(j + 1, i)) { // Bottom
					mineCount++;
				} 
				if (CheckForMine(j, i - 1)) { // Left
					mineCount++;
				}

				if (CheckForMine(j, i + 1)) { // Right
					mineCount++;
				}

				if (CheckForMine(j - 1, i + 1)) { // Top Left
					mineCount++;
				}

				if (CheckForMine(j - 1, i - 1)) { // Top Right
					mineCount++;
				}

				if (CheckForMine(j + 1, i - 1)) { // Bottom Left
					mineCount++;
				}

				if (CheckForMine(j + 1, i + 1)) { // Bottom Right
					mineCount++;
				}
				grid[j][i].value = std::to_string(mineCount);

			}
		}
	}

	bool CheckForMine(int x, int y) {
		if ( x < 0 || x > sizeY - 1 ) { // Check for bounds
			return false;
		} 
		else if (y < 0 || y > sizeX - 1) { // For whatever reason I HAVE to split the x and y into 2 conditionals
			return false;
		}
		else if (grid[x][y].value == "m") {
			return true;
		}
		else {
			return false;
		}
	}

	void MarkReserved(int x, int y) {
		if (InBounds(x, y)) {
			grid[y][x].value = "r";
		}
	}

	bool InBounds(int x, int y) {
		return (x >= 0 && x < sizeX - 1) && (y >= 0 && y < sizeY - 1);
	}

	void ZeroTileReveal(sf::Vector2i coord) {
		std::unordered_map<std::string, bool> visited;
		std::queue<sf::Vector2i> queue;
		std::string convertedX;
		std::string convertedY;

		AddToVisited(visited, coord, true);

		queue.push(coord);

		while (!queue.empty()) {
			sf::Vector2i currentCoord = queue.front();
			AddToVisited(visited, currentCoord, true);
			queue.pop();
			convertedX = std::to_string(currentCoord.x);
			convertedY = std::to_string(currentCoord.y);

			if (grid[currentCoord.y][currentCoord.x].value == "0" || grid[currentCoord.y][currentCoord.x].value == "R") {
				grid[currentCoord.y][currentCoord.x].discovered = true;

				AddToQueue(queue, visited, currentCoord.x - 1, currentCoord.y); // Left
				AddToQueue(queue, visited, currentCoord.x + 1, currentCoord.y); // Right
				AddToQueue(queue, visited, currentCoord.x, currentCoord.y + 1); // Top
				AddToQueue(queue, visited, currentCoord.x, currentCoord.y - 1); // Bottom

				AddToQueue(queue, visited, currentCoord.x - 1, currentCoord.y + 1); // Top Left
				AddToQueue(queue, visited, currentCoord.x + 1, currentCoord.y + 1); // Top Right
				AddToQueue(queue, visited, currentCoord.x - 1, currentCoord.y - 1); // Bottom Left
				AddToQueue(queue, visited, currentCoord.x + 1, currentCoord.y - 1); // Bottom Right

			}
			else if (grid[currentCoord.y][currentCoord.x].value != "m" && !grid[currentCoord.y][currentCoord.x].flagged) {
				grid[currentCoord.y][currentCoord.x].discovered = true;
			}
		}
	}

	void AddToQueue(std::queue<sf::Vector2i>& queue, std::unordered_map<std::string, bool>& visited, int x, int y) {
		if (InBounds(x, y) && !GetVisitedValue(visited, x, y)) {
			queue.push(sf::Vector2i(x, y));
		}
	}

	void AddToVisited(std::unordered_map<std::string, bool>& visited, sf::Vector2i coord, bool toggle) {
		visited[std::to_string(coord.y) + "," + std::to_string(coord.x)] = toggle;
	}

	bool GetVisitedValue(std::unordered_map<std::string, bool>& visited, int x, int y) {
		return visited[std::to_string(y) + "," + std::to_string(x)];
	}

};

