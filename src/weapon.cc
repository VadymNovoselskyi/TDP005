#include "weapon.h"

Weapon::Weapon(std::string name,
               std::string description,
               double damage,
               double damageMultiplication,
               int attackSpeed,
               int lvls,
               Point position,
               Rarity rarity)
    : name{name}, description{description}, damage{damage},
      damageMultiplication{damageMultiplication}, attackSpeed{attackSpeed}, lvls{lvls},
      position{position}, rarity{rarity}
{
}

void Weapon::setPosition(Point &pos)
{
    position = pos;
}