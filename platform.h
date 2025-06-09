#pragma once
#include <SFML/Graphics.hpp>

class Platform {
public:
    virtual ~Platform() = default;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual int getID() const = 0;
    virtual void update(float deltaTime);
    virtual sf::Vector2f getPosition() const = 0;
};

