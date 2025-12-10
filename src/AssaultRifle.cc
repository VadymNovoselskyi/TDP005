#include "AssaultRifle.h"

#include "Map.h"

AssaultRifle::AssaultRifle()
    : Weapon("AR",
             "Shoot kinda fast with a mediumlow damag",
             /*dmg*/ 5.5f,
             /*attackSpeed in ms*/ sf::milliseconds(80),
             Rarity::BASIC,
             /*bullet speed*/ 100)
{
}

void AssaultRifle::shoot()
{
    Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                              Transformable::getRotation(),
                                              speed,
                                              damage * damageMultiplication});
}