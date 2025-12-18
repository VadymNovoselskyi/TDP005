#include "AssaultRifle.h"

#include "Map.h"

AssaultRifle::AssaultRifle()
    : Weapon("AR",
             "Shoot kinda fast with a mediumlow damag",
             /*dmg*/ 33.5f,
             /*attackSpeed (shoots per sec)*/ 6,
             /*bullet speed*/ 40,
             /*bulletHP*/ 1,
             Rarity::BASIC)
{
}
void AssaultRifle::shoot()
{
    Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                              Transformable::getRotation(),
                                              bulletSpeed,
                                              damage * damageMultiplication,
                                              bulletHP,
                                              "AR_bullet.png"});
}