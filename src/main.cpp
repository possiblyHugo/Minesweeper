#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <chrono>
#include "Game.h"

sf::Vector2i ConvertToGrid(sf::Vector2i screenCoord) {
    return sf::Vector2i(screenCoord.x / 22, screenCoord.y / 22); // divides by the spacing to get the current grid
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
            if (event.type == sf::Event::Closed)
                window.close();
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i gridCoord = ConvertToGrid(sf::Mouse::getPosition(window));
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i gridCoord = ConvertToGrid(sf::Mouse::getPosition(window));
        }

    }

    return 0;
}