#include "TextureManager.h"

#include <map>

TextureManager *TextureManager::instancePtr{nullptr};

TextureManager *TextureManager::instance()
{
    if (TextureManager::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init TextureManager before calling instance on it");
    }
    return TextureManager::instancePtr;
}

TextureManager *TextureManager::init()
{
    TextureManager::instancePtr = new TextureManager();
    return TextureManager::instancePtr;
}

void TextureManager::deleteInstance()
{
    // std::cout << "Deleting the instance" << std::endl;
    delete TextureManager::instancePtr;
    TextureManager::instancePtr = nullptr;
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
        t.loadFromFile("static/" + name);
        textureMap[name] = t;
        return t;
    }
}

TextureManager::TextureManager() : textureMap{}
{
}
