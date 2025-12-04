#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>

#include <string>

class textureManager
{
    public:
    sf::Texture getTexture(std::string name);
};

#endif