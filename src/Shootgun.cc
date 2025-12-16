#include "Shootgun.h"

#include <iostream>

#include "Map.h"

Shootgun::Shootgun()
    : Weapon("Shootgun",
             "Shoot slow with a medium damag",
             /*dmg*/ 20.0f,
             /*attackSpeed (shoots per sec)*/ 1,
             /*bullet speed*/ 40,
             /*bulletHP*/ 1,
             Rarity::BASIC)
{
}

void Shootgun::shoot()
{
    for (int i{0}; i <= 7; i++)
    {
        Map::instance()->addEntity(
            new Projectile{Transformable::getPosition(),
                           /*bulletRotation*/ Transformable::getRotation() + ((i * 5) - 15),
                           speed,
                           damage * damageMultiplication,
                           bulletHP,
                           "Shootgun_bullet.png"});
    }
}