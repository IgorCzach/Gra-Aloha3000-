#include "Game.h"
#include "iostream"

const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 500;

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Aloha3000"),
    player((WINDOW_WIDTH - 40.f) / 2.f, WINDOW_HEIGHT - 100.f),currentState(GameState::StartMenu) {
    if (!startTexture.loadFromFile("./redbull.png")) {
        std::cerr << "Nie można załadować tła startowego!\n";
        exit(1);
    }
    startSprite.setTexture(startTexture);

    if (!playButtonTexture.loadFromFile("./button.png")) {
        std::cerr << "Nie można załadować grafiki przycisku graj!\n";
        exit(1);
    }
    playButtonSprite.setTexture(playButtonTexture);
    playButtonSprite.setPosition((WINDOW_WIDTH - playButtonTexture.getSize().x) / 2.f, 400.f);
    if (!instructionsTexture.loadFromFile("./instrukcja.png")) {
        std::cerr << "Nie można załadować grafiki z zasadami!\n";
        exit(1);
    }
    instructionsSprite.setTexture(instructionsTexture);
    if (!font.loadFromFile("./PressStart2P-Regular.ttf")) {
        std::cerr << "Nie udało się załadować czcionki!\n";
    }
    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 10.f);
    topBar.setSize({ WINDOW_WIDTH, 40 });
    topBar.setFillColor(sf::Color(50, 50, 50, 200));
    topBar.setPosition(0, 0);

}

void Game::run() {

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();

        if (currentState == GameState::Playing && !isGameOver)
            update(deltaTime);

        render();
    }
}



void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (currentState == GameState::StartMenu && event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (playButtonSprite.getGlobalBounds().contains(mousePos)) {
                    currentState = GameState::ShowingInstructions;
                }
            }
        } else if (currentState == GameState::ShowingInstructions && event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                currentState = GameState::Playing;
                initPlatforms();
            }
        }
    }

    if (currentState == GameState::Playing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.jump();
    }
}

void Game::update(float deltaTime) {
    player.update(platforms, deltaTime);
    for (Platform* platform : platforms) {

        platform->update(deltaTime);

    }
    sf::Time elapsed = gameClock.getElapsedTime();
    int seconds = static_cast<int>(elapsed.asSeconds());

    timerText.setString("Czas: " + std::to_string(seconds) + " s");

    sf::Vector2f playerPos = player.getPosition();
    float viewY = cameraView.getCenter().y;
    if (playerPos.y < viewY - 100.f) {
        cameraView.setCenter(WINDOW_WIDTH / 2.f, playerPos.y + 100.f);
    }
    if (player.getPosition().y > WINDOW_HEIGHT) {
        isGameOver = true;
    }
}

void Game::render() {


    window.clear();

    if (currentState == GameState::StartMenu) {
        window.setView(window.getDefaultView());
        window.draw(startSprite);
        window.draw(playButtonSprite);

    } else if (currentState == GameState::ShowingInstructions) {
        window.setView(window.getDefaultView());
        window.draw(instructionsSprite);

    } else if (currentState == GameState::Playing) {
        // 1. Widok gry (z kamerą)
        window.setView(cameraView);
        for (auto* platform : platforms)
            platform->draw(window);
        player.draw(window);

        // 2. Widok UI (statyczny) – reset widoku
        window.setView(window.getDefaultView());
        window.draw(topBar);
        window.draw(timerText);
    }

    window.display();



}

void Game::initPlatforms() {
    const int numPlatforms = 30;
    const float platformHeight = 0.22f;
    const float verticalSpacing = 60.0f;
    const float maxHorizontalOffset = 150.f;
    const float platformWidth = 1.0f;


    float currentY = WINDOW_HEIGHT - 40.f;
    float lastX = 0.f;

    platforms.clear();
    platforms.reserve(numPlatforms);

    for (int i = 0; i < 10; ++i) {
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

        Platform* platform;
        if (i == 6) {
            platform = new SharkPlatform(x, currentY, width, platformHeight, i); // 🦈 Rekin jako 6.
        } else {
            platform = new StaticPlatform(x, currentY, width, platformHeight, i);
        }

        platforms.push_back(platform);
        lastX = x;
        //Platform* platform = new StaticPlatform(x, currentY, width, platformHeight, i);
       // platforms.push_back(platform);
        //lastX = x;


    }
    for (int i = 10; i < numPlatforms; ++i) {
        currentY -= verticalSpacing;

        float width = platformWidth;
        float x = std::clamp(
            lastX + static_cast<float>((std::rand() % int(2 * maxHorizontalOffset)) - maxHorizontalOffset),
            0.f,
            WINDOW_WIDTH - width * 100.f
            );

        Platform* moving = new MovingPlatform(x, currentY, width, platformHeight, i);
        platforms.push_back(moving);
        lastX = x;
    }



}




