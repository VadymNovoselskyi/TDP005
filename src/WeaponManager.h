#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include "Weapon.h"

#include <vector>

class WeaponManager
{
  public: // singelton taget från vadyms kod
    static WeaponManager *instance();
    static WeaponManager *init();
    static void deleteInstance();

  private:
    static WeaponManager *instancePtr;
    WeaponManager();
    ~WeaponManager() = default;

    std::vector<Weapon*> weapons;
};

#endif