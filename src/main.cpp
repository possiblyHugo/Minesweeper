#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <chrono>
#include "Game.h"

sf::Vector2i ConvertToGrid(int x, int y) {
    return sf::Vector2i(x / 22, y / 22); // divides by the spacing to get the current grid
}

int main()
{
    const int height = 16;
    const int width = 30;
    sf::RenderWindow window(sf::VideoMode(660, 360), "Minesweeper"); // width x height

    std::vector<sf::RectangleShape> squares(height * width);
    std::vector<sf::Text> texts(height * width);
    
    Game newGame;
    newGame.Init();

    std::vector<std::vector<Tile>> grid = newGame.GetGrid();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            switch (event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i gridCoord = ConvertToGrid(event.mouseButton.x, event.mouseButton.y);
                        newGame.LeftClick(gridCoord);
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        sf::Vector2i gridCoord = ConvertToGrid(event.mouseButton.x, event.mouseButton.y);
                    }
            }
        }

        window.clear();

        newGame.DrawBoard(squares, texts);
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