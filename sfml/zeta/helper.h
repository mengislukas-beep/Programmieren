#pragma once
#include "complex.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

sf::VertexArray complexToLine(const std::vector<Complex>& values, sf::Vector2u windowSize) {
    sf::VertexArray line(sf::LineStrip, values.size());

    float scale = 50.f; // Zoom
    float centerX = windowSize.x / 2.f;
    float centerY = windowSize.y / 2.f;

    for (size_t i = 0; i < values.size(); ++i) {
        float x = values[i].real * scale + centerX;
        float y = -values[i].imag * scale + centerY; // Y-Achse invertieren

        line[i].position = sf::Vector2f(x, y);
        line[i].color = sf::Color::White;
    }

    return line;
}

std::string complexToString(const Complex& c) {
    std::ostringstream oss;
    if (c.imag >= 0) {
        oss << std::fixed << std::setprecision(2) << c.real << " + " << c.imag << "i";
    } else {
        oss << std::fixed << std::setprecision(2) << c.real << " - " << -c.imag << "i";
    }
    return oss.str();
}

