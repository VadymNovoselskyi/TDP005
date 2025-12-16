#include "SniperRifle.h"

#include "Map.h"

SniperRifle::SniperRifle()
    : Weapon("Sniper",
             "Shoot slow with a High damag",
             /*dmg*/ 100.0f,
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
                                              speed,
                                              damage * damageMultiplication,
                                              bulletHP,
                                              "Sniper_bullet.png"});
}