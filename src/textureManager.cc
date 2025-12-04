#include "textureManager.h"

#include <map>

TextureManager::TextureManager() : textureMap{}
{
}

sf::Texture TextureManager::getTexture(std::string name)
{
    if (auto resualt = textureMap.find(name);
        resualt != textureMap.end()) // tog if statmentet från
                                     // https://en.cppreference.com/w/cpp/container/map/find.html
    {
        return resualt->second;
    }
    else
    {
        sf::Texture t{};
        t.loadFromFile(name);
        textureMap[name] = t;
        return t;
    }
}
