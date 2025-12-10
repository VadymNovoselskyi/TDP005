#ifndef ASSAULT_RIFLE_H
#define ASSAULT_RIFLE_H
#include "Weapon.h"

class AssaultRifle : public Weapon
{
public:
    AssaultRifle();
    void tryToShoot() override;
    
private:
    void shoot() override;
    /* data */
};

#endif