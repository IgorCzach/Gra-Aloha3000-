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
    if (!heartTexture.loadFromFile("./serce.png")) {
        std::cerr << "Nie można załadować grafiki serce!\n";
        exit(1);
    }
    updateHeartsDisplay();
    if (!victoryTexture.loadFromFile("./wygrana.png")) {
        std::cerr << "Błąd ładowania victory.png\n";
        exit(1);
    }
    victorySprite.setTexture(victoryTexture);


    if (!gameOverTexture.loadFromFile("./gameover.png")) {
        std::cerr << "Błąd ładowania gameover.png\n";
    }
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(0, 0);
    // if (!backgroundTexture.loadFromFile("C:/Users/Igor/Desktop/Gra_2/tlo3.png")) {
    //     std::cerr << "Nie można załadować tła!\n";
    //     exit(1);
    // }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setTextureRect(sf::IntRect(0,2000, WINDOW_WIDTH, 3000));
    if (!backgroundMusic.openFromFile("./Muzyka2.mp3")) {
        std::cerr << "Nie można załadować muzyki!\n";
    }


    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10.f, 10.f);

    topBar.setSize({ WINDOW_WIDTH, 40 });
    topBar.setFillColor(sf::Color(50, 50, 50, 200));
    topBar.setPosition(0, 0);

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

    finalTimeText2.setFont(font);
    finalTimeText2.setCharacterSize(19);
    finalTimeText2.setFillColor(sf::Color::Yellow);
    finalTimeText2.setPosition(250.0f, 460.0f);



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
                backgroundMusic.setLoop(true);
                backgroundMusic.setVolume(40.f);
                backgroundMusic.play();
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
            player.resetHP();
            updateHeartsDisplay();
            player.teleportToStart();
            player.resetState();
            initPlatforms();
            cameraView.setCenter(350.f, 250.f);
            gameClock.restart();
            currentState = GameState::Playing;
            backgroundMusic.setLoop(true);
            backgroundMusic.setVolume(40.f);
            backgroundMusic.play();
        }
        else if (endButton.getGlobalBounds().contains(mousePos)) {
            window.close();
        }
    }

}

void Game::update(float deltaTime) {
    for (Shell& shell : shells) {
        shell.update();
    }
    player.update(platforms, deltaTime);
    for (Platform* platform : platforms) {

        platform->update(deltaTime);

    }
    sf::Time elapsed = gameClock.getElapsedTime();
    int seconds = static_cast<int>(elapsed.asSeconds());

    timerText.setString("Czas: " + std::to_string(seconds) + " s");
    float currentY = player.getPosition().y;


    // znajdownie najwyższej platformy, której gracz dotknął
    for (Platform* platform : platforms) {
        if (player.getBounds().intersects(platform->getBounds())) {
            highestPlatformY = platform->getPosition().y;
            break;
        }
    }

    float fallDistance = currentY - highestPlatformY;
    int fallenPlatforms = static_cast<int>(fallDistance / 60.0f);

    if (fallenPlatforms >= 3) {
        int damage = 0;
        if (fallenPlatforms >= 9) {
            damage = 3;
        } else if (fallenPlatforms >= 6) {
            damage = 2;
        } else {
            damage = 1;
        }

        player.hp -= damage;
        updateHeartsDisplay();

        if (player.hp <= 0) {
            currentState = GameState::GameOver;
                backgroundMusic.stop();
            finalTimeText.setString("Czas gry: " + std::to_string(static_cast<int>(gameClock.getElapsedTime().asSeconds())) + "s");
            return;
        }
        highestPlatformY = currentY;
    }
    for (Shell& shell : shells) {
        sf::FloatRect playerFeet = player.getHitbox();
        playerFeet.top += playerFeet.height - 5.f;  // dolna część tylko
        playerFeet.height = 5.f;

        if (!shell.isCollected && playerFeet.intersects(shell.getBounds())) {
            shell.isCollected = true;
            collectedShells++;

            if (collectedShells % 5 == 0 && player.hp < 3) {
                player.hp++;
                updateHeartsDisplay();
            }
        }

    }
    sf::Vector2f playerStart = player.getPosition();
    cameraView.setCenter(WINDOW_WIDTH / 2.f, playerStart.y + 100.f);

    if (!platforms.empty()) {
        Platform* lastPlatform = platforms.back();
        sf::FloatRect platformBounds = lastPlatform->getBounds();
        sf::FloatRect playerFeet = player.getBounds();

        //duzy problem był z wykryciem osotaniej platformy i z kolizja z nią
        //naprawinie problemu - odpowienie ustwainie odległosci
        //bool sprawdza czy gracz stoi
        bool standsOn =
            playerFeet.top + playerFeet.height <= platformBounds.top + 2.f && // górna powierzchnia
            playerFeet.top + playerFeet.height >= platformBounds.top - 5.f && // nie za wysoko
            playerFeet.left + playerFeet.width > platformBounds.left + 5.f &&
            playerFeet.left < platformBounds.left + platformBounds.width - 5.f;

        if (standsOn) {
            currentState = GameState::Victory;
            finalTimeText2.setString("Czas gry: " + std::to_string(static_cast<int>(gameClock.getElapsedTime().asSeconds())) + "s");
            return;
        }
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
       // window.draw(backgroundSprite);
        for ( Shell& shell : shells) {
            shell.draw(window);
        }
        for (auto* platform : platforms)
            platform->draw(window);
        player.draw(window);

        // 2. Widok UI (statyczny) – reset widoku
        window.setView(window.getDefaultView());
        window.draw(topBar);
        window.draw(timerText);
        for (const auto& heart : hearts) {
            window.draw(heart);
        }
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
    else if (currentState == GameState::Victory) {
        window.setView(window.getDefaultView());
        window.draw(victorySprite);
        window.draw(finalTimeText2);
    }

    window.display();



}

void Game::initPlatforms() {
    const int numPlatforms = 16;
    const float platformHeight = 0.23f;
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
            platform = new SharkPlatform(x, currentY, width, platformHeight, i);
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
    shells.clear();

    for (int i = 1; i < numPlatforms; ++i) {
        if (i % 3 == 0) {
            Platform* p = platforms[i];
            sf::Vector2f pos = p->getPosition();
            shells.emplace_back(pos.x + 30.f, pos.y - 30.f, p); // przypisana platforma
        }
    }



}
void Game::updateHeartsDisplay() {
    hearts.clear();

    float targetHeartHeight = 30.f;
    float scale = targetHeartHeight / heartTexture.getSize().y;

    float margin = 10.f;
    //odstęp między sercami
    float spacing = 5.f;
    float startX = WINDOW_WIDTH - margin;

    for (int i = 0; i < player.hp; ++i) {
        sf::Sprite sprite;
        sprite.setTexture(heartTexture);
        sprite.setScale(scale, scale);

        sf::FloatRect bounds = sprite.getGlobalBounds();
        startX -= bounds.width;

        sprite.setPosition(startX, (40.f - bounds.height) / 2.f);
        hearts.push_back(sprite);

        startX -= spacing;
    }
}




