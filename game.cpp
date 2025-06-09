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
    if (!gameOverTexture.loadFromFile("./gameover.png")) {
        std::cerr << "Błąd ładowania gameover.png\n";
    }
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(0, 0);

    restartButton.setSize({200, 50});
    restartButton.setPosition(80, 400);
    restartButton.setFillColor(sf::Color::Green);

    endButton.setSize({200, 50});
    endButton.setPosition(420, 400);
    endButton.setFillColor(sf::Color::Red);

    restartText.setFont(font);
    restartText.setString("PLAY AGAIN");
    restartText.setCharacterSize(16);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(100, 410);

    endText.setFont(font);
    endText.setString("END GAME");
    endText.setCharacterSize(16);
    endText.setFillColor(sf::Color::White);
    endText.setPosition(460, 410);

    finalTimeText.setFont(font);
    finalTimeText.setCharacterSize(19);
    finalTimeText.setFillColor(sf::Color::White);
    finalTimeText.setPosition(220.0f, 150.0f);
    playerStartY = player.getPosition().y;

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
                gameClock.restart();
                initPlatforms();
            }
        }
    }

    if (currentState == GameState::Playing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.jump();
    }
    if (currentState == GameState::GameOver && event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (restartButton.getGlobalBounds().contains(mousePos)) {
            player.teleportToStart();
            player.resetState();
            initPlatforms();
            cameraView.setCenter(350.f, 250.f);
            gameClock.restart();
            currentState = GameState::Playing;
        }
        else if (endButton.getGlobalBounds().contains(mousePos)) {
            window.close();
        }
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



    //float cameraBottom = cameraView.getCenter().y + cameraView.getSize().y / 2.f;
    float currentY = player.getPosition().y;

    if (currentY - playerStartY > 10.f) {
        currentState = GameState::GameOver;

        int seconds = static_cast<int>(gameClock.getElapsedTime().asSeconds());
        finalTimeText.setString("Czas gry: " + std::to_string(seconds) + "s");

        return;
    }
    sf::Vector2f playerStart = player.getPosition();
    cameraView.setCenter(WINDOW_WIDTH / 2.f, playerStart.y + 100.f);
    //if (playerPos.y < viewY - 100.f) {
       // cameraView.setCenter(WINDOW_WIDTH / 2.f, playerPos.y + 100.f);
  //  }

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
    else if(currentState == GameState::GameOver){
        window.setView(window.getDefaultView());
        window.draw(gameOverSprite);
        window.draw(finalTimeText);
        window.draw(restartButton);
        window.draw(endButton);
        window.draw(restartText);
        window.draw(endText);
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




