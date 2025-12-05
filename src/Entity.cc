#include "Entity.h"

#include <string>

Entity::Entity(std::string const &tag, sf::Vector2f const &pos) : Sprite(), tag{tag}

{
    sf::Sprite::Transformable::setPosition(pos);
}

std::string Entity::getTag() const
{
    return tag;
}

void Entity::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}