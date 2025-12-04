#include "projectileWeapon.h"

ProjectileWeapon::ProjectileWeapon(std::string name,
                                   std::string description,
                                   double damage,
                                   double damageMultiplication,
                                   sf::Time attackSpeed,
                                   int lvls,
                                   Point position,
                                   Rarity rarity,
                                   double speed)
    : Weapon(name, description, damage, damageMultiplication, attackSpeed, lvls, position, rarity),
      bullets{}, speed{speed}
{
}

void ProjectileWeapon::shoot()
{
    Point dir{0, 0};
    bullets.push_back(new Projectile{position, dir, speed, 20});
}

void ProjectileWeapon::uppdate()
{
    do
    {
        shoot();
        sf::sleep(attackSpeed);
    } while (true);
}

int main()
{
    return 0;
}