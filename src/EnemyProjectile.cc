#include "EnemyProjectile.h"

// #include <iostream>

#include "Enemy.h"
#include "Map.h"


EnemyProjectile::EnemyProjectile(
    sf::Vector2f const &pos, double rotation, double velocity, double damage, double hp, std::string pngName)
    : Projectile(pos, rotation, velocity, damage, hp, pngName), damage{damage}
{

}

void EnemyProjectile::onCollision(Entity *other)
{
    if (other->getTag() == "player")
    {
        other->takeDamage(damage);
        takeDamage();
    }
    if (other->getTag() == "obstacle")
    {
        die();
    }
}

