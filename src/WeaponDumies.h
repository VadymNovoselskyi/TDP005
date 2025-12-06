#ifndef WEAPONDUMIES_H
#define WEAPONDUMIES_H
#include "Weapon.h"
class WeaponDummie1 : public Weapon
{
    public:
    WeaponDummie1(std::string name,
                     std::string description,
                     double damage,
                     double damageMultiplication,
                     sf::Time attackSpeed,
                     int lvls,
                     Rarity rarity, double speed);

};
class WeaponDummie2 : public Weapon
{
    public:
    WeaponDummie2(std::string name,
                     std::string description,
                     double damage,
                     double damageMultiplication,
                     sf::Time attackSpeed,
                     int lvls,
                     Rarity rarity, double speed);

};
class WeaponDummie3 : public Weapon
{
    public:
    WeaponDummie3(std::string name,
                     std::string description,
                     double damage,
                     double damageMultiplication,
                     sf::Time attackSpeed,
                     int lvls,
                     Rarity rarity, double speed);

};

#endif /*WEAPONDUMIES_H*/
