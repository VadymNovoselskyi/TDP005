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
    for (auto &[name, texture] : TextureManager::instancePtr->textureMap)
    {
        delete texture;
    }
    delete TextureManager::instancePtr;
    TextureManager::instancePtr = nullptr;
}

sf::Texture *TextureManager::getTexture(std::string const &name)
{
    if (auto result = textureMap.find(name);
        result != textureMap.end()) // tog if statmentet från
                                    // https://en.cppreference.com/w/cpp/container/map/find.html
    {
        return result->second;
    }
    
    sf::Texture *t{new sf::Texture{}};
    t->loadFromFile("static/" + name);
    textureMap[name] = t;
    return t;
}
