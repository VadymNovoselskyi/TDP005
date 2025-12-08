#include "Obstacle.h"

#include <iostream>

#include "Entity.h"

Obstacle::Obstacle(sf::Texture const *texture, sf::Vector2f position) : Entity("obstacle", position)
{
    auto obstackeSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(obstackeSize.x / 2.0, obstackeSize.y / 2.0);
}

void Obstacle::onCollision(std::string const &other)
{
}

void Obstacle::move()
{
}

void Obstacle::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}
