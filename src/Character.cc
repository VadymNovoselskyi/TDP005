#include "Character.h"

Character::Character(std::string const &tag,
                     double hp,
                     int movementSpeed,
                     sf::Vector2f const &position)
    : Entity(tag, position, hp), movementSpeed{movementSpeed}
{
}

void Character::setMovementSpeed(int newSpeed)
{
    movementSpeed = newSpeed;
}