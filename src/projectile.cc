#include "projectile.h"

Projectile::Projectile(Point position, Point direction, double velocity, double damage)
    : position{position}, direction{direction}, velocity{velocity}, damage{damage}
{
}