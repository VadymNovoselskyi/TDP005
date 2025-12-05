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
           sf::Vector2f const &positon,
           sf::Vector2f const &direction,
           std::string const &name,
           int xp,
           int maxXP,
           int levels,
           double damageMultipplyer);

    void setXP(int xp);
    void levelUp(std::string string, int smth);
    // void addWeapon(weapon)
    // void createWeapon()

    void draw(sf::RenderWindow *window) const override;
    void drawHP();
    void drawXP();
    void move() override;
    void die() override;

    void onCollision(std::string const &other /*otehr = other.tag*/) override;

  private:
    std::string name{};
    int xp;
    int maxXP;
    int levels;
    double damageMultipplyer;
    sf::Texture const *texture;
};

#endif /*PLAYER_H*/