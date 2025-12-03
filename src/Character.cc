#include "Character.h"


void Character::takeDamage(double damage)
{
    currentHP = currentHP- damage;
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