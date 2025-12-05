#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, double velocity, double damage)
    :Entity(std::string{"projectile"}, pos), velocity{velocity}, damage{damage}
{
}

void Projectile::onCollistion(std::string other)
{
    if (other == "enemy")
    {
        //other take damage
    }
}

void Projectile::move()
{
    double x;
    double y;

    //calculate dir

    sf::Sprite::Transformable::move(x, y);
}
