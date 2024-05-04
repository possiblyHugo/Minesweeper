#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

int main()
{
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
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            sf::RectangleShape square(sf::Vector2f(20.f, 20.f));
            square.setFillColor(sf::Color(252, 186, 3));
            square.setPosition(positionX, positionY);
          /*  square.setOutlineThickness(2.f);
            square.setOutlineColor(sf::Color::Black);*/

            squares.push_back(square);

            std::string coordinates = "6";
            sf::Text text;
            text.setFont(font);
            text.setString(coordinates);
            text.setFillColor(sf::Color::Black);
            text.setCharacterSize(12);
            text.setPosition(positionX + 4, positionY + 3);
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