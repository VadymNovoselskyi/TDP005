#include "AssaultRifleWeapon.h"

AssaultRifleWeapon::AssaultRifleWeapon()
    : Weapon("AR",
             "Shoot kinda fast with a medium to low damag",
             /*dmg*/ 12.5f,
             /*attackSpeed in ms*/ sf::milliseconds(100),
             basic,
             /*bullet speed*/ 20)
{
}