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
    Enemy(/*Charactar*/ double currentHP,
          int movementSpeed,
          sf::Vector2f positon,
          /*Enemy*/ int attackRange,
          int attackSpeed,
          int XP_DROP,
          double damage,
          int score,
          Player *player);
    virtual ~Enemy();

    virtual void attack() = 0;
    std::string getTag();

    void draw(sf::RenderWindow *window)const override;
    
    //void move() override;
    void die() override;
    void onCollision(Entity *other) override;
    void onBorderCollision() override;

  protected:
    float calculateDistance();
    sf::Vector2f calculateDirection();
    float calculateRotation();
    void tryAttack(float leng);
    // void calcPath(sf::Vector2f);
    sf::Vector2f oldPosition;
    int attackRange;
    int attackSpeed;
    int count {attackSpeed};
    int XP_DROP;
    double damage;
    int score; // inte en privat för olika enyme är vär olika score
    Player *player;
    float rotation;

  private:
    std::string tag{"enemy"};
    
};

class Footman : public Enemy
{
  public:
    Footman(/*Charactar*/ double currentHp,
            int movementSpeed,
            sf::Vector2f positon,
            /*Enemy*/ int attackRange,
            int attackSpeed,
            int XP_DROP,
            double damage,
            int score,
            Player *player);
    void attack() override;
    void move() override;

  private:
    sf::Texture const *texture;
};

class Kaboom : public Enemy
{
  public:
    Kaboom(/*Charactar*/ double currentHp,
           int movementSpeed,
           sf::Vector2f positon,
           /*Enemy*/ int attackRange,
           int attackSpeed,
           int XP_DROP,
           double damage,
           int score,
           Player *player,
           double explodeDamage,
           double explodeRange,
           float agroRange);
    void attack() override;
    void move() override;

  private:
    void isInRange(float len);
    void explode(float len);
    double explodeRange;
    double explodeDamage;
    float agroRange;
    sf::Texture const *texture;
};

class Archer : public Enemy
{
  public:
    Archer(/*Charactar*/ double currentHp,
           int movementSpeed,
           sf::Vector2f positon,
           /*Enemy*/ int attackRange,
           int attackSpeed,
           int XP_DROP,
           double damage,
           int score,
           Player *player,
           double velocity);
    void attack() override;
    void move() override;

  protected:
    struct Projectles
    {
    };

  private:
    void shoot();
    float fireRange; 
    double velocity;
    sf::Texture const *texture;
};

#endif
