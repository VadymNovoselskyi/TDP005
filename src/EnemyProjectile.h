#ifndef Enemy_PROJECTILE_H
#define Enemy_PROJECTILE_H

#include "Entity.h"
#include "Projectile.h"

class EnemyProjectile : public Projectile
{
  public:
    EnemyProjectile(sf::Vector2f const &pos, double rotation, double velocity, double damage, double hp, std::string pngName);
    ~EnemyProjectile() = default;

    void onCollision(Entity *other) override;
    // void onBorderCollision() override;

    // void move() override;
    // void draw(sf::RenderWindow *window) const override;

    // void takeDamage(double damage = 1);
    // void die() override;

  private:
    // double velocity;
    double damage;
    // sf::Texture const *texture;
};

#endif
