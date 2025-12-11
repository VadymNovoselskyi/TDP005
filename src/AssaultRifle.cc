#include "AssaultRifle.h"

#include "Map.h"

AssaultRifle::AssaultRifle()
    : Weapon("AR",
             "Shoot kinda fast with a mediumlow damag",
             /*dmg*/ 7.5f,
             /*attackSpeed (shoots per sec)*/ 10,
             Rarity::BASIC,
             /*bullet speed*/ 80)
{
}
void AssaultRifle::tryToShoot()
{
    counter--;
    if (counter <= 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        shoot();
        counter = 60 / attackSpeed;
    }
}

void AssaultRifle::shoot()
{
    Map::instance()->addEntity(new Projectile{Transformable::getPosition(),
                                              Transformable::getRotation(),
                                              speed,
                                              damage * damageMultiplication, 1});
}