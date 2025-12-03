#include "Enemy.h"
#include <iostream>

double pythagoras(Point p) // ska vara en point
{
    return sqrt((p.x*p.x)+(p.y*p.y));
}

void Enemy::calcPath()
{
    
}

void Enemy::tryAttack()
{

    if(pythagoras(player)<= attackRange)
    {
        Enemy::attack();

    }
    sleep(attackSpeed);
}



bool Kaboom::isInRange()
{

    if(pythagoras(player)<= attackRange)
    {
        sleep(15);
        Kaboom::explode()

    }
    
}

void Kaboom::increaseSpeed(int newSpeed)
{
    movementSpeed += newSpeed;
}

void Kaboom::explode()
{
    if(pythagoras(player) <= explodeRange)
    {
        player.takeDamage(explodeDamage)
    }
    //explodeRange
    //explodeDamage
    //kaboom die
}