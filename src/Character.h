#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Entity.h"

class Character : public Entity
{
  public:
    Character(std::string tag,
              double maxHP,
              double currentHP,
              int movementSpeed,
              sf::Vector2f position,
              sf::Vector2f direction);

    virtual void move() = 0;
    void takeDamage(int);
    void setDirection(sf::Vector2f);
    sf::Vector2f getDirection();
    void setMovementSpeed(int);

  protected:
    // sf::SDL_Surface* sprite;  -sprite till karaktrer
    double maxHP;
    double currentHP;
    int movementSpeed;
    sf::Vector2f direction;
    virtual void die() = 0;
};

#endif /*CHARACTER_H*/