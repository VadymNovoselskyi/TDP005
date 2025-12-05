#include "Character.h"

Character::Character(
    float maxHP, float currentHP, int movementSpeed, Point position, Point direction)
    : maxHP{maxHP}, currentHP{currentHP}, movementSpeed{movementSpeed}, position{position},
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