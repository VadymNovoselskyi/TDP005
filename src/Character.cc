#include "Character.h"

Character::Character(std::string tag,
                     double maxHP,
                     double currentHP,
                     int movementSpeed,
                     sf::Vector2f position,
                     sf::Vector2f direction)
    : Entity(tag, position), maxHP{maxHP}, currentHP{currentHP}, movementSpeed{movementSpeed},
      direction{direction}
{
}

void Character::takeDamage(int damage)
{
    currentHP = currentHP - damage;
}
void Character::setDirection(sf::Vector2f newDirection)
{
    direction = newDirection;
}
sf::Vector2f Character::getDirection()
{
    return direction;
}
void Character::setMovementSpeed(int newSpeed)
{
    movementSpeed = newSpeed;
}