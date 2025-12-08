#include "Weapon.h"

Weapon::Weapon(std::string const &name,
               std::string const &description,
               double damage,
               sf::Time const &attackSpeed,
               Rarity rarity,
               double speed)
    : name{name}, description{description}, damage{damage}, damageMultiplication{},
      attackSpeed{attackSpeed}, rarity{rarity}, bullets{}, speed{speed}
{
}

void Weapon::shoot()
{
    bullets.push_back(
        new Projectile{Transformable::getPosition(), speed, damage * damageMultiplication});
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
