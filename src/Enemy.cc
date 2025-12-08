#include "Enemy.h"
#include <iostream>
#include <unistd.h>
#include <cmath>


Enemy::Enemy(/*Charactar*/  double maxHP, double currentHp, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
        int attackRange, int attackSpeed, int XP_DROP, double damage, int score, Player* player)
        :Character("enemy" ,maxHP, currentHp, movementSpeed, positon, direction), 
        attackRange{attackRange}, attackSpeed{attackSpeed}, XP_DROP{XP_DROP}, damage{damage}, score{score}, player{player} {}

Footman::Footman(/*Charactar*/ double maxHP, double currentHp, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
        int attackRange, int attackSpeed, int XP_DROP, double damage, int score, Player* player)
            :Enemy(maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score, player){}

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
    float rikting_x = figure1.x - figure2.x;
    float rikting_y = figure1.y - figure2.y;


    float len = std::sqrt(rikting_x * rikting_x + rikting_y + rikting_y);
    direction.x = (rikting_x / len);
    direction.y = (rikting_y / len);

    
    sf::Sprite::move(direction.x * SPEED, direction.y * SPEED);
}

std::string Enemy::getTag()
{
    return tag;
}
void Enemy::onCollision(std::string const &othe)
{
    //attack
}
void Enemy::tryAttack(sf::Vector2f player)
{

    if(pythagoras(player)<= attackRange)
    {
        //Enemy::attack();

    }
    sleep(attackSpeed);//använd timestap istälet
}



// bool Kaboom::isInRange(sf::Vector2f player)
// {

//     if(pythagoras(player)<= attackRange)
//     {
//         sleep(15);
//         Kaboom::explode(player);

//     }
    
// }

// void Kaboom::increaseSpeed(int newSpeed)
// {
//     movementSpeed += newSpeed;
// }

// void Kaboom::explode(sf::Vector2f player)
// {

    
//     if(pythagoras(player) <= explodeRange)
//     {
//        // player.takeDamage(explodeDamage);
//     }
        
//     //explodeRange
//     //explodeDamage
//     //kaboom die
// }

void Footman::attack()
{

}
// void Kaboom::attack()
// {
    
// }
// void Archer::attack()
// {
    
// }
