#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <chrono>
#include "Game.h"


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
    }

    return 0;
}