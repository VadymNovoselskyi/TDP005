#ifndef ASSAULT_RIFLE_H
#define ASSAULT_RIFLE_H
#include "Weapon.h"

class AssaultRifle : public Weapon
{
public:
    AssaultRifle();
    void shoot() override;
private:
    /* data */
};

#endif