#ifndef SHOOTGUN_H
#define SHOOTGUN_H
#include "Weapon.h"

class Shootgun : public Weapon
{
public:
    Shootgun();
private:
    void shoot() override;
    /* data */
};

#endif