#include "Weapon.h"
#include <iostream>

Weapon::Weapon(std::string const &name,
               std::string const &description,
               double damage,
               sf::Time const &attackSpeed,
               Rarity rarity,
               double speed)
    : name{name}, description{description}, damage{damage}, damageMultiplication{},
      attackSpeed{attackSpeed}, rarity{rarity}, speed{speed}
{
}

void Weapon::shoot()
{
    Map::instance() -> addEntity(new Projectile{Transformable::getPosition(), Transformable::getRotation() , speed, damage * damageMultiplication});
}

std::string Weapon::getName()
{
    return name;
}

void Weapon::uppdate()
{
    do
    {
        shoot();
        sf::sleep(attackSpeed);
    } while (true);
}
