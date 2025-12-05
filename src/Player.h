#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "Character.h"
#include "GameState.h"
#include "StateMachine.h"
enum Choises //levelup choise
{
  HP,
  SPEED,
  DAMAGE,
  WEAPON
};

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
           float damageMultiplier);
          
    void setXP(int xp);
    void levelUP(Choises choise);

    void drawInfo(bool boxPosX, bool boxPosY, float boxWidth, float boxheight);
    
    void draw(sf::RenderWindow *window) const;
    

    void move() override;
    void die() override;

    void onCollision(std::string other /*otehr = other.tag*/) override;

  private:
    void drawHP(bool boxPosX, bool boxPosY, float boxWidth, float boxheight);
    void drawXP(bool boxPosX, bool boxPosY, float boxWidth, float boxheight);
    float maxHP;

    std::string name{};
    int xp;
    int maxXP;
    float currentHP;
    int levels;

    float damageMultiplier;
    float boxWidth;
    float boxHeight;

    sf::Texture const *texture;

};

#endif /*PLAYER_H*/