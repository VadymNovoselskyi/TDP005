#include "WeaponsManager.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "AssaultRifleWeapon.h"

WeaponsManager::WeaponsManager() : equipedWeapons{}, unequipedWeapons{}
{
    unequipedWeapons.push_back(AssaultRifleWeapon());
}

void WeaponsManager::resetState()
{
    // Appending vectors taken from
    // https://www.geeksforgeeks.org/cpp/how-to-append-a-vector-to-a-vector-in-cpp/
    unequipedWeapons.insert(unequipedWeapons.end(), equipedWeapons.begin(), equipedWeapons.end());
}

void WeaponsManager::shoot()
{
    for (Weapon w : equipedWeapons)
    {
        w.shoot();
    }
}

void WeaponsManager::setWeaponsPos(sf::Vector2f const &pos)
{
    for (Weapon w : equipedWeapons)
    {
        w.setPosition(pos.x, pos.y);
    }
}

void WeaponsManager::setWeaponsRotation(double rotaiton)
{
    for (Weapon w : equipedWeapons)
    {
        w.setRotation(rotaiton);
    }
}

void WeaponsManager::receiveNewWeapon(std::string const &name)
{
    auto weaponIt = std::find_if(unequipedWeapons.begin(),
                                 unequipedWeapons.end(),
                                 [&name](Weapon w) { return w.getName() == name; });
    equipWeapon(*weaponIt);
}

void WeaponsManager::receiveRandomWeapon()
{
    // random index generator taken from https://en.cppreference.com/w/cpp/numeric/random/rand.html
    if (unequipedWeapons.size() < 1)
    {
        return;
    }

    auto randIndex{std::rand() % unequipedWeapons.size()};
    equipedWeapons.push_back(unequipedWeapons.at(randIndex));
}

void WeaponsManager::equipWeapon(Weapon const &weaponToDelete)
{
    unequipedWeapons.erase(
        std::remove_if(unequipedWeapons.begin(),
                       unequipedWeapons.end(),
                       [&weaponToDelete](Weapon const &weapon)
                       { return weaponToDelete.getName() == weapon.getName(); }));
    equipedWeapons.push_back(weaponToDelete);
}