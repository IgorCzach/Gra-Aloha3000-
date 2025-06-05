#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.h"
#include "movingplatform.h"


class Player {
public:
    Player(float x, float y);
    void handleInput();
    void update(std::vector<Platform*>& platforms, float deltaTime);
    void draw(sf::RenderWindow& window);
    void jump();
    void teleport();
    sf::FloatRect getHitbox() const;
    sf::Vector2f getPosition() const;
    void teleportToStart();
    sf::FloatRect getBounds() const { return getHitbox(); }

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    MovingPlatform* standingOn = nullptr;

    float animationTimer;
    const float animationDelay = 0.15f;
   const float moveSpeed = 200.0f;

    enum State { Standing, Jumping, MovingLeft, MovingRight } currentState;
    void animate(float deltaTime);

    bool isOnGround;
    bool isInAir;
    int currentPlatformID;
    int previousPlatformID;
};
