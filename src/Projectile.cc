#include "Projectile.h"

#include <iostream>

#include "Enemy.h"
#include "Map.h"

Projectile::Projectile(sf::Vector2f const &pos,
                       double rotation,
                       double velocity,
                       double damage,
                       double bulletHP,
                       std::string const &pngName)
    : Entity(std::string{"projectile"}, pos, bulletHP), velocity{velocity}, damage{damage},
      texture{TextureManager::instance()->getTexture(pngName)}, isDying{false}
{
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setRotation(rotation);
    sf::Sprite::setOrigin(sf::Sprite::getScale().x / 2, sf::Sprite::getScale().y / 2);
}

void Projectile::onCollision(Entity *other)
{
    if (other->getTag() == "enemy")
    {
        other->takeDamage(damage);
        takeDamage();
    }
    if (other->getTag() == "obstacle")
    {
        die();
    }
}

void Projectile::onBorderCollision()
{
    Map::instance()->removeEntity(this);
}

void Projectile::move()
{
    sf::Vector2f dir{
        static_cast<float>(std::cos((sf::Sprite::getRotation() + 90) * M_PI / 180.0f)),
        static_cast<float>(std::sin((sf::Sprite::getRotation() + 90) * M_PI / 180.0f))};

    sf::Sprite::Transformable::move(-dir.x * velocity, -dir.y * velocity);
}

void Projectile::takeDamage(double damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        die();
    }
}

void Projectile::die()
{
    if (!isDying)
    {
        Map::instance()->removeEntity(this);
    }
    isDying = true;
}
