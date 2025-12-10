#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Character : public Entity
{
  public:
    Character(std::string const &tag,
              double hp,
              int movementSpeed,
              sf::Vector2f const &position);

    void takeDamage(double &);
    void setMovementSpeed(int);

  protected:
    double hp;
    int movementSpeed;
    sf::Vector2f position;

    virtual void die() = 0;
};

#endif /*CHARACTER_H*/