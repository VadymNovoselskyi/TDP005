#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Character : public Entity
{
  public:
    Character(std::string const &tag, double hp, int movementSpeed, sf::Vector2f const &position);

    void setMovementSpeed(int movementSpeed);

  protected:
    int movementSpeed;
    sf::Vector2f position;
};

#endif /*CHARACTER_H*/