#pragma once
#include <SFML/Graphics.hpp>
#include "platform.h"

class Shell {
public:
    Shell(float x, float y, Platform* parent = nullptr);
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isCollected = false;


private:
    sf::Sprite sprite;
    static sf::Texture texture;
    static bool textureLoaded;
    Platform* parentPlatform = nullptr; // wskaźnik na platformę, jeśli przypisana
    sf::Vector2f offsetFromPlatform;
};
