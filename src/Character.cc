#include "Character.h"

Character::Character(std::string tag,
                     double maxHP,
                     double currentHP,
                     int movementSpeed,
                     Point position,
                     Point direction)
    : Entity(tag, position), maxHP{maxHP}, currentHP{currentHP}, movementSpeed{movementSpeed},
      direction{direction}
{
}

void Character::takeDamage(int damage)
{
    currentHP = currentHP - damage;
}
void Character::setDirection(Point newDirection)
{
    direction = newDirection;
}
Point Character::getDirection()
{
    return direction;
}
void Character::setMovementSpeed(int newSpeed)
{
    movementSpeed = newSpeed;
}