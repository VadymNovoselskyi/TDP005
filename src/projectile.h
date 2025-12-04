#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "point.h"
#include <SFML/Graphics.hpp>

class Projectile
{
    public:
    Projectile(Point position, Point direction, double velocity, double damage);
    // void move();

    private:
    Point position; 
    Point direction;
    double velocity;
    double damage;
};

#endif