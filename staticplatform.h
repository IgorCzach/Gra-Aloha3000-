#pragma once
#include "Platform.h"


class StaticPlatform : public Platform {
public:
    StaticPlatform(float x, float y, float width, float height, int id);
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;
    int getID() const override;

protected:
    sf::RectangleShape shape;
    int m_platformID;
};
