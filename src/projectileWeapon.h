#ifndef PROJECTILEWEAPON_H
#define PROJECTILEWEAPON_H

#include <SFML/Graphics.hpp>

#include "weapon.h"
#include "projectile.h"

class ProjectileWeapon : public Weapon
{
  public:
    ProjectileWeapon(std::string name,
                     std::string description,
                     double damage,
                     double damageMultiplication,
                     sf::Time attackSpeed,
                     int lvls,
                     Point position,
                     Rarity rarity, double speed);
    void shoot() override;

  private:
    void uppdate();
    std::vector<Projectile*> bullets;
    double speed;
};

#endif