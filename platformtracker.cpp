#include "PlatformTracker.h"

PlatformTracker::PlatformTracker() {
    platformText.setCharacterSize(24);
    platformText.setFillColor(sf::Color::White);
    platformText.setPosition(600, 20);
}

void PlatformTracker::update(int platformID) {
    platformText.setString("Platforma: " + std::to_string(platformID));
}

void PlatformTracker::draw(sf::RenderWindow& window) {
    window.draw(platformText);
}
