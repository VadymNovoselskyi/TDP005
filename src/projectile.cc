#include "projectile.h"

Projectile::Projectile(Point position, Point direction, double velocity, double damage)
    :Entity(std::string{"projectile"}, position), direction{direction}, velocity{velocity}, damage{damage}
{
}

// void Projectile::onCollistion(Entity other)
// {
//     if (other.getTag() == "enemy")
//     {

//     }
// }

void Projectile::move()
{
    position += direction *= velocity;
}
