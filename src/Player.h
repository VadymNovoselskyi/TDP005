#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "Character.h"
#include "GameState.h"
#include "StateMachine.h"

class Player : public Character
{
  public:
    Player(float maxHP,
           float currentHp,
           int movementSpeed,
           sf::Vector2f positon,
           sf::Vector2f direction,
           std::string name,
           int xp,
           int maxXP,
           int levels,
           float damageMultiplier,
           sf::Texture textue,
           float boxWidth,
           float boxHeight);
          
    void setXP(int xp);
    void levelUP(int smth);
    // void addWeapon(weapon)
    /// void createWeapon()

    void drawInfo();

    void draw(sf::RenderWindow *window) const;
    void drawHP();
    void drawXP();

    void move() override;
    void die() override;

    void onCollision(std::string other /*otehr = other.tag*/) override;

  private:
    void drawHP();
    void drawXP();
    float maxHP;

    std::string name{};
    int xp;
    int maxXP;
    float currentHP;
    int levels;

    float damageMultiplier;
    float boxWidth;
    float boxHeight;

    sf::Texture texture;

};

#endif /*PLAYER_H*/