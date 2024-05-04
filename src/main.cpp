#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Game.h"

int main()
{
    Game newGame;
    newGame.Init();
    std::vector<std::vector<Tile>> grid = newGame.GetGrid();

    const int height = 16;
    const int width = 30;

    sf::RenderWindow window(sf::VideoMode(660, 360), "Minesweeper"); // width x height
    std::vector<sf::RectangleShape> squares(height * width);
    std::vector<sf::Text> texts(height * width);

    const float spacingX = 22.0;
    const float spacingY = 22.0;

    float positionX = 0;
    float positionY = 0;

    // Text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font.";
        return -1;
    }


    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j].value << "\n";
            sf::RectangleShape square(sf::Vector2f(20.f, 20.f));
            square.setPosition(positionX, positionY);
          /*  square.setOutlineThickness(2.f);
            square.setOutlineColor(sf::Color::Black);*/


            //std::cout << grid[i][j].value << "\n";
            sf::Text text;
            text.setFont(font);
            text.setString(grid[i][j].value);
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(12);
            text.setPosition(positionX + 4, positionY + 3);

            if (grid[i][j].value == "m") {
                square.setFillColor(sf::Color::Red);
            }
            else {
                square.setFillColor(sf::Color::Yellow);
            }
            
            squares.push_back(square);
            texts.push_back(text);

            positionX += spacingX;
        }
        positionY += spacingY;
        positionX = 0;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (auto shape : squares) {
            window.draw(shape);
        }

        for (auto text : texts) {
            window.draw(text);
        }

        window.display();
    }

    return 0;
}