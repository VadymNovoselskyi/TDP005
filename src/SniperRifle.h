#ifndef SNIPER_RIFLE_H
#define SNIPER_RIFLE_H
#include "Weapon.h"

/**
 * SniperRifle
 *
 * SniperRifle is responsible for:
 * - Shooting projectiles
 */
class SniperRifle : public Weapon
{
  public:
    /**
     * Construct a SniperRifle where every varible is set
     */
    SniperRifle();

  private:
    /**
     * Spawn a projectile
     */
    void shoot() override;
};

#endif