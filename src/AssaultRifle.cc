#include "AssaultRifle.h"

#include "Map.h"

AssaultRifle::AssaultRifle()
    : Weapon("AR",
             "Shoot kinda fast with a mediumlow damag",
             /*dmg*/ 12.5f,
             /*attackSpeed (shoots per sec)*/ 10,
             /*bullet speed*/ 40,
             /*bulletHP*/ 2,
             Rarity::BASIC)
{
}
void AssaultRifle::shoot()
{
    Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                              Transformable::getRotation(),
                                              speed,
                                              damage * damageMultiplication,
                                              bulletHP,
                                              "AR_bullet.png"});
}