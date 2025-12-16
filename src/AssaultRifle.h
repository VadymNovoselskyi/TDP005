#ifndef ASSAULT_RIFLE_H
#define ASSAULT_RIFLE_H
#include "Weapon.h"

class AssaultRifle : public Weapon
{
public:
    AssaultRifle();
    
private:
    void shoot() override;
    /* data */
};

#endif