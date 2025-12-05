#include "WeaponDumies.h"
WeaponDummie1::WeaponDummie1(std::string name,
                             std::string description,
                             double damage,
                             double damageMultiplication,
                             sf::Time attackSpeed,
                             int lvls,
                             Rarity rarity,
                             double speed)
    : Weapon(name, description,damage, damageMultiplication, attackSpeed, lvls, rarity, speed) {}
WeaponDummie2::WeaponDummie2(std::string name,
                             std::string description,
                             double damage,
                             double damageMultiplication,
                             sf::Time attackSpeed,
                             int lvls,
                             Rarity rarity,
                             double speed)
    : Weapon(name, description,damage, damageMultiplication, attackSpeed, lvls, rarity, speed) {}

WeaponDummie3::WeaponDummie3(std::string name,
                             std::string description,
                             double damage,
                             double damageMultiplication,
                             sf::Time attackSpeed,
                             int lvls,
                             Rarity rarity,
                             double speed)
    : Weapon(name, description,damage, damageMultiplication, attackSpeed, lvls, rarity, speed) {}
