#pragma once
#include "StaticPlatform.h"
#include "Player.h"


class SharkPlatform : public StaticPlatform {
public:
    SharkPlatform(float x, float y, float width, float height, int id);

    void handleSharkEvent(sf::RenderWindow& window, Player& player);
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBounds() const override;

private:
    sf::RectangleShape popupBox;
    sf::Text questionText;
    sf::RectangleShape yesButton;
    sf::RectangleShape noButton;
    sf::Text yesText;
    sf::Text noText;

    bool showPopup = false;
    bool alreadyActivated = false;

    sf::Font font;
};
