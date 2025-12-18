#include "Shootgun.h"

#include "Map.h"

int const Shootgun::BULLETS_COUNT {21};
float const Shootgun::BULLETS_SPREAD_ANGLE {15};
float const Shootgun::ANGLE_STEP {BULLETS_SPREAD_ANGLE * 2.0f / (BULLETS_COUNT - 1)};
Shootgun::Shootgun()
    : Weapon("Shootgun",
             "Shoot slow with a medium damag",
             /*dmg*/ 7.5f,
             /*attackSpeed (shoots per sec)*/ 0.5,
             /*bullet speed*/ 30,
             /*bulletHP*/ 1,
             Rarity::EPIC)
{
}

void Shootgun::shoot()
{
    // i is bullets
    for (int i{0}; i < BULLETS_COUNT; i++)
    {
        double angleOffset = i * ANGLE_STEP - BULLETS_SPREAD_ANGLE;
        Map::instance()->addEntity(
            new Projectile{Transformable::getPosition(),
                           /*bulletRotation*/ Transformable::getRotation() + angleOffset,
                           bulletSpeed,
                           damage * damageMultiplication,
                           bulletHP,
                           "Shootgun_bullet.png"});
    }
}