#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

#include "point.h"

class Entity : public sf::Sprite
{
  public:
    Entity(std::string tag, Point position);
    virtual void onCollistion(std::string other /*otehr = other.tag*/) = 0;
    std::string getTag();
    Point getPosition();

  protected:
    Point position;
    std::string variation;
  private:
    std::string tag;
};

#endif