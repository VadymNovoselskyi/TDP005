#include "Weapon.h"

#include <iostream>

#include "Map.h"

Weapon::Weapon(std::string const &name,
               std::string const &description,
               double const &damage,
               double const &attackSpeed,
               Rarity rarity,
               double speed, double bulletHP)
    : name{name}, description{description}, damage{damage}, damageMultiplication{1},
      attackSpeed{attackSpeed}, counter {}, rarity{rarity}, speed{speed}, bulletHP{bulletHP}
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