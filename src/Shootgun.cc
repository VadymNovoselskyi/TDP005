#include "Shootgun.h"

#include <iostream>

#include <cmath>
#include "Map.h"

int const Shootgun::BULLETS_COUNT {9};
float const Shootgun::BULLETS_SPREAD_ANGLE {15};
float const Shootgun::angleStep {BULLETS_SPREAD_ANGLE * 2.0f / (BULLETS_COUNT - 1)};
Shootgun::Shootgun()
    : Weapon("Shootgun",
             "Shoot slow with a medium damag",
             /*dmg*/ 20.0f,
             /*attackSpeed (shoots per sec)*/ 1,
             /*bullet speed*/ 30,
             /*bulletHP*/ 1,
             Rarity::BASIC)
{
}

void Shootgun::shoot()
{
    // i is bullets
    for (int i{0}; i < BULLETS_COUNT; i++)
    {
        double angleOffset = i * angleStep - BULLETS_SPREAD_ANGLE;
        Map::instance()->addEntity(
            new Projectile{Transformable::getPosition(),
                           /*bulletRotation*/ Transformable::getRotation() + angleOffset,
                           speed,
                           damage * damageMultiplication,
                           bulletHP,
                           "Shootgun_bullet.png"});
    }
}