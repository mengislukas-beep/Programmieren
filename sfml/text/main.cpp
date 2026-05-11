#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Ich Mache Texte!");
    sf::Font font;
    if (!font.loadFromFile("font/Inter-VariableFont_opsz,wght.ttf")) {
        std::cout << "Fehler beim Laden der Schriftart\n";
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hallo, ich heisse");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(10.f, 50.f);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);

        window.display();
    }

    return 0;
}