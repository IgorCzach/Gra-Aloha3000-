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
//metode getbounds tzreba było zmodyfikować, ponieważ kolizja wykrywana była z kazdej strony platformy
//problem występuje zwłaszcza przy osotaniej platformie - Victory
sf::FloatRect StaticPlatform::getBounds() const {
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();
    return sf::FloatRect(pos.x, pos.y, size.x, 5.f);// cienki pasek na górze platformy, np. 5px wysokości
}

int StaticPlatform::getID() const {
    return m_platformID;
}

sf::Vector2f StaticPlatform::getPosition() const {
    return shape.getPosition();
}
