#include "SniperRifle.h"

#include "Map.h"

#include <iostream>

SniperRifle::SniperRifle()
    : Weapon("Sniper",
             "Shoot slow with a High damag",
             /*dmg*/ 100.0f,
             /*attackSpeed (shoots per sec)*/ 1,
             /*bullet speed*/ 30,
             /*bulletHP*/ 2,
             Rarity::BASIC),
      bulletRotation{}
{
}

void SniperRifle::shoot()
{
    if (Entity *closeEnemy = Map::instance()->getClosestEnemy(); closeEnemy != nullptr)
    {
        //calculateRotation(closeEnemy);

        Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                                  /*bulletRotation*/ Transformable::getRotation(),
                                                  speed,
                                                  damage * damageMultiplication,
                                                  bulletHP,
                                                  "Sniper_bullet.png"});
    }
}

void SniperRifle::calculateRotation(Entity *closeEnemy)
{
    // detta är taget från classen player fuktionen updateRotation
    double rotationRadians = std::atan2((closeEnemy->getPosition().x - Transformable::getPosition().x), closeEnemy->getPosition().y - Transformable::getPosition().y);
    double rotation = rotationRadians ; // transform radians to rotation
    
    std::cout << "enemy "<< closeEnemy->getPosition().x << " | "<< closeEnemy->getPosition().y << std::endl;
    std::cout << "weapon "<< closeEnemy->getPosition().x << " | "<< Transformable::getPosition().y << std::endl;
    bulletRotation = rotation;
    std::cout << rotation << " | "<< rotationRadians << std::endl;
}