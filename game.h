#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "StaticPlatform.h"
#include "button.h"
#include"movingplatform.h"
#include "sharkplatform.h"
#include <SFML/Audio.hpp>
#include "shell.h"
class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void initPlatforms();
    bool isGameOver = false;
    sf::RenderWindow window;
    Player player;
    sf::View cameraView;
    std::vector<Platform*> platforms;
    enum class GameState { StartMenu, ShowingInstructions, Playing, GameOver, Victory, Instr };
    GameState currentState = GameState::StartMenu;
    sf::Font font;
    sf::Texture startTexture;
    sf::Sprite startSprite;
    sf::Texture playButtonTexture;
    sf::Sprite playButtonSprite;
    sf::Texture instructionsTexture;
    sf::Sprite instructionsSprite;
    sf::Texture playButtonTexture2;
    sf::Sprite playButtonSprite2;
    sf::Text timerText;
    sf::Clock gameClock;
    sf::RectangleShape topBar;
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;

    sf::RectangleShape restartButton;
    sf::RectangleShape endButton;
    sf::Text restartText;
    sf::Text endText;
    sf::Text finalTimeText;
    float playerStartY = 0.f;
    sf::Texture heartTexture;
    sf::Sprite heartSprite;
    std::vector<sf::Sprite> hearts;
    void updateHeartsDisplay();
    float highestPlatformY = player.getPosition().y; //potrzebne do poźniejszesjej implementacji odejmowania hp przy spadaniu
    sf::Texture victoryTexture;
    sf::Sprite victorySprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text finalTimeText2;
    sf::Music backgroundMusic;
    std::vector<Shell> shells;
    int collectedShells = 0;
    sf::Texture instrButtonTexture;
    sf::Sprite instrButtonSprite;
    sf::Texture instrTexture;
    sf::Sprite instrSprite;
    sf::Texture backButtonTexture;
    sf::Sprite backButtonSprite;

};

