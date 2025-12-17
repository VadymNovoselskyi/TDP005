#ifndef SNIPER_RIFLE_H
#define SNIPER_RIFLE_H
#include "Weapon.h"

class SniperRifle : public Weapon
{
  public:
    SniperRifle();

  private:
    void shoot() override;
};

#endif