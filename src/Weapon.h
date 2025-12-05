#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "Projectile.h"

#include <string>

enum Rarity
{
    basic,
    rare,
    epic
}; // https://en.cppreference.com/w/cpp/language/enum.html
// kollade hur ennums funka (kolade på exempel svårt för mig att säga om jag koppiera då de bara
// står exemplet hur man skriver den)

class Weapon : public sf::Sprite::Transformable
{
  public:
    Weapon(std::string name,
                     std::string description,
                     double damage,
                     double damageMultiplication,
                     sf::Time attackSpeed,
                     int lvls,
                     Rarity rarity, double speed);
    void shoot();

  protected:
    std::string name;
    std::string description;

    double damage;
    double damageMultiplication;
    sf::Time attackSpeed;
    int lvls;

    Rarity rarity;
    void uppdate();
    std::vector<Projectile*> bullets;
    double speed;
};

#endif