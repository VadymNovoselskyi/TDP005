#include "entity.h"

Entity::Entity(std::string tag, Point position) : tag{tag}, position{position}
{
}

std::string Entity::getTag()
{
    return tag;
}

Point Entity::getPosition()
{
    return position;
}