#ifndef ASSAULT_RIFLE_H
#define ASSAULT_RIFLE_H
#include "Weapon.h"

class AssaultRifleWeapon : public Weapon
{
public:
    AssaultRifleWeapon();
    void shoot() override;
private:
    /* data */
};

#endif