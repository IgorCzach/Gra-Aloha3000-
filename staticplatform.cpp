#include "StaticPlatform.h"
#include "texturemenager.h"

StaticPlatform::StaticPlatform(float x, float y, float width, float height, int id)
    : m_platformID(id) {
    shape.setPosition(x, y);
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width * 100.f, height * 100.f));

    shape.setTexture(&TextureManager::getTexture("./platforma.png"));


}

void StaticPlatform::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect StaticPlatform::getBounds() const {
    return shape.getGlobalBounds();
}

int StaticPlatform::getID() const {
    return m_platformID;
}
