#include "Player.h"
Player::Player(int maxHp,
               int currentHp,
               int movementSpeed,
               Point positon,
               Point direction,
               std::string name,
               int xp,
               int maxXp,
               int levels,
               double damageMultipplyer)
    : Character(maxHP, currentHp, movementSpeed, positon, direction), name{name}, xp{xp},
      levels{levels}, damageMultipplyer{damageMultipplyer}
{
}

void Player::setXP(int gainedXP)
{
    xp += gainedXP;
    if (xp <= maxXp)
    {
      xp =- maxXp;
      maxXp += 100; // variabel för ökning + räkn med* - avrunda
      levelUp();
    }

}
void Player::levelUp()
{
  
}