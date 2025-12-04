#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"

class Projectile : public Entity
{
  public:
    Projectile(Point position, Point direction, double velocity, double damage);
    void onCollistion(std::string other) override;
    void move();

  private:
    Point direction;
    double velocity;
    double damage;
};

#endif