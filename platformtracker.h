#pragma once
#include <SFML/Graphics.hpp>

class PlatformTracker {
public:
    PlatformTracker();
    void update(int platformID);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text platformText;
};
