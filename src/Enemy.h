#ifndef Enemy_H
#define Enemy_H
#include <string>

#include "Character.h"
#include "GameState.h"
#include "Player.h"
#include "StateMachine.h"

class Enemy : public Character
{
  public:
    Enemy(/*Character*/ std::string const& pngName,
          double currentHP,
          int movementSpeed,
          sf::Vector2f positon,
          /*Enemy*/ int attackRange,
          int attackSpeed,
          int const XP_DROP,
          double damage,
          int score,
          Player *player);
    ~Enemy() override = default;

    virtual void attack() = 0;
    std::string getTag();

    // void move() override;
    void die() override;
    void onCollision(Entity *other) override;
    void onBorderCollision() override;

  protected:
    float calculateDistance();
    sf::Vector2f calculateDirection();
    float calculateRotation();
    void collisionHandler(Entity *other);
    void tryAttack(float leng);
    sf::Vector2f oldPosition;
    int attackRange;
    int attackSpeed;
    int count{};
    int const XP_DROP;
    double damage;
    int score; // inte en privat för olika enyme är vär olika score
    Player *player;
    float rotation;
    std::string const &pngName;
};

class Footman : public Enemy
{
  public:
    Footman(/*Character*/ std::string const& pngName,
            double currentHp,
            int movementSpeed,
            sf::Vector2f positon,
            /*Enemy*/ int attackRange,
            int attackSpeed,
            int const XP_DROP,
            double damage,
            int score,
            Player *player);
    void attack() override;
    void move() override;
};

class Kaboom : public Enemy
{
  public:
    Kaboom(/*Character*/ std::string const& pngName,
           double currentHp,
           int movementSpeed,
           sf::Vector2f positon,
           /*Enemy*/ int attackRange,
           int attackSpeed,
           int const XP_DROP,
           double damage,
           int score,
           Player *player,
           double explodeDamage,
           double explodeRange,
           int explodeCountdown,
           float agroRange);
    void attack() override;
    void move() override;

  private:
    void isInRange(float len);
    void explode(float len);
    double explodeDamage;
    double explodeRange;
    int explodeCountdown;
    float agroRange;
};

class Archer : public Enemy
{
  public:
    Archer(/*Character*/ std::string const& pngName,
           double currentHp,
           int movementSpeed,
           sf::Vector2f positon,
           /*Enemy*/ int attackRange,
           int attackSpeed,
           int const XP_DROP,
           double damage,
           int score,
           Player *player,
           double velocity);
    void attack() override;
    void move() override;

  private:
    void shoot();
    // float fireRange;
    double velocity;
};

#endif
