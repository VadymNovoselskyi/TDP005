#include "Character.h"

Character::Character(std::string const &tag,
                     float maxHP,
                     float currentHP,
                     int movementSpeed,
                     sf::Vector2f const &position,
                     sf::Vector2f const &direction)
    : Entity(tag, position), maxHP{maxHP}, currentHP{currentHP}, movementSpeed{movementSpeed},
      direction{direction}
{
}

void Character::takeDamage(double damage)
{
    currentHP = currentHP - damage;
}
void Character::setDirection(sf::Vector2f newDirection)
{
    direction = newDirection;
}
sf::Vector2f Character::getDirection() const
{
    return direction;
}

// sf::Vector2f Character::getPosition() const
// {
//     return position;
// }

void Character::setMovementSpeed(int newSpeed)
{
    movementSpeed = newSpeed;
}