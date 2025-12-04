#include "Projectile.h"

Projectile::Projectile(Point position, Point direction, double velocity, double damage)
    :Entity(std::string{"projectile"}, position), direction{direction}, velocity{velocity}, damage{damage}
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
    position += direction *= velocity;
}
