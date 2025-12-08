#include "Weapon.h"

Weapon::Weapon(std::string const &name,
               std::string const &description,
               double damage,
               double damageMultiplication,
               sf::Time const &attackSpeed,
               int lvls,
               Rarity rarity,
               double speed)
    : name{name}, description{description}, damage{damage},
      damageMultiplication{damageMultiplication}, lvls{lvls}, speed{speed},
      attackSpeed{attackSpeed}, rarity{rarity}, bullets{}
{
}

void Weapon::shoot()
{
    bullets.push_back(
        new Projectile{Transformable::getPosition(), speed, damage * damageMultiplication});
    bullets.back()->setRotation(Transformable::getRotation());
    bullets.back()->move();
}

void Weapon::update()
{
    do
    {
        shoot();
        sf::sleep(attackSpeed);
    } while (true);
}
