#include "Projectile.h"
#include <iostream>

Projectile::Projectile(sf::Vector2f const &pos, double rotation, double velocity, double damage)
    :Entity(std::string{"projectile"}, pos), velocity{velocity}, damage{damage}, texture{TextureManager::instance()->getTexture("AR_bullet.png")}
{
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setRotation(rotation);
}

void Projectile::onCollision(std::string const &other)
{
    if (other == "enemy")
    {
        // other take damage
    }
}

void Projectile::move()
{
    sf::Vector2f dir {std::cos(Transformable::getRotation()), std::sin(Transformable::getRotation())};

    sf::Sprite::Transformable::move(-dir.x * velocity, -dir.y * velocity);
}

void Projectile::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    // Draw HP and XP too plz
}