#include "Character.h"

Character::Character(
    double maxHP, double currentHp, int movementSpeed, Point positon, Point direction)
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