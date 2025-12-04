#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "Character.h"

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
           int maxXp,
           int levels,
           double damageMultipplyer);
    void setXP(int);
    void levelUp(std::string, auto );
    // void addWeapon(weapon)
    /// void createWeapon()
    void drawHP();
    void drawXP();
    void move() override;

  private:
    std::string name{};
    int xp;
    int maxXp;
    int levels;
    double damageMultipplyer;
};

#endif /*PLAYER_H*/