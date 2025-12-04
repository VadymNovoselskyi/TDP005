#ifndef WEAPON_H
#define WEAPON_H

#include "point.h"
#include <SFML/Graphics.hpp>
#include <string>

enum Rarity
{
    basic,
    rare,
    epic
}; // https://en.cppreference.com/w/cpp/language/enum.html
// kollade hur ennums funka (kolade på exempel svårt för mig att säga om jag koppiera då de bara
// står exemplet hur man skriver den)

class Weapon
{
  public:
    Weapon(std::string name,
           std::string description,
           double damage,
           double damageMultiplication,
           sf::Time attackSpeed,
           int lvls,
           Point position,
           Rarity rarity);

    virtual ~Weapon() = default;

    virtual void shoot() = 0;
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
};

#endif