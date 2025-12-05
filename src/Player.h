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
           Point positon,
           Point direction,
           std::string name,
           int xp,
           int maxXP,
           int levels,
           float damageMultiplier,
           float boxWidth,
           float boxHeight);
    void setXP(int xp);
    void levelUP(int smth);
    // void addWeapon(weapon)
    /// void createWeapon()
    void drawInfo();
    void move() override;
    void die() override;

  private:
    void drawHP();
    void drawXP();
    float maxHP;

    std::string name{};
    int xp;
    int maxXP;
    float currentHP;
    int levels;
    float damageMultipler;
    float boxWidth;
    float boxHeight;
};

#endif /*PLAYER_H*/