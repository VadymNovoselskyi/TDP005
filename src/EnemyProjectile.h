#ifndef Enemy_PROJECTILE_H
#define Enemy_PROJECTILE_H

#include "Entity.h"
#include "Projectile.h"
/**
 * EnemyProjectile
 *
 * EnemyProjectile is responsible for:
 * - hitting player and interact with them
 */

class EnemyProjectile : public Projectile
{
  public:
    /**
     * Construct a EnemyProjectile that send pos, rotation, velocity, damage, bulletHP and pngName
     * to projektile construct
     *
     * @param pos Position is so it and other know where it is
     * @param rotation is for the sprite so its rotated
     * @param velocity is the projectile speed and make how fast the projectile travel
     * @param damage is how how mutch enemys hit points should drop when hit
     * @param bulletHP is the hit points the bullet has
     * @param pngName is the name of the png
     */

    EnemyProjectile(sf::Vector2f const &pos,
                    double rotation,
                    double velocity,
                    double damage,
                    double hp,
                    std::string pngName);

    /**
     * Handel collison white a player
     *
     * @param other a pointer to a Entity so the can interakt with itch other
     */
    void onCollision(Entity *other) override;

  private:
    double damage;
};

#endif
