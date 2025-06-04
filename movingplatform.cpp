#include "MovingPlatform.h"
#include <cstdlib>

MovingPlatform::MovingPlatform(float x, float y, float width, float height, int id)
    : StaticPlatform(x, y, width, height, id) {
    direction = (std::rand() % 2 == 0) ? 1.f : -1.f;
}
void MovingPlatform::update(float deltaTime) {
    shape.move(speed * direction * deltaTime, 0.f);
    float left = shape.getPosition().x;
    float right = left + shape.getSize().x;
    if (left <= 0.f || right >= 800.f) {
        direction *= -1.f;
    }
}
sf::Vector2f MovingPlatform::getMovementOffset(float deltaTime) const {
    return sf::Vector2f(speed * direction * deltaTime, 0.f);
}
