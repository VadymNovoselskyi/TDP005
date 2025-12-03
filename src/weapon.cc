#include "weapon.h"

Weapon::Weapon(std::string name, std::string description, int attackSpeed, int lvls, Point position, Rarity rarity)
    : name{name}, description{description}, attackSpeed{attackSpeed}, lvls{lvls}, position {position}, rarity{rarity}
{

}

void Weapon::setPosition(Point &pos)
{
    position = pos;
}