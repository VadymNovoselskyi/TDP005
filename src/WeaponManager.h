#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include "Weapon.h"

#include <vector>
#include <string>

class WeaponManager
{
  public: // singelton taget från vadyms kod
    static WeaponManager *instance();
    static WeaponManager *init();
    static void deleteInstance();

    void shoot();
    void setWeaponsPos(sf::Vector2f pos);
    void setWeaponsRotation(double rotaiton);
    Weapon* getWeapon(std::string const &name);
    void generatWeapon(int number /*0-3*/);

  private:
    static WeaponManager *instancePtr;
    WeaponManager();
    ~WeaponManager() = default;

    std::vector<Weapon*> weapons;
    std::vector<Weapon*> activWeapons;
};

#endif