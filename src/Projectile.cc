#include "Projectile.h"

#include <iostream>

#include "Enemy.h"
#include "Map.h"

Projectile::Projectile(
    sf::Vector2f const &pos, double rotation, double velocity, double damage, double hp, std::string pngName)
    : Entity(std::string{"projectile"}, pos, hp), velocity{velocity}, damage{damage},
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

void Projectile::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
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
    std::cout << "Removing projectile: " << this << std::endl;
    if (!isDying)
    {
        Map::instance()->removeEntity(this);
    }
    std::cout << "Removed projectile" << std::endl;
    isDying = true;
}
