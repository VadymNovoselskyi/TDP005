#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

/**
 * Projectile
 *
 * Projectile is responsible for:
 * - moving
 * - hitting enemys or other objects and interact with them
 */
class Projectile : public Entity
{
  public:
    /**
     * Construct a Projectile and populate it with pos, rotation, velocity, damage, bulletHP and
     * pngName
     *
     * @param pos Position is so it and other know where it is
     * @param rotation is for the sprite so its rotated
     * @param velocity is the projectile speed and make how fast the projectile travel
     * @param damage is how how mutch enemys hit points should drop when hit
     * @param bulletHP is the hit points the bullet has
     * @param pngName is the name of the png
     */
    Projectile(sf::Vector2f const &pos,
               double rotation,
               double velocity,
               double damage,
               double bulletHP,
               std::string const &pngName);

    /**
     * Destroy the Projectile
     */
    ~Projectile() override = default;

    /**
     * Handel all sort of collison when map say that it have collided with other
     *
     * @param other a pointer to a Entity so the can interakt with itch other
     */
    void onCollision(Entity *other) override;

    /**
     * Delet the projectile with map removeEntity
     */
    void onBorderCollision() override;

    /**
     * Move the projectile forward buy calculating rotation to direction
     */
    void move() override;

    /**
     * Take away from hitPoints (hP) with the amount of damage
     *
     * @param damage Damage is how mutch you should take away from hitPoints (hP)
     */
    void takeDamage(double damage = 1) override;

    /**
     * Delet the projectile with map removeEntity
     */
    void die() override;

  private:
    double velocity;
    double damage;
    sf::Texture const *texture;

    bool isDying;
};

#endif
