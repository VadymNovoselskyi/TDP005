#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

class TextureManager
{
  public: // singelton taget från vadyms kod
    static TextureManager *instance();
    static TextureManager *init();
    static void deleteInstance();

    sf::Texture *getTexture(std::string const &name);

  private:
    static TextureManager *instancePtr;
    TextureManager();

    std::map<std::string, sf::Texture *> textureMap;
};

#endif