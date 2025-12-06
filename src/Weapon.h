#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Projectile.h"

enum Rarity
{
    BASIC,
    RARE,
    EPIC
};
// https://en.cppreference.com/w/cpp/language/enum.html
// kollade hur ennums funka (kolade på exempel svårt för mig att säga om jag koppiera då de bara
// står exemplet hur man skriver den)

class Weapon : public sf::Sprite::Transformable
{
  public:
    Weapon(std::string const &name,
           std::string const &description,
           double damage,
           double damageMultiplication,
           sf::Time const &attackSpeed,
           int lvls,
           Rarity rarity,
           double speed);
    void shoot();

  protected:
    std::string name;
    std::string description;

    double damage;
    double damageMultiplication;
    int lvls;
    double speed;
    sf::Time attackSpeed;

    Rarity rarity;
    std::vector<Projectile *> bullets;

    void update();
};

#endif