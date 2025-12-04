#include "weapon.h"

weapon::weapon(std::string name,
                                   std::string description,
                                   double damage,
                                   double damageMultiplication,
                                   sf::Time attackSpeed,
                                   int lvls,
                                   Point position,
                                   Rarity rarity,
                                   double speed)
    : name{name}, description{description}, damage{damage},
      damageMultiplication{damageMultiplication}, attackSpeed{attackSpeed}, lvls{lvls},
      position{position}, rarity{rarity}, bullets{}, speed{speed}
{
}

void weapon::shoot()
{
    Point dir{0, 0};
    bullets.push_back(new Projectile{position, dir, speed, damage * damageMultiplication});
}

void weapon::setPosition(Point &pos)
{
    position = pos;
}

void weapon::uppdate()
{
    do
    {
        shoot();
        sf::sleep(attackSpeed);
    } while (true);
}
