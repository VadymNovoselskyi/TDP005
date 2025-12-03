#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

struct Point
{
    int x;
    int y;
};

class Character
{
  public:
    Character(int width, int height, int maxHP, int currentHp, int movementSpeed, Point positon, Point direction)
    :widht{widht}, height{height}, maxHP{maxHP}, currentHP{currentHP}, movementSpeed{movementSpeed}, position{position}, direction{direction}  {} 
    virtual void move() = 0;
    void takeDamage(int );
    void setDirection(Point);
    Point getDirection();
    void setMovementSpeed(int); 

    protected:
    int widht;
    int height;
    //sf::SDL_Surface* sprite;  -sprite till karaktrer
    int maxHP;
    int currentHP;
    int movementSpeed;
    Point position;
    Point direction;
    virtual void die() = 0;
};

#endif /*CHARACTER_H*/