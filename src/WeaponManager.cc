#include "WeaponManager.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "AssaultRifleWeapon.h"

WeaponManager::WeaponManager() : equipedWeapons{}, unequipedWeapons{}
{
    unequipedWeapons.push_back(new AssaultRifleWeapon());
}

WeaponManager::~WeaponManager()
{
    for (auto weapon : equipedWeapons)
    {
        delete weapon;
    }

    for (auto weapon : unequipedWeapons)
    {
        delete weapon;
    }
}

void WeaponManager::shoot()
{
    for (Weapon *w : equipedWeapons)
    {
        w->shoot();
    }
}

void WeaponManager::setWeaponsPos(sf::Vector2f const &pos)
{
    for (Weapon *w : equipedWeapons)
    {
        w->setPosition(pos.x, pos.y);
    }
}

void WeaponManager::setWeaponsRotation(double rotaiton)
{
    for (Weapon *w : equipedWeapons)
    {
        w->setRotation(rotaiton);
    }
}

Weapon *WeaponManager::getWeapon(std::string const &name)
{
    auto weapon = std::find_if(equipedWeapons.begin(),
                               equipedWeapons.end(),
                               [&name](Weapon *w) { return w->getName() == name; });
    return *weapon;
}

void WeaponManager::receiveNewWeapon(std::string const &name)
{
    auto weaponIt = std::find_if(unequipedWeapons.begin(),
                                 unequipedWeapons.end(),
                                 [&name](Weapon *w) { return w->getName() == name; });
    equipWeapon(*weaponIt);
}

void WeaponManager::receiveRandomWeapon()
{
    // random index generator taken from https://en.cppreference.com/w/cpp/numeric/random/rand.html
    if (unequipedWeapons.size() < 1)
    {
        return;
    }

    auto randIndex{std::rand() % unequipedWeapons.size()};
    equipedWeapons.push_back(unequipedWeapons.at(randIndex));
}

void WeaponManager::equipWeapon(Weapon *weapon)
{
    unequipedWeapons.erase(std::remove(unequipedWeapons.begin(), unequipedWeapons.end(), weapon));
    equipedWeapons.push_back(weapon);
}