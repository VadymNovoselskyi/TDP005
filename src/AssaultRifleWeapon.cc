#include "AssaultRifleWeapon.h"

#include "Map.h"

AssaultRifleWeapon::AssaultRifleWeapon()
    : Weapon("AR",
             "Shoot kinda fast with a mediumlow damag",
             /*dmg*/ 5.5f,
             /*attackSpeed in ms*/ sf::milliseconds(80),
             Rarity::BASIC,
             /*bullet speed*/ 100)
{
}

void AssaultRifleWeapon::shoot()
{
    Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                              Transformable::getRotation(),
                                              speed,
                                              damage * damageMultiplication});
}