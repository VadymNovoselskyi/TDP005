#include "SniperRifle.h"

#include <iostream>

#include "Map.h"

SniperRifle::SniperRifle()
    : Weapon("Sniper",
             "Shoot slow with a High damag",
             /*dmg*/ 100.0f,
             /*attackSpeed (shoots per sec)*/ 1,
             /*bullet speed*/ 100,
             /*bulletHP*/ 3,
             Rarity::BASIC),
      bulletRotation{}
{
}

void SniperRifle::shoot()
{
    if (Entity *closeEnemy = Map::instance()->getClosestEnemy(); closeEnemy != nullptr)
    {
        // calculateRotation(closeEnemy);
    }

    Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                              /*bulletRotation*/ Transformable::getRotation(),
                                              speed,
                                              damage * damageMultiplication,
                                              bulletHP,
                                              "Sniper_bullet.png"});
}

void SniperRifle::calculateRotation(Entity *closeEnemy)
{
    // detta är taget från classen player fuktionen updateRotation
    double rotationRadians =
        std::atan2(Transformable::getPosition().x - closeEnemy->getPosition().x,
                   Transformable::getPosition().y - closeEnemy->getPosition().y);
    double rotation = rotationRadians * (180 / M_PI); // transform radians to rotation

    std::cout << "enemy " << closeEnemy->getPosition().x << " | " << closeEnemy->getPosition().y
              << std::endl;
    std::cout << "weapon " << closeEnemy->getPosition().x << " | " << Transformable::getPosition().y
              << std::endl;
    bulletRotation = rotation;
    std::cout << rotation << " | " << rotationRadians << std::endl;
}