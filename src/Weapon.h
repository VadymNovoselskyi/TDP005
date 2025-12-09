#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Projectile.h"
#include "Map.h"

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
           sf::Time const &attackSpeed,
           Rarity rarity,
           double speed);
    void shoot();
    std::string getName();

  protected:
    std::string name;
    std::string description;

    double damage;
    double damageMultiplication;
    sf::Time attackSpeed;

    Rarity rarity;
    void uppdate();
    double speed;
};

#endif