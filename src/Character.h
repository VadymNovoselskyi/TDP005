#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Entity.h"
#include "Point.h"

class Character : public Entity
{
  public:
    Character(std::string tag,
              double maxHP,
              double currentHP,
              int movementSpeed,
              Point position,
              Point direction);

    virtual void move() = 0;
    void takeDamage(int);
    void setDirection(Point);
    Point getDirection();
    void setMovementSpeed(int);

  protected:
    // sf::SDL_Surface* sprite;  -sprite till karaktrer
    double maxHP;
    double currentHP;
    int movementSpeed;
    Point direction;
    virtual void die() = 0;
};

#endif /*CHARACTER_H*/