#include "Entity.h"

#include <string>

#include "TextureManager.h"

Entity::Entity(std::string const &tag, sf::Vector2f const &pos, double hp)
    : Sprite(), hp{hp}, tag{tag}
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

void Entity::takeDamage(double &damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        die();
    }
}