#ifndef PROJECTILEWEAPON_H
#define PROJECTILEWEAPON_H

#include <SFML/Graphics.hpp>
#include "projectile.h"
#include "point.h"

#include <string>

enum Rarity
{
    basic,
    rare,
    epic
}; // https://en.cppreference.com/w/cpp/language/enum.html
// kollade hur ennums funka (kolade på exempel svårt för mig att säga om jag koppiera då de bara
// står exemplet hur man skriver den)

class ProjectileWeapon
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
    void shoot();
    void setPosition(Point &pos);

  protected:
    std::string name;
    std::string description;

    double damage;
    double damageMultiplication;
    sf::Time attackSpeed;
    int lvls;

    Point position;
    Rarity rarity;
    void uppdate();
    std::vector<Projectile*> bullets;
    double speed;
};

#endif