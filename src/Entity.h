#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

//to lower classes
#include "TextureManager.h"

class Entity : public sf::Sprite
{
  public:
    Entity(std::string tag, sf::Vector2f pos);
    virtual void onCollision(std::string other /*otehr = other.tag*/) = 0;
    std::string getTag();
    virtual void move() = 0;
    virtual void draw(sf::RenderWindow *window) const = 0;


  private:
    std::string tag;
};

#endif