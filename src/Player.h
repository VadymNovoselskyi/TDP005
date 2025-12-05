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
    Player(int maxHP,
           int currentHp,
           int movementSpeed,
           Point positon,
           Point direction,
           std::string name,
           int XP,
           int maxXP,
           int levels,
           double damageMultipplyer);
    void setXP(int xp);
    void levelUp(std::string string, int smth);
    // void addWeapon(weapon)
    /// void createWeapon()
    void drawHP();
    void drawXP();
    void move() override;
    void die() override;

  private:
    std::string name{};
    int xp;
    int maxXP;
    int levels;
    double damageMultipplyer;

    
};

#endif /*PLAYER_H*/