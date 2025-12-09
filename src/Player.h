#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

#include "Character.h"
#include "GameState.h"
#include "LevelUPManager.h"
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
           sf::Vector2f const &position,
           sf::Vector2f const &direction,
           std::string const &name,
           int levels,
           float damageMultiplier,
           sf::Vector2f oldPosition);

    // void levelUP(Choises choise);

    void drawInfo(sf::RenderWindow *window);

    void draw(sf::RenderWindow *window);

    void move();
    void uppdateRotation(sf::RenderWindow *window);
    void die() override;

    void onCollision(std::string const &other /*otehr = other.tag*/) override;
    
  private:
    double maxHP;
    double currentHP;
    std::string name;
    float rotation;
    int levels;
    float damageMultiplier;
    sf::Vector2f oldPosition;

    void drawBox(sf::RenderWindow *window,
                 sf::RectangleShape box,
                 float boxPosX,
                 float boxPosY,
                 float boxWidth,
                 float boxheight,
                 sf::Color boxColor);
    
    sf::Texture const *texture;
    // create box for xp and hp
    sf::RectangleShape HPBox; // background box to show how much hp a player has lost
    sf::RectangleShape currentHPBox; // shows the current hp lenght changes on % left of currenthp / maxhp

    sf::RectangleShape xpBox; //background box to show how much xp is left until next level
    sf::RectangleShape currentXPBox; // shows the current xp lengt changs on the % left of xp / maxXP to next level
    
    sf::Color static const CURRENT_HP_BOX_COLLOR; // lighter red to show current hp
    sf::Color static const HP_BOX_COLOR; // darker red to show max hp
    sf::Color static const CURRENT_XP_BOX_COLOR;
    sf::Color static const XP_BOX_COLOR;
    float static const BOX_OFFSET; //a set offset to be 18 pixles away from screen top left corner used by both xp and hp
    float static const XP_BOX_Y_OFFSET;  // a set offset by 78 for the xp box to be set under the hp box

};

#endif /*PLAYER_H*/