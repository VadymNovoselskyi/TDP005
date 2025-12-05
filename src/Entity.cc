#include "Entity.h"

Entity::Entity(std::string tag, Point position) : sf::Sprite(), position{position}, tag{tag}
{
}

std::string Entity::getTag()
{
    return tag;
}

// Point Entity::getPosition()
// {
//     return position;
// }