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
    Enemy(double hp,
          int movementSpeed,
          sf::Vector2f positon,
          int attackRange,
          int attackSpeed,
          int XP_DROP,
          double damage,
          int score,
          Player *player);

    virtual void attack() = 0;
    std::string getTag();

    void draw(sf::RenderWindow *window) const override;

    // void move() override;
    void die() override;
    void onCollision(std::string const &othe) override;

  protected:
    void tryAttack(float leng);
    // void calcPath(sf::Vector2f);
    int attackRange;
    int attackSpeed;
    int XP_DROP;
    double damage;
    int score; // inte en privat för olika enyme är vär olika score
    Player *player;
};

class Footman : public Enemy
{
  public:
    Footman(double hp,
            int movementSpeed,
            sf::Vector2f positon,
            int attackRange,
            int attackSpeed,
            int XP_DROP,
            double damage,
            int score,
            Player *player);
    void attack() override;
    void move() override;
};

class Kaboom : public Enemy
{
  public:
    Kaboom(double hp,
           int movementSpeed,
           sf::Vector2f positon,
           int attackRange,
           int attackSpeed,
           int XP_DROP,
           double damage,
           int score,
           Player *player,
           double explodeDamage,
           double explodeRange);
    void attack() override;
    void move() override;

  private:
    bool isInRange(float len);
    void explode(float len);
    double explodeDamage;
    double explodeRange;
};

class Archer : public Enemy
{
  public:
    Archer(double hp,
           int movementSpeed,
           sf::Vector2f positon,
           int attackRange,
           int attackSpeed,
           int XP_DROP,
           double damage,
           int score,
           Player *player);
    void attack() override;
    void move() override;

  private:
    void shoot();
};

#endif