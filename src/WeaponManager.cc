#include "WeaponManager.h"

#include "AssaultRifleWeapon.h"

#include <iostream>
#include <algorithm>

WeaponManager *WeaponManager::instancePtr{nullptr};

// Static methods:
WeaponManager *WeaponManager::instance()
{
    if (WeaponManager::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init WeaponManager before calling instance on it");
    }
    return WeaponManager::instancePtr;
}

WeaponManager *WeaponManager::init()
{
    WeaponManager::instancePtr = new WeaponManager();
    return WeaponManager::instancePtr;
}

void WeaponManager::deleteInstance()
{
    // std::cout << "Deleting the instance" << std::endl;
    delete WeaponManager::instancePtr;
    WeaponManager::instancePtr = nullptr;
}

void WeaponManager::shoot()
{
    for (Weapon* w : activWeapons)
    {
        w -> shoot();
    }
}


void WeaponManager::setWeaponsPos(sf::Vector2f pos)
{
    for (Weapon* w : activWeapons)
    {
        w -> setPosition(pos.x, pos.y);
    }
}

void WeaponManager::setWeaponsRotation(double rotaiton)
{
    for (Weapon* w : activWeapons)
    {
        w -> setRotation(rotaiton);
    }
}

Weapon* WeaponManager::getWeapon(std::string const &name)
{
    auto it = std::find_if(activWeapons.begin(), activWeapons.end(), [name](Weapon* w)
    {
        return w -> getName() == name;
    });
    return *it;

}

void generatWeapon(int number /*0-3*/);

WeaponManager::WeaponManager() : weapons {/*Add all weapons here (uniqe weapon class)*/ new AssaultRifleWeapon{}}, activWeapons {new AssaultRifleWeapon{}}
{
}