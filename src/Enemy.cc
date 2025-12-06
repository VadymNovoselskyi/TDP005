#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <unistd.h>
#include <cmath>


Enemy::Enemy(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
        int attackRange, int attackSpeed, int XP_DROP, double damage, int score)
        :Character("enemy" ,maxHP, currentHp, movementSpeed, positon, direction), 
        attackRange{attackRange}, attackSpeed{attackSpeed}, XP_DROP{XP_DROP}, damage{damage}, score{score} {}

// Footman::Footman(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
//             /*Enemy*/int attackRange, int attackSpeed, int XP_DROP, double damage, int score)
//             :Enemy("enemy",maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score){}

// Archer::Archer(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
//             /*Enemy*/int attackRange, int attackSpeed, int XP_DROP, double damage, int score)
//             :Enemy("enemy",maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score){}

// Kaboom::Kaboom(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, Point positon, Point direction,
//             /*Enemy*/int attackRange, int attackSpeed, int XP_DROP, double damage, int score,
//             double explodeDamage, double explodeRange)
//             :Enemy("enemy",maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score),
//             explodeDamage{explodeDamage}, explodeRange{explodeRange}{}

double pythagoras(sf::Vector2f p) // ska vara en point
{
    return sqrt((p.x*p.x)+(p.y*p.y));
}

Enemy::~Enemy() {}

void Enemy::die()
{
    
}

void Enemy::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
    // Draw HP and XP too plz
}



//fnkar inte här me är hur den kan se ut i game.cc
void Enemy::move()
{

    sf::Vector2f figure1 = player -> getPosition();
    sf::Vector2f figure2 = getPosition();
    double const SPEED{5};
    direction.x = 0;
    direction.y = 0;

    //Point player {figure1.getPosition()};
    //Point enemy  {figure2.getPosition()};


    if(figure2.x < figure1.x)
    {
        direction.x += 1;

    }
    if (figure2.x > figure1.x)
    {
        direction.x -= 1;

    }
    
    if(figure2.y < figure1.y)
    {
        direction.y += 1;

    }
    if (figure2.y > figure1.y)
    {
        direction.y -= 1;

    }

    if(std::abs(direction.x) + std::abs(direction.y) > 1)
    {
        direction.x = direction.x / std::sqrt(2);
        direction.y = direction.y / std::sqrt(2);     
    }
    
    sf::Sprite::move(direction.x * SPEED, direction.y * SPEED);
}

std::string Enemy::getTag()
{
    return tag;
}
/*
void Enemy::calcPath(sf::Vector2f player)
{
    
    direction.x = 0;
    direction.y = 0;
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
*/
void Enemy::tryAttack(sf::Vector2f player)
{

    if(pythagoras(player)<= attackRange)
    {
        //Enemy::attack();

    }
    sleep(attackSpeed);//använd timestap istälet
}


/*
bool Kaboom::isInRange(sf::Vector2f player)
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

void Kaboom::explode(sf::Vector2f player)
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
*/