#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    const int height = 16;
    const int width = 30;

    sf::RenderWindow window(sf::VideoMode(500, 500), "Minesweeper");
    std::vector<sf::RectangleShape> squares(height * width);

    const float spacingX = 10.0;
    const float spacingY = 10.0;

    float positionX = 0;
    float positionY = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            sf::RectangleShape square(sf::Vector2f(20.f, 20.f));
            square.setFillColor(sf::Color(100, 250, 0));
            square.setPosition(positionX, positionY);
            squares.push_back(square);
            positionX += spacingX;

            window.draw(square);
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

        window.display();
    }

    return 0;
}