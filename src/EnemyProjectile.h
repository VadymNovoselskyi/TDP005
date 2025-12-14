#ifndef Enemy_PROJECTILE_H
#define Enemy_PROJECTILE_H

#include "Entity.h"

class EnemyProjectile : public Entity
{
  public:
    EnemyProjectile(sf::Vector2f const &pos, double rotation, double velocity, double damage, double hp, std::string pngName);

    void onCollision(Entity *other) override;
    void onBorderCollision() override;

    void move() override;
    void draw(sf::RenderWindow *window) const override;

    void takeDamage(double damage = 1) override;
    void die() override;

  private:
    double velocity;
    double damage;
    sf::Texture const *texture;
};

#endif
