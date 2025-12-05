#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"

class Projectile : public Entity
{
  public:
    Projectile(sf::Vector2f pos, double velocity, double damage);
    void onCollision(std::string other) override;

    void move();

  private:
    double velocity;
    double damage;
};

#endif