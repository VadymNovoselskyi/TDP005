#ifndef SHOOTGUN_H
#define SHOOTGUN_H
#include "Weapon.h"

/**
 * Shootgun
 *
 * Shootgun is responsible for:
 * - Shooting projectiles
 */
class Shootgun : public Weapon
{
  public:
    /**
     * Construct a Shootgun where every varible is set
     */
    Shootgun();

  private:
    /**
     * Spawn a serten amount of projectiles with diffrent rotation
     */
    void shoot() override;
    int static const BULLETS_COUNT;
    float static const BULLETS_SPREAD_ANGLE;
    float static const ANGLE_STEP;
    /* data */
};

#endif