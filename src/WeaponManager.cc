#include "WeaponManager.h"

#include <algorithm>
#include <iostream>

#include "AssaultRifleWeapon.h"

WeaponManager::WeaponManager() : activeWeapons{}, weapons{}
{
    weapons.push_back(new AssaultRifleWeapon());
}

WeaponManager::~WeaponManager()
{
    for (auto weapon : weapons)
    {
        delete weapon;
    }
}

void WeaponManager::shoot()
{
    for (Weapon *w : activeWeapons)
    {
        w->shoot();
    }
}

void WeaponManager::setWeaponsPos(sf::Vector2f const &pos)
{
    for (Weapon *w : activeWeapons)
    {
        w->setPosition(pos.x, pos.y);
    }
}

Weapon *WeaponManager::getWeapon(std::string const &name)
{
    auto it = std::find_if(activeWeapons.begin(),
                           activeWeapons.end(),
                           [name](Weapon *w) { return w->getName() == name; });
    return *it;
}

void generatWeapon(int number /*0-3*/);
