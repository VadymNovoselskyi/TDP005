#include "WeaponManager.h"

#include "AssaultRifleWeapon.h"

#include <iostream>

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

WeaponManager::WeaponManager() : weapons {/*Add all weapons here (uniqe weapon class)*/ new AssaultRifleWeapon{}}
{
}