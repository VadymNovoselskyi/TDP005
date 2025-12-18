#include "WeaponsManager.h"

#include <algorithm>
#include <cstdlib>

#include "AssaultRifle.h"
#include "Shootgun.h"
#include "SniperRifle.h"

WeaponsManager::WeaponsManager() : equipedWeapons{}, unequipedWeapons{}
{
    unequipedWeapons.push_back(new AssaultRifle());
    unequipedWeapons.push_back(new SniperRifle());
    unequipedWeapons.push_back(new Shootgun());
}

void WeaponsManager::resetState()
{
    // Appending vectors taken from
    // https://www.geeksforgeeks.org/cpp/how-to-append-a-vector-to-a-vector-in-cpp/
    unequipedWeapons.insert(unequipedWeapons.end(), equipedWeapons.begin(), equipedWeapons.end());
    equipedWeapons.clear();
}

WeaponsManager::~WeaponsManager()
{
    for (Weapon *w : equipedWeapons)
    {
        delete w;
    }
    for (Weapon *w : unequipedWeapons)
    {
        delete w;
    }
}

void WeaponsManager::shoot()
{
    for (Weapon *w : equipedWeapons)
    {
        w->tryToShoot();
    }
}

void WeaponsManager::setWeaponsPos(sf::Vector2f const &pos)
{
    for (Weapon *w : equipedWeapons)
    {
        w->setPosition(pos.x, pos.y);
    }
}

void WeaponsManager::setWeaponsRotation(double rotaiton)
{
    for (Weapon *w : equipedWeapons)
    {
        w->setRotation(rotaiton);
    }
}

void WeaponsManager::receiveNewWeapon(std::string const &name)
{
    auto weaponIt = std::find_if(unequipedWeapons.begin(),
                                 unequipedWeapons.end(),
                                 [&name](Weapon *w) { return w->getName() == name; });
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
    equipWeapon(unequipedWeapons.at(randIndex));
}

bool WeaponsManager::canGetNewWeapon() const
{
    return unequipedWeapons.size() > 0;
}

void WeaponsManager::equipWeapon(Weapon *weaponToDelete)
{
    unequipedWeapons.erase(
        std::remove_if(unequipedWeapons.begin(),
                       unequipedWeapons.end(),
                       [weaponToDelete](Weapon *weapon)
                       { return weaponToDelete->getName() == weapon->getName(); }),
        unequipedWeapons.end());
    equipedWeapons.push_back(weaponToDelete);
}