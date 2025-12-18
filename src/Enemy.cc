#include "Enemy.h"

#include <cmath>

#include "EnemyProjectile.h"
#include "Highscore.h"
#include "Map.h"

Enemy::Enemy(/*Charactar*/ std::string const &pngName,
             double currentHp,
             int movementSpeed,
             sf::Vector2f positon,
             int attackRange,
             int attackSpeed,
             int const XP_DROP,
             double damage,
             int score,
             Player *player)
    : Character("enemy", currentHp, movementSpeed, positon), attackRange{attackRange},
      attackSpeed{attackSpeed}, count{attackSpeed}, XP_DROP{XP_DROP}, damage{damage}, score{score},
      player{player}, rotation{0}, pngName{pngName}
{
    auto texture{TextureManager::instance()->getTexture(pngName)};
    auto enemySize{texture->getSize()};
    sf::Sprite::setTexture(*texture);
    sf::Sprite::setOrigin(enemySize.x / 2.0f, enemySize.y / 2.0);
}

Footman::Footman(/*Charactar*/
                 std::string const &pngName,
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

Archer::Archer(/*Charactar*/ std::string const &pngName,
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

Kaboom::Kaboom(/*Charactar*/ std::string const &pngName,
               double currentHp,
               int movementSpeed,
               sf::Vector2f positon,
               int attackRange,
               int attackSpeed,
               int const XP_DROP,
               double damage,
               int score,
               Player *player,
               double exploadeDamage,
               double exploadeRange,
               int exploadeCountdown,
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
      explosionDamage{exploadeDamage}, explosionRange{exploadeRange},
      explosionCountdown{exploadeCountdown}, agroRange{agroRange}
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
    sf::Vector2 direction{calculateDirection()};

    return std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
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
void Enemy::entityCollisionHandler(Entity *other)
{
    sf::Vector2f diff = sf::Sprite::getPosition() - other->getPosition();
    float lenDistance = std::sqrt((diff.x * diff.x) + (diff.y * diff.y));
    sf::Vector2f direction;
    float push = other->getGlobalBounds().width / 6.0f;
    if (lenDistance > 0)
    {
        direction = diff / lenDistance;
    }
    else
    {
        direction = sf::Vector2f(0.5f, 0.5f);
    }

    // using a set variable to lower the push force

    sf::Sprite::setPosition(sf::Sprite::getPosition() + direction * push);
}
void Enemy::boxCollisionHandler(Entity *box)
{
    sf::FloatRect enemyBounds = getGlobalBounds();
    sf::FloatRect boxBounds = box->getGlobalBounds();

    // calculates the distance between enemy and box
    float horizontalDistance =
        (enemyBounds.left + enemyBounds.width / 2) - (boxBounds.left + boxBounds.width / 2);
    float verticalDistance =
        (enemyBounds.top + enemyBounds.height / 2) - (boxBounds.top + boxBounds.height / 2);

    // calculates how much the enemy image is above the box
    float overlapX = (enemyBounds.width + boxBounds.width) / 2 - std::abs(horizontalDistance);
    float overlapY = (enemyBounds.height + boxBounds.height) / 2 - std::abs(verticalDistance);

    // moves along the smaller intersection to seperate enemy from the box
    sf::Vector2f move;
    if (overlapX < overlapY)
    {
        if (horizontalDistance < 0)
        {
            overlapX = -overlapX; // left
        }

        move = sf::Vector2f(overlapX, 0.f); // right
    }
    else
    {
        if (verticalDistance < 0)
        {
            overlapY = -overlapY; // top
        }

        move = sf::Vector2f(0.f, overlapY); // bottom
    }

    setPosition(getPosition() + move);
}

std::string Enemy::getTag()
{
    return "enemy";
}

void Enemy::onCollision(Entity *other)
{
    if (other->getTag() == "player" || other->getTag() == "enemy")
    {
        entityCollisionHandler(other);
    }
    else if (other->getTag() == "obstacle")
    {
        boxCollisionHandler(other);
        return;
    }
}

void Enemy::onBorderCollision()
{
    sf::Sprite::setPosition(oldPosition);
}

void Enemy::tryAttack(float len)
{
    auto playerSize{player->getTexture()->getSize()};
    auto enemySize{this->getTexture()->getSize()};

    float imageRange{static_cast<float>(attackRange)};
    imageRange +=
        sqrt((playerSize.x / 2) * (playerSize.x / 2) + (playerSize.y / 2) * (playerSize.y / 2)) +
        sqrt((enemySize.x / 2) * (enemySize.x / 2) + (enemySize.y / 2) * (enemySize.y / 2));

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
    auto playerSize{player->getTexture()->getSize()};
    auto enemySize{this->getTexture()->getSize()};

    double imageRange{static_cast<double>(attackRange)};
    imageRange +=
        sqrt((playerSize.x / 2) * (playerSize.x / 2) + (playerSize.y / 2) * (playerSize.y / 2)) +
        sqrt((enemySize.x / 2) * (enemySize.x / 2) + (enemySize.y / 2) * (enemySize.y / 2));

    if (len <= imageRange)
    {
        contuneBegin = true;
    }
    if (contuneBegin && explosionCountdown > 0)
    {
        explosionCountdown--;
    }
    if (contuneBegin)
    {
        exploade(len);
    }
}

void Kaboom::exploade(float len)
{
    if (hasExploded)
    {
        die();
        return; // här för att stoppa att en kabom kan explodera fellera gånger
    }

    if (explosionCountdown > 0)
    {
        hasExploded = true;

        //std::cout<<"kaboom"<<std::endl;
        auto p { player -> getTexture()-> getSize()};
        auto e {this -> getTexture()-> getSize()};

        double imageRange{explosionRange};
        imageRange += sqrt((p.x/2)*(p.x/2)+(p.y/2)*(p.y/2))+sqrt((e.x/2)*(e.x/2)+(e.y/2)*(e.y/2));

        if (len <= imageRange)
        {
            player->takeDamage(explosionDamage);
        }
        auto texture{TextureManager::instance()->getTexture("explod.png")};
        this -> setTexture(*texture, true); // tog delen från SFML att om man säter true i setTExur så får bilden bhåla sin storlek när den ritas ut https://www.sfml-dev.org/documentation/3.0.2/classsf_1_1Sprite.html#a3729c88d88ac38c19317c18e87242560
        //sf::Sprite s;
        //s.setTexture(*texture);
        auto explodSize{texture->getSize()};
        //std::cout<<"x "<<explodSize.x<<" y "<<explodSize.y<<std::endl;
        this-> setOrigin(explodSize.x / 2.0, explodSize.y / 2.0);
    }

    auto playerSize{player->getTexture()->getSize()};
    auto enemySize{this->getTexture()->getSize()};

    double imageRange{explosionRange};
    imageRange +=
        sqrt((playerSize.x / 2) * (playerSize.x / 2) + (playerSize.y / 2) * (playerSize.y / 2)) +
        sqrt((enemySize.x / 2) * (enemySize.x / 2) + (enemySize.y / 2) * (enemySize.y / 2));

    if (len <= imageRange)
    {
        player->takeDamage(explosionDamage);
    }
    auto texture{TextureManager::instance()->getTexture("expload.png")};
    this->setTexture(
        *texture,
        true); // tog delen från SFML att om man säter true i setTExur så får bilden bhåla sin
    // storlek när den ritas ut
    // https://www.sfml-dev.org/documentation/3.0.2/classsf_1_1Sprite.html#a3729c88d88ac38c19317c18e87242560
    // sf::Sprite s;
    // s.setTexture(*texture);
    auto explosionSize{texture->getSize()};
    this->setOrigin(explosionSize.x / 2.0, explosionSize.y / 2.0);
    hasExploded = true;
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
    isInRange(len);
}

// Archer
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