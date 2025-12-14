#ifndef WEAPON_MANAGER_H
#define WEAPON_MANAGER_H

#include <string>
#include <vector>

#include "Weapon.h"

class WeaponsManager
{
  public:
    WeaponsManager();
    ~WeaponsManager();
    void resetState();

    void shoot();
    void setWeaponsPos(sf::Vector2f const &pos);
    void setWeaponsRotation(double rotaiton);

    void receiveNewWeapon(std::string const &name);
    void receiveRandomWeapon();

    bool canGetNewWeapon() const;

  private:
    void equipWeapon(Weapon *weapon);

    std::vector<Weapon *> equipedWeapons;
    std::vector<Weapon *> unequipedWeapons;
};

#endif