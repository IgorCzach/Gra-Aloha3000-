
#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {
public:
    static sf::Texture& getTexture(const std::string& filename);
private:
    static std::map<std::string, sf::Texture> textures;
};
