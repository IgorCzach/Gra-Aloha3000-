#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "StaticPlatform.h"
#include "button.h"
#include"movingplatform.h"


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
    enum class GameState { StartMenu, ShowingInstructions, Playing, GameOver };
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

};

