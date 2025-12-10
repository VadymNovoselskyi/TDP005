#include "SniperRifle.h"

#include "Map.h"

SniperRifle::SniperRifle()
    : Weapon("AR",
             "Shoot kinda fast with a mediumlow damag",
             /*dmg*/ 5.5f,
             /*attackSpeed (shoots per sec)*/ 1,
             Rarity::BASIC,
             /*bullet speed*/ 200)
{
}

void SniperRifle::shoot()
{
    Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                              Transformable::getRotation(),
                                              speed,
                                              damage * damageMultiplication});
}