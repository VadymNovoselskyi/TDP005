#include "WeaponManager.h"

#include <algorithm>
#include <iostream>

#include "AssaultRifle.h"

WeaponManager::WeaponManager() : activeWeapons{}, weapons{}
{
    weapons.push_back(new AssaultRifle());
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
        w->fire();
    }
}

void WeaponManager::setWeaponsPos(sf::Vector2f const &pos)
{
    for (Weapon *w : activeWeapons)
    {
        w->setPosition(pos.x, pos.y);
    }
}

void WeaponManager::setWeaponsRotation(double rotaiton)
{
    for (Weapon *w : activeWeapons)
    {
        w->setRotation(rotaiton);
    }
}

Weapon *WeaponManager::getWeapon(std::string const &name)
{
    auto weapon = std::find_if(activeWeapons.begin(),
                               activeWeapons.end(),
                               [name](Weapon *w) { return w->getName() == name; });
    return *weapon;
}

void WeaponManager::receiveNewWeapon(std::string const &name)
{
    auto weapon = std::find_if(
        weapons.begin(), weapons.end(), [name](Weapon *w) { return w->getName() == name; });
    activeWeapons.push_back(*weapon);
}