#include <SFML/Graphics.hpp>
#include "complex.h"
#include "zeta_function.h"
#include "helper.h"
#include <iostream>
#include <vector>




int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Zeta Function Visualization");
    sf::Font font;
    if (!font.loadFromFile("font/Inter-VariableFont_opsz,wght.ttf")) {
        std::cout << "Fehler beim Laden der Schriftart\n";
        return -1;
    }
    sf::Text zahl;
    sf::Text wert;
    zahl.setFont(font);
    wert.setFont(font);

    zahl.setCharacterSize(15);
    zahl.setFillColor(sf::Color::White);
    wert.setCharacterSize(15);
    wert.setFillColor(sf::Color::White);





    float inputScale = 100.f; // wie stark Maus → komplexe Zahl skaliert

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Mausposition
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Maus → komplexe Zahl (zentriert)
        Complex s(
            (mousePos.x - window.getSize().x / 2.f) / inputScale,
            -(mousePos.y - window.getSize().y / 2.f) / inputScale
        );

        

        // Zetafunktion Partialsummen
        std::vector<Complex> partialSums = zeta_partial_sums(s, 1000);


        // Linie erzeugen
        sf::VertexArray line = complexToLine(partialSums, window.getSize());
        zahl.setPosition(mousePos.x + 20, mousePos.y);
        zahl.setString("s = " + complexToString(s));

        wert.setPosition(partialSums.back().real * 50.f + window.getSize().x / 2.f + 20, -partialSums.back().imag * 50.f + window.getSize().y / 2.f);
        wert.setString("zeta(s) = " + complexToString(partialSums.back()));

        window.clear();
        window.draw(line);
        window.draw(zahl);
        window.draw(wert);
        window.display();
    }

    return 0;
}