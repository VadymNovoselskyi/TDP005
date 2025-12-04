#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>

#include <string>

class TextureManager
{
    public:
    TextureManager();
    sf::Texture getTexture(std::string name);

    private:
    std::map<std::string, sf::Texture> textureMap;
};

#endif