#ifndef Enemy_PROJECTILE_H
#define Enemy_PROJECTILE_H

#include "Entity.h"
#include "Projectile.h"

class EnemyProjectile : public Projectile
{
  public:
    EnemyProjectile(sf::Vector2f const &pos,
                    double rotation,
                    double velocity,
                    double damage,
                    double hp,
                    std::string pngName);

    void onCollision(Entity *other) override;

  private:
    double damage;
};

#endif
