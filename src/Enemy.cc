#include "Enemy.h"
#include <iostream>
#include <unistd.h>
#include <cmath>

Enemy::Enemy(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
        int attackRange, int attackSpeed, int XP_DROP, double damage, int score)
        :Character(maxHP, currentHp, movementSpeed, positon, direction), 
        attackRange{attackRange}, attackSpeed{attackSpeed}, XP_DROP{XP_DROP}, damage{damage}, score{score} {}

Footman::Footman(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
            /*Enemy*/int attackRange, int attackSpeed, int XP_DROP, double damage, int score)
            :Enemy(maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score){}

Archer::Archer(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
            /*Enemy*/int attackRange, int attackSpeed, int XP_DROP, double damage, int score)
            :Enemy(maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score){}

Kaboom::Kaboom(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
            /*Enemy*/int attackRange, int attackSpeed, int XP_DROP, double damage, int score,
            double explodeDamage, double explodeRange)
            :Enemy(maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score),
            explodeDamage{explodeDamage}, explodeRange{explodeRange}{}

double pythagoras(Point p) // ska vara en point
{
    return sqrt((p.x*p.x)+(p.y*p.y));
}

Enemy::~Enemy() {}

void Enemy::die()
{
    
}

//fnkar inte här me är hur den kan se ut i game.cc
void Enemy::move(sf::Sprite &figure1, sf::CircleShape &figure2)
{
    double const SPEED{5};
    Point new_direction{0,0};
    //Point player {figure1.getPosition()};
    //Point enemy  {figure2.getPosition()};


    if(figure2.getPosition().x < figure1.getPosition().x)
    {
        new_direction.x += 1;

    }
    if (figure2.getPosition().x > figure1.getPosition().x)
    {
        new_direction.x -= 1;

    }
    
    if(figure2.getPosition().y < figure1.getPosition().y)
    {
        new_direction.y += 1;

    }
    if (figure2.getPosition().y > figure1.getPosition().y)
    {
        new_direction.y -= 1;

    }

    if(std::abs(new_direction.x) + std::abs(new_direction.y) > 1)
    {
        new_direction.x = new_direction.x / std::sqrt(2);
        new_direction.y = new_direction.y / std::sqrt(2);     
    }
    
    figure2.move(sf::Vector2f(new_direction.x * SPEED, new_direction.y * SPEED));
}

std::string Enemy::getTag()
{
    return tag;
}

void Enemy::calcPath(Point player)
{
    Point new_direction{0,0};
    /*första disig*/
    if(position.x < player.x)
    {
        new_direction.x += 1;
    }
    else if (position.x > player.x)
    {
        new_direction.x -= 1;
    }
    
    if(position.y < player.y)
    {
        new_direction.y += 1;
    }
    else if (position.y > player.y)
    {
        new_direction.y -= 1;
    }

    if(std::abs(new_direction.x) + std::abs(new_direction.y) > 1)
    {
        new_direction.x = new_direction.x / std::sqrt(2);
        new_direction.y = new_direction.y / std::sqrt(2);     
    }

    setDirection(new_position);
}

void Enemy::tryAttack(Point player)
{

    if(pythagoras(player)<= attackRange)
    {
        //Enemy::attack();

    }
    sleep(attackSpeed);//använd timestap istälet
}



bool Kaboom::isInRange(Point player)
{

    if(pythagoras(player)<= attackRange)
    {
        sleep(15);
        Kaboom::explode(player);

    }
    
}

void Kaboom::increaseSpeed(int newSpeed)
{
    movementSpeed += newSpeed;
}

void Kaboom::explode(Point player)
{

    
    if(pythagoras(player) <= explodeRange)
    {
       // player.takeDamage(explodeDamage);
    }
        
    //explodeRange
    //explodeDamage
    //kaboom die
}

void Footman::attack()
{

}
void Kaboom::attack()
{
    
}
void Archer::attack()
{
    
}