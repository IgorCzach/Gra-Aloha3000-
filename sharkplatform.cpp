#include "SharkPlatform.h"
//#include "texturemenager.h"
#include <random>
#include <iostream>

SharkPlatform::SharkPlatform(float x, float y, float width, float height, int id)
    : StaticPlatform(x, y, width, height, id)
{
    //shape.setTexture(&TextureManager::getTexture("./shark_platform.png"));

    //font.loadFromFile("arial.ttf");

    popupBox.setSize({ 300, 150 });
    popupBox.setFillColor(sf::Color(0, 0, 0, 200));
    popupBox.setPosition(250, 200);

    questionText.setFont(font);
    questionText.setString("Czy chcesz zaryzykować i zagrać z rekinem Hazardzistą? - rzuca kością jęsli wypadnie 6 autoamtycznie wygrywasz w innym przypadku cofasz sie na sam początek");
    questionText.setCharacterSize(20);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(270, 220);

    yesButton.setSize({ 100, 40 });
    yesButton.setFillColor(sf::Color::Green);
    yesButton.setPosition(270, 270);

    noButton.setSize({ 100, 40 });
    noButton.setFillColor(sf::Color::Red);
    noButton.setPosition(400, 270);

    yesText.setFont(font);
    yesText.setString("Tak");
    yesText.setCharacterSize(18);
    yesText.setFillColor(sf::Color::Black);
    yesText.setPosition(295, 278);

    noText.setFont(font);
    noText.setString("Nie");
    noText.setCharacterSize(18);
    noText.setFillColor(sf::Color::Black);
    noText.setPosition(430, 278);
}

void SharkPlatform::handleSharkEvent(sf::RenderWindow& window, Player& player)
{
    if (!alreadyActivated && player.getHitbox().intersects(getBounds())) {
        showPopup = true;
    }

    if (showPopup) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect yesRect = yesButton.getGlobalBounds();
        sf::FloatRect noRect = noButton.getGlobalBounds();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (yesRect.contains((sf::Vector2f)mousePos)) {
                std::random_device rd;
                std::mt19937 rng(rd());
                std::uniform_int_distribution<int> dice(1, 6);
                int result = dice(rng);

                std::cout << "Rekin wyrzucił: " << result << "\n";
                if (result == 6) {
                    std::cout << "Wygrałeś! Możesz kontynuować.\n";
                } else {
                    std::cout << "Przegrałeś! Cofasz się na początek!\n";
                    player.teleportToStart();
                }
                alreadyActivated = true;
                showPopup = false;
            }
            else if (noRect.contains((sf::Vector2f)mousePos)) {
                std::cout << "Odmówiłeś gry z rekinem.\n";
                alreadyActivated = true;
                showPopup = false;
            }
        }
    }
}

void SharkPlatform::draw(sf::RenderWindow& window) const
{
    StaticPlatform::draw(window);

    if (showPopup) {
        window.draw(popupBox);
        window.draw(questionText);
        window.draw(yesButton);
        window.draw(noButton);
        window.draw(yesText);
        window.draw(noText);
    }
}

sf::FloatRect SharkPlatform::getBounds() const {
    return shape.getGlobalBounds();
}
