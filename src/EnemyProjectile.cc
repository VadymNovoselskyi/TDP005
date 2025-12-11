#include "EnemyProjectile.h"

#include <iostream>

#include "Enemy.h"
#include "Map.h"


EnemyProjectile::EnemyProjectile(
    sf::Vector2f const &pos, double rotation, double velocity, double damage, double hp, std::string pngName)
    : Entity(std::string{"projectile"}, pos, hp), velocity{velocity}, damage{damage},
      texture{TextureManager::instance()->getTexture(pngName)}
{
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setRotation(rotation);
    sf::Sprite::setOrigin(sf::Sprite::getScale().x / 2, sf::Sprite::getScale().y / 2);
}

void EnemyProjectile::onCollision(Entity *other)
{
    if (other->getTag() == "player")
    {
        other->takeDamage(damage);
        takeDamage();
    }
}

void EnemyProjectile::onBorderCollision()
{
    Map::instance()->removeEntity(this);
}

void EnemyProjectile::move()
{
    sf::Vector2f dir{
        static_cast<float>(std::cos((sf::Sprite::getRotation() + 90) * M_PI / 180.0f)),
        static_cast<float>(std::sin((sf::Sprite::getRotation() + 90) * M_PI / 180.0f))};

    sf::Sprite::Transformable::move(-dir.x * velocity, -dir.y * velocity);
}

void EnemyProjectile::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}

void EnemyProjectile::takeDamage(double damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        die();
    }
}

void EnemyProjectile::die()
{
    Map::instance()->removeEntity(this);
}