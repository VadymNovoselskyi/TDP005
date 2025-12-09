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
            :Enemy(maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score, player),
            texture{TextureManager::instance()->getTexture("enemy.png")}        
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
}

Archer::Archer(/*Charactar*/ double maxHP, double currentHp, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
        int attackRange, int attackSpeed, int XP_DROP, double damage, int score, Player* player)
            :Enemy(maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score, player),
            texture{TextureManager::instance()->getTexture("enemy.png")}        
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
}

Kaboom::Kaboom(/*Charactar*/ double maxHP, double currentHp, int movementSpeed, sf::Vector2f positon, sf::Vector2f direction,
        int attackRange, int attackSpeed, int XP_DROP, double damage, int score, Player* player,
            double explodeDamage, double explodeRange)
            :Enemy(maxHP, currentHp, movementSpeed, positon, direction, attackRange, attackSpeed, XP_DROP, damage, score, player),
            explodeDamage{explodeDamage}, explodeRange{explodeRange},
            texture{TextureManager::instance()->getTexture("enemy.png")}        
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
}

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

std::string Enemy::getTag()
{
    return tag;
}
void Enemy::onCollision(std::string const &other)
{
    if (other == "player")
    {
        attack();
    }

}
void Enemy::tryAttack(float len)
{

    if(len <= attackRange)
    {
        attack();
        sleep(attackSpeed);//använd timestap istälet
    }
    
}

//Footman
void Footman::attack()
{
    player -> takeDamage(damage);
}

void Footman::move()
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


    float len = std::sqrt(rikting_x * rikting_x + rikting_y * rikting_y);
    if(len != 0)
    {
        direction.x = (rikting_x / len);
        direction.y = (rikting_y / len);
    }
    
    sf::Sprite::move(direction.x * SPEED, direction.y * SPEED);
    tryAttack(len);

}

//kaboom
bool Kaboom::isInRange(float len)
{

    if(len <= attackRange)
    {
        sleep(15);
        Kaboom::explode(len);

    }
    
}



void Kaboom::explode(float len)
{

    
    if(len <= explodeRange)
    {
       player -> takeDamage(explodeDamage);
    }
    die();
    //explodeRange
    //explodeDamage
    //kaboom die
}

void Kaboom::attack()
{
    player -> takeDamage(damage);
}
void Kaboom::move()
{

    sf::Vector2f figure1 = player -> getPosition();
    sf::Vector2f figure2 = getPosition();
    double SPEED{5};
    direction.x = 0;
    direction.y = 0;
 

    //Point player {figure1.getPosition()};
    //Point enemy  {figure2.getPosition()};
    float rikting_x = figure1.x - figure2.x;
    float rikting_y = figure1.y - figure2.y;


    float len = std::sqrt(rikting_x * rikting_x + rikting_y * rikting_y);
    if(len != 0)
    {
        direction.x = (rikting_x / len);
        direction.y = (rikting_y / len);
    }
    if(len <= 300)
    {
        SPEED = 10.0;
    }
    
    sf::Sprite::move(direction.x * SPEED, direction.y * SPEED);
    tryAttack(len);
}



void Archer::attack()
{
    
}
void Archer::move()
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


    float len = std::sqrt(rikting_x * rikting_x + rikting_y * rikting_y);
    if(len != 0)
    {
        direction.x = (rikting_x / len);
        direction.y = (rikting_y / len);
    }
    if(len > 500)
    {
        sf::Sprite::move(direction.x * SPEED, direction.y * SPEED);
    }
    tryAttack(len);
}