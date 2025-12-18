#include "Weapon.h"
#include "GameEngine.h"

#include <iostream>

Weapon::Weapon(std::string const &name,
               std::string const &description,
               double const &damage,
               double const &attackSpeed,
               double bulletSpeed,
               double bulletHP,
               Rarity rarity)
    : name{name}, description{description}, damage{damage}, damageMultiplication{1},
      attackSpeed{attackSpeed}, bulletSpeed{bulletSpeed}, bulletHP{bulletHP}, counter{}, rarity{rarity}
{
}

void Weapon::tryToShoot()
{
    counter--;
    if (counter <= 0)
    {
        shoot();
        counter =  GameEngine::FPS / attackSpeed;
    }
}

std::string Weapon::getName() const
{
    return name;
}