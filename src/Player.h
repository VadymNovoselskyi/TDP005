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

enum Directions
{
  NORTH = -1,
  SOUTH = 1,
  EAST = -1,
  WEST = 1
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

    void drawInfo(float boxPosX, float boxPosY, float boxWidth, float boxheight);
    
    void draw(sf::RenderWindow *window);
    

    void move() override;
    void die() override;

    void onCollision(std::string other /*otehr = other.tag*/) override;

  private:
    void drawBox(float boxPosX, float boxPosY, float boxWidth, float boxheight, int r, int g, int b);
    
    float maxHP;

    std::string name{};
    float rotation {};
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