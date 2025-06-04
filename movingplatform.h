#pragma once
#include "StaticPlatform.h"

class MovingPlatform : public StaticPlatform {
public:
    MovingPlatform(float x, float y, float width, float height, int id);
    void update(float deltaTime) override;
    sf::Vector2f getMovementOffset(float deltaTime) const;
private:
    float direction;
    float speed = 150.0f;

};
