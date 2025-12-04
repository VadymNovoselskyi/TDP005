#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "point.h"
#include "textureManager.h"

#include <string>



class Entity : public sf::Sprite
{
  public:
    Entity(std::string tag, Point position);
    virtual void onCollistion(std::string other /*otehr = other.tag*/) = 0;
    std::string getTag();
    Point getPosition();

  protected:
    Point position;
  private:
    std::string tag;
};

#endif