#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <cmath>
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
    /**
     * Construct a Weapon and populate it with name, description, damage, attackSpeed, bulletSpeed,
     * bulletHP and rarity
     *
     * @param name is the way to identify what weapon it is
     * @param description is a litel note of how fast it shoot and witch lvl of dmg it
     * has
     * @param damage is how mutch hp it should take away on what it hit and reakt with
     * @param attackSpeed is how fast it shoot and is count is how many shoots per sec it shoots
     * @param bulletSpeed is how fast the bullet will fly
     * @param bulletHP is how mutch the bullet can take
     * @param rarity is how rare it is to get or a way to know how good it is (rarity system was not
     * made)
     */
    Weapon(std::string const &name,
           std::string const &description,
           double const &damage,
           double const &attackSpeed,
           double bulletSpeed,
           double bulletHP,
           Rarity rarity);

    /**
     * This functions jobb is to count when it can shoot and when it can shoot it will call on shoot
     */
    virtual void tryToShoot();

    /**
     * Return the name of the weapon
     *
     * @return Name of the weapon as a std::string
     */
    std::string getName() const;

  protected:
    std::string name;
    std::string description;

    double damage;
    double damageMultiplication;
    double attackSpeed;
    double bulletSpeed;
    double bulletHP;

    double counter;

    Rarity rarity;

    void update();

  private:
    /**
     * The lower classes implement it but its jobb is to be how de weapon shoot
     */
    virtual void shoot() = 0;
};

#endif