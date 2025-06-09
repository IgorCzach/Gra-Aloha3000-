#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "texturemenager.h"

const float GRAVITY = 1000.0f;
const float JUMP_VELOCITY = -400.f;

Player::Player(float x, float y)
    : velocity(0.f, 0.f), animationTimer(0.f), currentState(Standing),
    isOnGround(false), isInAir(true), currentPlatformID(-1), previousPlatformID(-1) {

    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(40.f, 60.f));

    shape.setTexture(&TextureManager::getTexture("./gracz6.png"));

    shape.setTextureRect(sf::IntRect(0, 0, 90, 180));
}

void Player::handleInput() {
    velocity.x = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x = -moveSpeed;
        currentState = MovingLeft;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x = moveSpeed;
        currentState = MovingRight;
    } else {
        currentState = Standing;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        jump();
    }
}

void Player::update(std::vector<Platform*>& platforms, float deltaTime) {
    handleInput();

    velocity.y += GRAVITY * deltaTime;
    shape.move(velocity.x * deltaTime, 0.f);
    shape.move(0.f, velocity.y * deltaTime);

    isOnGround = false;
    isInAir = true;

    sf::FloatRect hitbox = getHitbox();


    for (auto* p : platforms) {
        if (hitbox.intersects(p->getBounds())) {
            sf::FloatRect platformBounds = p->getBounds();
            float playerBottom = shape.getPosition().y + shape.getSize().y;
            float platformTop = platformBounds.top;

            // Uderzenie z góry platformy, nie z boku lub dołu
            if (velocity.y > 0 && playerBottom - velocity.y * deltaTime <= platformTop + 5.f) {
                velocity.y = 0;
                isOnGround = true;
                isInAir = false;
                shape.setPosition(shape.getPosition().x, platformTop - shape.getSize().y);

                if (p->getID() > previousPlatformID) {
                    currentPlatformID = p->getID();
                    previousPlatformID = currentPlatformID;
                }
                standingOn = dynamic_cast<MovingPlatform*>(p);


            }

        }

    }
    if (standingOn) {
        shape.move(standingOn->getMovementOffset(deltaTime));
    }
    animate(deltaTime);
}

void Player::animate(float deltaTime) {
    animationTimer += deltaTime;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Player::jump() {
    if (isOnGround) {
        velocity.y = JUMP_VELOCITY;
        isOnGround = false;
        isInAir = true;
        currentState = Jumping;
    }
}

void Player::teleport() {
    shape.setPosition(shape.getPosition().x, 431.f);
}

//metoda była potzrebna do wykrywania platformy z góry a nie od boku
//ustawiam w niej małą odległość nad platforma tak aby gracz dotykał ją stopami
sf::FloatRect Player::getBounds() const {
    sf::FloatRect bounds = shape.getGlobalBounds();
    return sf::FloatRect(
        bounds.left,
        bounds.top + bounds.height - 5.f,
        bounds.width,
        5.f
        );
}
sf::FloatRect Player::getHitbox() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}
void Player::teleportToStart() {
    float playerWidth = shape.getSize().x;
    float playerHeight = shape.getSize().y;

    float platformX = 0.f;
    float platformY = 460.f;

    float x = platformX + (700.f - playerWidth) / 2.f;
    float y = platformY - playerHeight;

    shape.setPosition(x, y);
    //velocity = sf::Vector2f(0.f, 0.f);
}
void Player::resetState(){
    velocity = sf::Vector2f(0.f, 0.f);
    isInAir = false;
    isOnGround = true;
    currentState = Standing;
    standingOn = nullptr;
}
void Player::resetHP(){
    hp = 3;
}
