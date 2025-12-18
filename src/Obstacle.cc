#include "Obstacle.h"

#include "Entity.h"

Obstacle::Obstacle(sf::Texture const *texture, sf::Vector2f position, std::string const &tag)
    : Entity(tag, position, 1)
{
    sf::Sprite::setTexture(*texture);
}

void Obstacle::onCollision(Entity *other)
{
}

void Obstacle::onBorderCollision()
{
}

void Obstacle::move()
{
}

void Obstacle::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}

void Obstacle::die()
{
}
