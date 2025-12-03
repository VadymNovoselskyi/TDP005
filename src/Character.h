#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

struct Point
{
    double x;
    double y;
};

class Character
{
  public:
    Character(double maxHP, double currentHp, int movementSpeed, Point positon, Point direction)
    :maxHP{maxHP}, currentHP{currentHP}, movementSpeed{movementSpeed}, position{position}, direction{direction}  {} 
    virtual void move() = 0;
    void takeDamage(int );
    void setDirection(Point);
    Point getDirection();
    void setMovementSpeed(int); 

    protected:
    //sf::SDL_Surface* sprite;  -sprite till karaktrer
    double maxHP;
    double currentHP;
    int movementSpeed;
    Point position;
    Point direction;
    virtual void die() = 0;
};

#endif /*CHARACTER_H*/