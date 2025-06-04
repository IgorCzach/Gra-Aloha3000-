#include "Game.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Aloha3000"),
    player((WINDOW_WIDTH - 40.f) / 2.f, WINDOW_HEIGHT - 100.f) {
    initPlatforms();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}



void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) player.jump();
}

void Game::update(float deltaTime) {
    player.update(platforms, deltaTime);

    sf::Vector2f playerPos = player.getPosition();
    float viewY = cameraView.getCenter().y;
    if (playerPos.y < viewY - 100.f) {
        cameraView.setCenter(WINDOW_WIDTH / 2.f, playerPos.y + 100.f);
    }
}

void Game::render() {
    window.clear();
    window.setView(cameraView);
    for (auto* platform : platforms)
        platform->draw(window);
    player.draw(window);
    window.display();
}

void Game::initPlatforms() {
    const int numPlatforms = 15;
    const float platformHeight = 0.1f;
    const float verticalSpacing = 60.0f;
    const float maxHorizontalOffset = 150.f;
    const float platformWidth = 1.0f;


    float currentY = WINDOW_HEIGHT - 40.f;
    float lastX = 0.f;

    platforms.clear();
    platforms.reserve(numPlatforms);

    for (int i = 0; i < numPlatforms; ++i) {
        float width = (i == 0) ? WINDOW_WIDTH / 100.f : platformWidth;
        float x;

        if (i == 0) {
            x = 0.f;
        } else {
            currentY -= verticalSpacing;
            float minX = std::max(0.f, lastX - maxHorizontalOffset);
            float maxX = std::min(WINDOW_WIDTH - width * 100.f, lastX + maxHorizontalOffset);
            x = minX + static_cast<float>(std::rand()) / RAND_MAX * (maxX - minX);
        }

        Platform* platform = new StaticPlatform(x, currentY, width, platformHeight, i);
        platforms.push_back(platform);
        lastX = x;
    }
}




