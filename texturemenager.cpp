#include "texturemenager.h"


std::map<std::string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::getTexture(const std::string& filename) {
    if (textures.find(filename) == textures.end()) {
        textures[filename].loadFromFile(filename);
    }
    return textures[filename];
}
