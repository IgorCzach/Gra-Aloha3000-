#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "StaticPlatform.h"
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

    sf::RenderWindow window;
    Player player;
    sf::View cameraView;
    std::vector<Platform*> platforms;
};
