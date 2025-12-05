#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Entity.h"

class Character : public Entity
{
  public:
    Character(std::string const &tag,
              double maxHP,
              double currentHP,
              int movementSpeed,
              sf::Vector2f const &position,
              sf::Vector2f const &direction);

    void takeDamage(int);
    void setDirection(sf::Vector2f);
    sf::Vector2f getDirection() const;
    void setMovementSpeed(int);

  protected:
    double maxHP;
    double currentHP;
    int movementSpeed;
    sf::Vector2f direction;

    virtual void die() = 0;
};

#endif /*CHARACTER_H*/