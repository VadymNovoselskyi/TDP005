#ifndef ASSAULT_RIFLE_H
#define ASSAULT_RIFLE_H
#include "Weapon.h"

/**
 * AssaultRifle
 *
 * AssaultRifle is responsible for:
 * - Shooting projectiles
 */
class AssaultRifle : public Weapon
{
  public:
    /**
     * Construct a AssaultRifle where every varible is set
     */
    AssaultRifle();

  private:
    /**
     * Spawn a projectile
     */
    void shoot() override;
};

#endif