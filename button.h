#pragma once
#include <SFML/Graphics.hpp>
struct Button {
    sf::RectangleShape shape;
    sf::Text label;

    bool isHovered(const sf::Vector2f& mousePos) const {
        return shape.getGlobalBounds().contains(mousePos);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(label);
    }
};
