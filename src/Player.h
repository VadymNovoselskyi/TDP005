#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "Character.h"
#include "LevelUPManager.h"
#include "GameState.h"
#include "StateMachine.h"

enum Directions
{
  NORTH = -1,
  SOUTH = 1,
  EAST = -1,
  WEST = 1
};

enum Rotations
{
  UP = 0,
  LEFT = -90,
  DOWN = 180,
  RIGHT = 90 
};

class Player : public Character
{
  public:
    Player(double maxHP,
           double currentHp,
           int movementSpeed,
           sf::Vector2f positon,
           sf::Vector2f direction,
           std::string name,
           int levels,
           float damageMultiplier);
          
    // void levelUP(Choises choise);

    void drawInfo(sf::RenderWindow *window);
    
    void draw(sf::RenderWindow *window);
    

    void move() override;
    void die() override;

    void onCollision(std::string other /*otehr = other.tag*/) override;

    protected:
    double maxHP;
    double currentHP;
    std::string name;
    float rotation;
    int levels;
    float damageMultiplier;

    private:
    void drawBox(sf::RenderWindow *window, sf::RectangleShape box, float boxPosX, float boxPosY, float boxWidth, float boxheight, int r, int g, int b);
    sf::Texture const *texture;
    //create box for xp and hp
    sf::RectangleShape HPBox;
    sf::RectangleShape CurrentHPBox;
    
    sf::RectangleShape XPBox;
    sf::RectangleShape CurrentXPBox;
    

};

#endif /*PLAYER_H*/