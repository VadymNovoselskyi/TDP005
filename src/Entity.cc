#include "Entity.h"
#include "TextureManager.h"
Entity::Entity(std::string tag, sf::Vector2f pos) : Sprite(), tag{tag}

{
    sf::Sprite::Transformable::setPosition(pos);
}

std::string Entity::getTag()
{
    return tag;
}