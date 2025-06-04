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
    const int numPlatforms = 50;
    const float platformHeight = 0.1f;
    const float verticalSpacing = 45.0f;

    float currentY = WINDOW_HEIGHT - 40.f;

    platforms.reserve(numPlatforms);

    for (int i = 0; i < numPlatforms; ++i) {
        float width = (i == 0) ? WINDOW_WIDTH / 100.f : 1.0f;
        float x = (i == 0) ? 0.f : static_cast<float>(std::rand() % (WINDOW_WIDTH - static_cast<int>(width * 100)));
        if (i != 0) currentY -= verticalSpacing;

        Platform* platform = (i >= 10)
                                 ? static_cast<Platform*>(new MovingPlatform(x, currentY, width, platformHeight, i))
                                 : static_cast<Platform*>(new StaticPlatform(x, currentY, width, platformHeight, i));

        platforms.push_back(platform);
    }
}




