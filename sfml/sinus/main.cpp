#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main()
{   

    int speed = 120;

    int breite = 1800;
    int hoehe = 800;
    sf::RenderWindow window(sf::VideoMode(breite, hoehe), "Sinus");

    int middleX = 300;
    int middleY = hoehe / 2;

    float t = 0.f;
    float dt = 0.005f * speed / 100.f;

    float amplitude = 200.f;
    int count = 50;

    std::vector<sf::Vertex> wavePoints;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::vector<sf::CircleShape> circles;
        std::vector<sf::CircleShape> points;

        float x = middleX;
        float y = middleY;

        for (int i = 0; i < count; i++)
        {
            float radius = amplitude / (2.f * i + 1.f);
            float angle = (2.f * i + 1.f) * t;

            float oldX = x;
            float oldY = y;

            x += radius * std::cos(angle) * std::pow(-1.f, i);
            y += radius * std::sin(angle);





            sf::CircleShape circle(radius);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1.f);
            circle.setPosition(oldX - radius, oldY - radius);
            circles.push_back(circle);

            sf::CircleShape point(5.f);
            point.setFillColor(sf::Color::White);
            point.setPosition(x - 5.f, y - 5.f);
            points.push_back(point);
        }

        window.clear();

        for (int i = 0; i < static_cast<int>(circles.size()); i++)
        {
            window.draw(circles[i]);
            // window.draw(points[i]);
        }

        sf::Vertex line[] = 
        {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(700, y), sf::Color::White)
        };

        window.draw(line, 2, sf::Lines);

        wavePoints.insert(wavePoints.begin(), sf::Vertex(sf::Vector2f(700, y), sf::Color::White));

        for (auto& point : wavePoints)
        {
            point.position.x += 0.2f * speed / 100.f;
        }

        if (wavePoints.size() > 8000)
        {
            wavePoints.pop_back();
        }

        window.draw(wavePoints.data(), wavePoints.size(), sf::LinesStrip);
        






        window.display();

        t += dt;
    }

    return 0;
}