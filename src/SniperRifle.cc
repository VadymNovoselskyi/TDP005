#include "SniperRifle.h"

#include "Map.h"

SniperRifle::SniperRifle()
    : Weapon("Sniper",
             "Shoot slow with a High damag",
             /*dmg*/ 200.0f,
             /*attackSpeed (shoots per sec)*/ 1,
             /*bullet speed*/ 50,
             /*bulletHP*/ 3,
             Rarity::RARE)
{
}

void SniperRifle::shoot()
{
    Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                              /*bulletRotation*/ Transformable::getRotation(),
                                              bulletSpeed,
                                              damage * damageMultiplication,
                                              bulletHP,
                                              "Sniper_bullet.png"});
}