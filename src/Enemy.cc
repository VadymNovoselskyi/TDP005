#include "Enemy.h"

#include <cmath>
#include <iostream>

#include "EnemyProjectile.h"
#include "Highscore.h"
#include "Map.h"

Enemy::Enemy(/*Charactar*/ std::string const& pngName,
             double currentHp,
             int movementSpeed,
             sf::Vector2f positon,
             int attackRange,
             int attackSpeed,
             int const XP_DROP,
             double damage,
             int score,
             Player *player)
    : Character("enemy", currentHp, movementSpeed, positon), pngName{pngName},
      attackRange{attackRange}, attackSpeed{attackSpeed}, count{attackSpeed}, XP_DROP{XP_DROP},
      damage{damage}, score{score}, player{player}, rotation{0}
{
    auto texture{TextureManager::instance()->getTexture(pngName)};
    auto enemySize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(enemySize.x / 2.0f, enemySize.y / 2.0);
}

Footman::Footman(/*Charactar*/
                 std::string const& pngName,
                 double currentHp,
                 int movementSpeed,
                 sf::Vector2f positon,
                 int attackRange,
                 int attackSpeed,
                 int const XP_DROP,
                 double damage,
                 int score,
                 Player *player)
    : Enemy(pngName,
            currentHp,
            movementSpeed,
            positon,
            attackRange,
            attackSpeed,
            XP_DROP,
            damage,
            score,
            player)

{

}

Archer::Archer(/*Charactar*/std::string const& pngName,
               double currentHp,
               int movementSpeed,
               sf::Vector2f positon,
               int attackRange,
               int attackSpeed,
               int const XP_DROP,
               double damage,
               int score,
               Player *player,
               double velocity)
    : Enemy(pngName,
            currentHp,
            movementSpeed,
            positon,
            attackRange,
            attackSpeed,
            XP_DROP,
            damage,
            score,
            player),
      velocity{velocity}
{

}

Kaboom::Kaboom(/*Charactar*/ std::string const& pngName,
               double currentHp,
               int movementSpeed,
               sf::Vector2f positon,
               int attackRange,
               int attackSpeed,
               int const XP_DROP,
               double damage,
               int score,
               Player *player,
               double explodeDamage,
               double explodeRange,
               int explodeCountdown,
               float agroRange)
    : Enemy(pngName,
            currentHp,
            movementSpeed,
            positon,
            attackRange,
            attackSpeed,
            XP_DROP,
            damage,
            score,
            player),
      explodeDamage{explodeDamage}, explodeRange{explodeRange}, explodeCountdown{explodeCountdown},
      agroRange{agroRange}
{
    
}

void Enemy::die()
{

    Map::instance()->removeEntity(this);
    player->gainXp(XP_DROP);
    Highscore::instance()->addKillScore(score);
}

float Enemy::calculateDistance()
{
    oldPosition = getPosition();
    sf::Vector2f playerPositon = player->getPosition();
    sf::Vector2f enemyPosition = oldPosition;

    float directionX = playerPositon.x - enemyPosition.x;
    float directionY = playerPositon.y - enemyPosition.y;

    return std::sqrt((directionX * directionX) + (directionY * directionY));
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
    rotation = rotationRadians * (180.f / M_PI) + 90.f;
    return rotation;
}
void Enemy::collisionHandler(Entity *other)
{
    sf::Vector2f diff = sf::Sprite::getPosition() - other->getPosition();
    float lenDistance = std::sqrt((diff.x * diff.x) + (diff.y * diff.y));
    sf::Vector2f direction;
    if (lenDistance > 0)
    {
        direction = diff / lenDistance;
    }
    else
    {
        direction = sf::Vector2f(0.5F, 0.0F);
    }
    // using a set variable to lower the push force
    float push = other->getGlobalBounds().width / 6.0f;
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
        collisionHandler(other);
    }
    else if (other->getTag() == "enemy")
    {
        collisionHandler(other);
    }
    else if (other->getTag() == "obstacle")
    {
        collisionHandler(this);
        return;
    }
}

void Enemy::onBorderCollision()
{
    sf::Sprite::setPosition(oldPosition);
}

void Enemy::tryAttack(float len)
{
    auto p{player->getTexture()->getSize()};
    auto e{this->getTexture()->getSize()};

    float imageRange{static_cast<float>(attackRange)};
    imageRange += sqrt((p.x / 2) * (p.x / 2) + (p.y / 2) * (p.y / 2)) +
                  sqrt((e.x / 2) * (e.x / 2) + (e.y / 2) * (e.y / 2));

    count--;
    if (len <= imageRange and count <= 0)
    {
        attack();
        count = 600 / attackSpeed;
    }
}

// Footman
void Footman::attack()
{
    player->takeDamage(damage);
}

void Footman::move()
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
    if (explodeCountdown == 0)
    {
        if (len <= explodeRange)
        {
            player->takeDamage(explodeDamage);
        }
        die();
    }
    explodeCountdown--;
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
    shoot();
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
    if (len > attackRange)
    {
        sf::Sprite::setRotation(calculateRotation());
        sf::Sprite::move(direction.x * movementSpeed, direction.y * movementSpeed);
    }
    sf::Sprite::setRotation(calculateRotation());
    tryAttack(len);
}

void Archer::shoot()
{
    Map::instance()->addEntity(new EnemyProjectile{Transformable::getPosition(),
                                                   Transformable::getRotation(),
                                                   velocity,
                                                   damage,
                                                   1,
                                                   "Enemy_bullet.png"});
}