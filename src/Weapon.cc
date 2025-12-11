#include "Weapon.h"

#include <iostream>

#include "Map.h"

Weapon::Weapon(std::string const &name,
               std::string const &description,
               double const &damage,
               double const &attackSpeed,
               Rarity rarity,
               double speed)
    : name{name}, description{description}, damage{damage}, damageMultiplication{1},
      attackSpeed{attackSpeed}, rarity{rarity}, speed{speed}, counter {}
{
}

void Weapon::tryToShoot()
{
    counter--;
    if (counter <= 0)
    {
        shoot();
        counter = 60 / attackSpeed;
    }
}

std::string Weapon::getName() const
{
    return name;
}