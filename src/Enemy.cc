#include "Enemy.h"

#include <cmath>
#include <iostream>
#include <unistd.h>

#include "Map.h"

Enemy::Enemy(/*Charactar*/ double currentHp,
             int movementSpeed,
             sf::Vector2f positon,
             int attackRange,
             int attackSpeed,
             int XP_DROP,
             double damage,
             int score,
             Player *player)
    : Character("enemy", currentHp, movementSpeed, positon),
      attackRange{attackRange}, attackSpeed{attackSpeed}, XP_DROP{XP_DROP}, damage{damage},
      score{score}, player{player}
{
}

Footman::Footman(/*Charactar*/
                 double currentHp,
                 int movementSpeed,
                 sf::Vector2f positon,
                 int attackRange,
                 int attackSpeed,
                 int XP_DROP,
                 double damage,
                 int score,
                 Player *player)
    : Enemy(
            currentHp,
            movementSpeed,
            positon,
            attackRange,
            attackSpeed,
            XP_DROP,
            damage,
            score,
            player),
      texture{TextureManager::instance()->getTexture("enemy.png")}
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
}

Archer::Archer(/*Charactar*/ 
               double currentHp,
               int movementSpeed,
               sf::Vector2f positon,
               int attackRange,
               int attackSpeed,
               int XP_DROP,
               double damage,
               int score,
               Player *player)
    : Enemy(
            currentHp,
            movementSpeed,
            positon,
            attackRange,
            attackSpeed,
            XP_DROP,
            damage,
            score,
            player),
      texture{TextureManager::instance()->getTexture("enemy.png")}
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
}

Kaboom::Kaboom(/*Charactar*/
               double currentHp,
               int movementSpeed,
               sf::Vector2f positon,
               int attackRange,
               int attackSpeed,
               int XP_DROP,
               double damage,
               int score,
               Player *player,
               double explodeDamage,
               double explodeRange)
    : Enemy(
            currentHp,
            movementSpeed,
            positon,
            attackRange,
            attackSpeed,
            XP_DROP,
            damage,
            score,
            player),
      explodeDamage{explodeDamage}, explodeRange{explodeRange},
      texture{TextureManager::instance()->getTexture("obstacle-gas.png")}
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
}

double pythagoras(sf::Vector2f p) // ska vara en point
{
    return sqrt((p.x * p.x) + (p.y * p.y));
}

Enemy::~Enemy()
{
}

void Enemy::die()
{
    // ge xp och påeng
    // Map::removeEntity(Entity *this);
}

void Enemy::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}
void Enemy::moveHelper()
{
    
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
    if (len <= attackRange)
    {
        attack();
        // sleep(attackSpeed);//använd timestap istälet
    }
}

// Footman
void Footman::attack()
{
    player->takeDamage(damage);
}

void Footman::move() // skapa en move hjälper 
{
    sf::Vector2f playerPositon = player->getPosition();
    sf::Vector2f enemyPosition = getPosition();
    sf::Vector2f direction;
    direction.x = 0;
    direction.y = 0;

    // Point player {figure1.getPosition()};
    // Point enemy  {figure2.getPosition()};
    float direction_x = playerPositon.x - enemyPosition.x;
    float direction_y = playerPositon.y - enemyPosition.y;

    float len = std::sqrt(direction_x * direction_x + direction_y* direction_y);
    if (len != 0)
    {
        direction.x = (direction_x / len);
        direction.y = (direction_y/ len);
    }

    sf::Sprite::move(direction.x * movementSpeed, direction.y * movementSpeed);
    tryAttack(len);
}

// kaboom
void Kaboom::isInRange(float len)
{
    if (len <= attackRange)
    {
        // sleep(15);
        Kaboom::explode(len);
    }
}

void Kaboom::explode(float len)
{
    if (len <= explodeRange)
    {
        player->takeDamage(explodeDamage);
    }
    die();
    // explodeRange
    // explodeDamage
    // kaboom die
}

void Kaboom::attack()
{
    player->takeDamage(damage);
}
void Kaboom::move()
{
    sf::Vector2f figure1 = player->getPosition();
    sf::Vector2f figure2 = getPosition();
    sf::Vector2f direction;
    direction.x = 0;
    direction.y = 0;

    // Point player {figure1.getPosition()};
    // Point enemy  {figure2.getPosition()};
    float direction_x = figure1.x - figure2.x;
    float direction_y = figure1.y - figure2.y;

    float len = std::sqrt(direction_x * direction_x + direction_y * direction_y);
    if (len != 0)
    {
        direction.x = (direction_x / len);
        direction.y = (direction_y / len);
    }
    if (len <= 300)
    {
        movementSpeed = 10.0;
    }

    sf::Sprite::move(direction.x * movementSpeed, direction.y * movementSpeed);
    tryAttack(len);
}

void Archer::attack()
{
}
void Archer::move()
{
    sf::Vector2f figure1 = player->getPosition();
    sf::Vector2f figure2 = getPosition();
    sf::Vector2f direction;
    direction.x = 0;
    direction.y = 0;

    float direction_x = figure1.x - figure2.x;
    float direction_y = figure1.y - figure2.y;

    float len = std::sqrt(direction_x * direction_x + direction_y * direction_y);
    if (len != 0)
    {
        direction.x = (direction_x / len);
        direction.y = (direction_y / len);
    }
    if (len > 500)
    {
        sf::Sprite::move(direction.x * movementSpeed, direction.y * movementSpeed);
    }
    tryAttack(len);
}
