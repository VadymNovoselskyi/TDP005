#ifndef PLAYER_H
#define PLAYER_H
#include <functional>
#include <string>
#include <vector>

#include "Character.h"
#include "Entity.h"
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
/**
 * Player is responsible for:
 * updating player movement and rotation
 * uppdating the healt and xp bar
 * collision handling with obstacles
 * increasign varaibles such as healt,speed and damageMultiplayer
 */
class Player : public Character
{
  public:
    /**
     * Constructor for player with needed informaiton
     *
     * @param startHP Saves the health that a player starts with
     * @param startSpeed Saves the speed that a plyer shtarts with
     * @param position Is used to store the plyers current position and is set to be in the middle
     * of the map at the beggining
     * @param tag Is used with collision for the other enemis to se if they have collided with the
     * player
     * @param onLevelUp Handles what happends when a player levels up
     */
    Player(double startHP,
           int startSpeed,
           sf::Vector2f const &position,
           std::string const &tag,
           std::function<void(std::vector<LevelUpInfo>)> const &onLevelUp);

    /**
     * Resets the players variables with the start values
     * @param newPosition stores the start position ( middle of the map)
     */
    void resetState(sf::Vector2f const &newPosition);

    /**
     * Is used to draw all four xp and hp boxes with a help function drawBox
     *
     * @param window Is used to let drawBox drawthe boxes on the window
     */
    void drawInfo(sf::RenderWindow *window);

    /**
     * Moves the player based on keyboard inputs
     * Checks wads keys to decide movement direction. If the player moves diagonal the direction
     * vector is normalized by dividing with squrt(2) to keep an even speed.
     *
     * Then it sets the weapons position to the players new position and calls the shooting function
     * automatically.
     *
     * Before the calculations begin sets the direction x and y values to 0
     * oldPosition is saved to allow reseting movement with collision of obstacles
     *
     * Formula steps:
     * 1. uppdates direction  based on wasd
     * 2. if moving diagonally (checked with abs(direction.x) + abs(direction.y) > 1)
     * direction.x /= sqrt(2)
     * directiony /= squrt(2)
     * 3. sprite.position += direction * movementSpeed
     *
     */
    void move() override;

    /**
     * Calculates the players rotation depending on the mouses position in the game window
     *
     * Uses atan2 on the difference between mouse positon and window center to get the angle in
     * radians, converts to degrees and add 90 to allign the sprite
     * WHich it uses to uppdate the sprites adn weapons rotaitons.
     *
     * Formula:
     * rotation = atan2(mouseY - centerY, mouseX - centerX) * (180 / PI) + 90
     *
     * @param window Is used to get the mouses posiiton from the game window instead of the screen
     * window
     */
    void updateRotation(sf::RenderWindow *window);

    /**
     * Increases the players current xp
     *
     * @param xp Stores the amount the players current xp should increase with
     */
    void gainXp(int xp);

    /**
     * Increases the players current health
     *
     * @param amount Stores the amount the players current health should increase with
     */
    void heal(double amount);

    /**
     * Increases the players max health
     *
     * @param hp Stores the amount the players max health should increase with
     */
    void increaseMaxHp(double hp);

    /**
     * Increases the players speed
     *
     * @param amount Stores the amount the players speed should increase with
     */
    void increaseSpeed(int amount);

    /**
     * Increases the players current xp
     *
     * @param amount Stores the amount the players current damageMultiplyer should increase with
     */
    void increaseDamageMultiplyer(double amount);

    /**
     * Calls a function from statemachine which switch gamestate to game over
     */
    void die() override;

    /**
     * Is used to handle plyers collision with objects
     * @param other stores the entety the player has collided with
     */
    void onCollision(Entity *other) override;

    /**
     * handles collision with the border and is used by the map
     */
    void onBorderCollision() override;

  private:
    double const startHp;
    double maxHp;
    int const startSpeed;
    double damageMultiplier;

    float rotation;
    sf::Vector2f oldPosition;

    ExperienceManager expManager;
    WeaponsManager weaponsManager;
    std::function<void(std::vector<LevelUpInfo>)> onLevelUp;
    /**
     * Is used to draw boxes for health and experience
     *
     * @param window Is used to let the method draw on the game window
     * @param box Is used to tell the draw function what shape it should take in to draw
     * @param boxPosY Stores the boxes y cordinates and tells the draw function where on the y
     * positon it should be drawn
     * @param boxPosX Stores the boxes x cordinates and tells the draw function where on the x
     * position it should be drawn
     * @param boxWidth Stores the boxes width and is used to set the widht of the box
     * @param boxHeight Stores the boxes height and is used to se thte height on the box
     * @param boxColor Stores the box color and is sued to set a color for each box
     */
    void drawBox(sf::RenderWindow *window,
                 sf::RectangleShape &box,
                 float const &boxPosX,
                 float const &boxPosY,
                 float const &boxWidth,
                 float const &boxheight,
                 sf::Color const &boxColor);

    // create box for xp and hp
    sf::RectangleShape hpBox; // background box to show how much hp a player has lost
    sf::RectangleShape
        currentHpBox; // shows the current hp lenght changes on % left of currenthp / maxhp

    sf::RectangleShape xpBox; // background box to show how much xp is left until next level
    sf::RectangleShape
        currentXpBox; // shows the current xp lengt changs on the % left of xp / maxXP to next level

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

    // using Character::draw;
};

#endif /*PLAYER_H*/