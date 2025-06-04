#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(float x, float y, float width, float height, int id)
    : StaticPlatform(x, y, width, height, id) {}

void MovingPlatform::update(float deltaTime) {
    shape.move(speed * direction * deltaTime, 0.f);
    float left = shape.getPosition().x;
    float right = left + shape.getSize().x;
    if (left <= 0.f || right >= 800.f) {
        direction *= -1.f;
    }
}
