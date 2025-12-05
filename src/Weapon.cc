#include "Weapon.h"

Weapon::Weapon(std::string name,
                                   std::string description,
                                   double damage,
                                   double damageMultiplication,
                                   sf::Time attackSpeed,
                                   int lvls,
                                   Rarity rarity,
                                   double speed)
    : name{name}, description{description}, damage{damage},
      damageMultiplication{damageMultiplication}, attackSpeed{attackSpeed}, lvls{lvls}, rarity{rarity}, bullets{}, speed{speed}
{
}

void Weapon::shoot()
{
    bullets.push_back(new Projectile{Transformable::getPosition(), speed, damage * damageMultiplication});
    bullets.back()->setRotation(Transformable::getRotation());
    bullets.back()->move();
}

void Weapon::uppdate()
{
    do
    {
        shoot();
        sf::sleep(attackSpeed);
    } while (true);
}
