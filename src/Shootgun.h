#ifndef SHOOTGUN_H
#define SHOOTGUN_H
#include "Weapon.h"

class Shootgun : public Weapon
{
public:
    Shootgun();
private:
    void shoot() override;
    int static const BULLETS_COUNT;
    float static const BULLETS_SPREAD_ANGLE;
    float static const angleStep;
    /* data */
};

#endif