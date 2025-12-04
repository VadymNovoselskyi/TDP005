#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

#include "point.h"

class Entity : public sf::Sprite
{
  public:
    Entity(std::string tag, Point position);
    virtual void onCollistion(Entity other) = 0;
    std::string getTag();
    Point getPosition();

  protected:
    Point position;

  private:
    std::string tag;
};

#endif