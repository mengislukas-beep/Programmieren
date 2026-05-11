#include "print.h"
#include <SFML/Graphics.hpp>
#include <vector>


void print(sf::RenderWindow& window,
               const std::vector<int>& data,
               int startpo,
               int endpo,
               const sf::Color& color)
{
    const int m = static_cast<int>(data.size());
    if (m == 0) return;

    const float windowHeight = static_cast<float>(window.getSize().y);
    const float barWidth = static_cast<float>(endpo - startpo) / static_cast<float>(m);
    const float startX = static_cast<float>(startpo);

    sf::RectangleShape rect;
    rect.setFillColor(color);

    for (int i = 0; i < m; ++i)
    {
        const float height = (static_cast<float>(data[i]) / static_cast<float>(m)) * windowHeight;

        rect.setSize(sf::Vector2f(barWidth, height));
        rect.setPosition(startX + i * barWidth, windowHeight - height);

        window.draw(rect);
    }
}
