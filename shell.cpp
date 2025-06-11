#include "Shell.h"

sf::Texture Shell::texture;
bool Shell::textureLoaded = false;

Shell::Shell(float x, float y, Platform* parent)
    : parentPlatform(parent) {
    if (!textureLoaded) {
        texture.loadFromFile("./Muszla.png");
        textureLoaded = true;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.7f, 0.7f);

    if (parentPlatform) {
        offsetFromPlatform = { x - parent->getPosition().x, y - parent->getPosition().y };
        sprite.setPosition(parent->getPosition() + offsetFromPlatform);
    } else {
        sprite.setPosition(x, y);
    }
}

void Shell::update() {
    if (parentPlatform && !isCollected) {
        sprite.setPosition(parentPlatform->getPosition() + offsetFromPlatform);
    }
}
void Shell::draw(sf::RenderWindow& window) {
    if (!isCollected) {
        window.draw(sprite);
    }
}

sf::FloatRect Shell::getBounds() const {
    return sprite.getGlobalBounds();
}
