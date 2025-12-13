#ifndef PLAYER_H
#define PLAYER_H
#include <functional>
#include <string>
#include <vector>

#include "Character.h"
#include "ExperienceManager.h"
#include "GameState.h"
#include "StateMachine.h"
#include "WeaponsManager.h"

enum Direction
{
    NORTH = -1,
    SOUTH = 1,
    EAST = -1,
    WEST = 1
};

class Player : public Character
{
  public:
    Player(double startHP,
           int startSpeed,
           sf::Vector2f const &position,
           std::string const &tag,
           std::function<void(std::vector<LevelUpInfo>)> const &onLevelUp);
    void resetState(sf::Vector2f const &newPosition);

    void draw(sf::RenderWindow *window);

    void move() override;
    void updateRotation(sf::RenderWindow *window);

    void gainXp(int xp);
    void heal(double amount);
    void increaseMaxHP(double amount);

    void increaseSpeed(int amount);
    void increaseDamageMultiplyer(double amount);
    void die() override;

    void onCollision(Entity *other) override;
    void onBorderCollision() override;

  private:
    double const START_HP;
    double maxHP;
    int const START_SPEED;
    double damageMultiplier;

    float rotation;
    sf::Vector2f oldPosition;

    ExperienceManager expManager;
    WeaponsManager weaponsManager;
    std::function<void(std::vector<LevelUpInfo>)> onLevelUp;
    void drawInfo(sf::RenderWindow *window);
    void drawBox(sf::RenderWindow *window,
                 sf::RectangleShape &box,
                 float const &boxPosX,
                 float const &boxPosY,
                 float const &boxWidth,
                 float const &boxheight,
                 sf::Color const &boxColor);

    // create box for xp and hp
    sf::RectangleShape HPBox; // background box to show how much hp a player has lost
    sf::RectangleShape
        currentHPBox; // shows the current hp lenght changes on % left of currenthp / maxhp

    sf::RectangleShape xpBox; // background box to show how much xp is left until next level
    sf::RectangleShape
        currentXPBox; // shows the current xp lengt changs on the % left of xp / maxXP to next level

    sf::Color static const CURRENT_HP_BOX_COLLOR; // lighter red to show current hp
    sf::Color static const HP_BOX_COLOR;          // darker red to show max hp
    sf::Color static const CURRENT_XP_BOX_COLOR;
    sf::Color static const XP_BOX_COLOR;
    float static const BOX_OFFSET; // a set offset to be 18 pixles away from screen top left corner
                                   // used by both xp and hp
    float static const XP_BOX_Y_OFFSET; // a set offset by 78 for the xp box to be set under the hp
                                        // box
    float static const BOX_WIDHT;
    float static const BOX_HEIGTH;
};

#endif /*PLAYER_H*/