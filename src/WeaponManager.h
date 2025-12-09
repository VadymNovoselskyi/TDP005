#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include <string>
#include <vector>

#include "Weapon.h"

class WeaponManager
{
  public:
    WeaponManager();
    ~WeaponManager();

    void shoot();
    void setWeaponsPos(sf::Vector2f const &pos);
    void setWeaponsRotation(double rotaiton);

    Weapon *getWeapon(std::string const &name);
    void getNewWeapon();

  private:
    std::vector<Weapon *> activeWeapons;
    std::vector<Weapon *> weapons;
};

#endif