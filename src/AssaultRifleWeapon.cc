#include "AssaultRifleWeapon.h"

AssaultRifleWeapon::AssaultRifleWeapon()
    : Weapon("AR",
             "Shoot kinda fast with a mediumlow damag",
             /*dmg*/ 5.5f,
             /*attackSpeed in ms*/ sf::milliseconds(100),
             Rarity::BASIC,
             /*bullet speed*/ 20)
{
}