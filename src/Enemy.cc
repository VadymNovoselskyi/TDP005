#include "Enemy.h"

#include <cmath>
#include <iostream>

#include "Map.h"
#include "Highscore.h"

Enemy::Enemy(/*Charactar*/ double currentHp,
             int movementSpeed,
             sf::Vector2f positon,
             int attackRange,
             int attackSpeed,
             int XP_DROP,
             double damage,
             int score,
             Player *player)
    : Character("enemy", currentHp, movementSpeed, positon), attackRange{attackRange},
      attackSpeed{attackSpeed}, XP_DROP{XP_DROP}, damage{damage}, score{score}, player{player}
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
    : Enemy(currentHp,
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
               Player *player,
               float fireRange)
    : Enemy(currentHp,
            movementSpeed,
            positon,
            attackRange,
            attackSpeed,
            XP_DROP,
            damage,
            score,
            player),
      fireRange{fireRange}, texture{TextureManager::instance()->getTexture("fighter.png")}
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
               double explodeRange,
               float agroRange)
    : Enemy(currentHp,
            movementSpeed,
            positon,
            attackRange,
            attackSpeed,
            XP_DROP,
            damage,
            score,
            player),
      explodeDamage{explodeDamage}, explodeRange{explodeRange}, agroRange{agroRange},
      texture{TextureManager::instance()->getTexture("obstacle-gas.png")}
{
    auto playerSize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(playerSize.x / 2.0, playerSize.y / 2.0);
}

void Enemy::die()
{
    // ge xp och påeng
    // Map::removeEntity(Entity *this);

    Map::instance()->removeEntity(this);
    player->gainXp(XP_DROP);
    Highscore::instance()->addKillScore(score);
}

void Enemy::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}
float Enemy::calculateDistance()
{
    oldPosition = getPosition();
    sf::Vector2f playerPositon = player->getPosition();
    sf::Vector2f enemyPosition = oldPosition;

    float direction_x = playerPositon.x - enemyPosition.x;
    float direction_y = playerPositon.y - enemyPosition.y;

    return std::sqrt(direction_x * direction_x + direction_y * direction_y);
}
sf::Vector2f Enemy::calculateDirection()
{
    sf::Vector2f playerPositon = player->getPosition();
    sf::Vector2f enemyPosition = getPosition();
    sf::Vector2f directionResult{playerPositon.x - enemyPosition.x,
                                 playerPositon.y - enemyPosition.y};
    return directionResult;
}
float Enemy::calculateRotation()
{
    double rotationRadians = std::atan2((player->getPosition().y - getPosition().y),
                                        (player->getPosition().x - getPosition().x));
    rotation = rotationRadians * (180 / M_PI) + 90;
    return rotation;
}
void Enemy::enemyCollision(Entity *other)
{
    sf::Vector2f diff = sf::Sprite::getPosition() - other->getPosition();
    float lenDistance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    sf::Vector2f direction;
    if (lenDistance > 0)
    {
        direction = diff / lenDistance;
    }
    else
    {
        direction = sf::Vector2f(1.f, 0.f);
    }
    float push = other->getGlobalBounds().width / 6;
    sf::Sprite::setPosition(sf::Sprite::getPosition() + direction * push);
}

std::string Enemy::getTag()
{
    return "enemy";
}

void Enemy::onCollision(Entity *other)
{
    if (other->getTag() == "player")
    {
        // attack();
        enemyCollision(other);
        std::cout << "collided with player" << std::endl;
    }
    else if (other->getTag() == "enemy")
    {
        std::cout << "collided with enemy" << std::endl;
        auto collidingEnemy = static_cast<Enemy *>(other);
        enemyCollision(collidingEnemy);
    }
    else if (other->getTag() == "box")
    {
        std::cout << "collided with box" << std::endl;
        enemyCollision(this);

        return;
    }
}

void Enemy::onBorderCollision()
{
    sf::Sprite::setPosition(oldPosition);
}

void Enemy::tryAttack(float len)
{
    count--;
    if (len <= attackRange and count <= 0)
    {
        attack();
        count = 60 / attackSpeed;
    }
}

// Footman
void Footman::attack()
{
    player->takeDamage(damage);
}

void Footman::move() // skapa en move hjälper
{                    // TODO: calculate rotaiton
    oldPosition = getPosition();
    sf::Vector2f directionResult = calculateDirection();

    sf::Vector2f direction;
    direction.x = 0;
    direction.y = 0;
    float len = calculateDistance();
    if (len != 0)
    {
        direction.x = (directionResult.x / len);
        direction.y = (directionResult.y / len);
    }
    sf::Sprite::setRotation(calculateRotation());
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
    oldPosition = getPosition();
    sf::Vector2f directionResult = calculateDirection();
    sf::Vector2f direction;
    direction.x = 0;
    direction.y = 0;
    float len = calculateDistance();
    if (len != 0)
    {
        direction.x = (directionResult.x / len);
        direction.y = (directionResult.y / len);
    }
    if (len <= agroRange)
    {
        movementSpeed = 8.0;
    }
    sf::Sprite::setRotation(calculateRotation());
    sf::Sprite::move(direction.x * movementSpeed, direction.y * movementSpeed);
    tryAttack(len);
}

void Archer::attack()
{
}
void Archer::move()
{
    oldPosition = getPosition();
    sf::Vector2f directionResult = calculateDirection();

    sf::Vector2f direction;
    direction.x = 0;
    direction.y = 0;
    float len = calculateDistance();
    if (len != 0)
    {
        direction.x = (directionResult.x / len);
        direction.y = (directionResult.y / len);
    }
    if (len > fireRange)
    {
        sf::Sprite::setRotation(calculateRotation());
        sf::Sprite::move(direction.x * movementSpeed, direction.y * movementSpeed);
    }
    tryAttack(len);
}