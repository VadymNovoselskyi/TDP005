#ifndef Enemy_H
#define Enemy_H
#include <string>

#include "Character.h"
#include "GameState.h"
#include "Player.h"
#include "StateMachine.h"

/**
 * Enemy is responsible for:
 * how all enemy behave on colishen white utore enetity
 * how all enemy die
 * how alla enemy vill makes atemt to damage the player
 */

class Enemy : public Character
{
  public:
    /**
     * Constructor for enemy with needed informaiton
     * @param pngName save which picure shode be jus to repesent the enemy
     * @param currentHP Saves the health that a enemy have
     * @param movementSpeed Saves the speed that a enemy have
     * @param position Is used to store the enemy current position
     * @param attackRange save the bigest distant that the enyme can attack from
     * @param attackSpeed how often the enemy can attack the player
     * @param XP_DROP save the emut of XP the player get when the enemy dies
     * @param damage save how much damege the enemy can do to the player
     * @param score save the emut of point that highscore get when the enemy dies
     * @param player is a pointer to the player bul carahter and its difrent informaskion.
     */

    Enemy(/*Character*/ std::string const &pngName,
          double currentHP,
          int movementSpeed,
          sf::Vector2f positon,
          /*Enemy*/ int attackRange,
          int attackSpeed,
          int const XP_DROP,
          double damage,
          int score,
          Player *player);
    ~Enemy() override = default;

    /**
     * säget till att alla barnklaser behöver ha en egen attack
     */
    virtual void attack() = 0;
    /**
     * ger tagen enemy som används i collisions för att veta vad som händer
     */
    std::string getTag();

    /**
     * handel what hapen when a enyme die
     *
     * removit from the map and game
     * giv xp to plater and score to highscore
     */
    void die() override;

    /**
     * Handles enems collision with other enemies and player.

     * When a collision occurs it calculates how long the images are over each other and then pushes
     * one of the enemy away with the full distance divided by 6 to get a smaller force push
     * @param other stores the object the enemy
     */
    void onCollision(Entity *other) override;

    /**
     * Handles enemy collision with obstacles by calculating the minimum distance it has to move.
     *
     * The method compares the intersection along the x and y axes and moves the enemy along the
     * smallest intersecting axis to avoid contact by pushing the enemy in the other direction.
     *
     * Formula steps:
     * 1. diff = enemy.position - other.position
     * 2. lenDistance = sqrt(diff.x * diff.x + diff.y * diff.y)
     * 3. direction = diff / lenDistance   // fallback if lenDistance is 0
     * 4. push = other.width / 6
     * 5. enemy.position += direction * push
     */
    void boxCollisionHandler(Entity *box);

    /**
     * Sets the enemies current position to the old position
     */
    void onBorderCollision() override;

  protected:
    /**
     * Calculates the Pythagoras distance between the enemy and player.
     * Formula:
     * distance =  sqrt(x^2 + y^2)
     *
     * @return Distance between enemy and player with cordinates
     */
    float calculateDistance();

    /**
     * Calculates the direction vector from the enemy to the player.
     * The vector is calculated by subtracting the enemy position from the player position. The
     * resulting vector points towards the player positon and still contains the distance.
     * Formula:
     * direction = playerPosition - enemyPosition
     *
     * @return Vector pointing from the enemy to the player
     */
    sf::Vector2f calculateDirection();

    /**
     * Calculates the rotaiton angle needed for the eneme to look at the player.
     * The angle is obtained by using atan2 which gives the angle between the x axis and the vector
     * from the enemy to the player. The value is converted from radians to degrees and offset by +
     * 90 degrees to align with the sprite.
     *
     * Formula:
     * rotation = atan2(player.y - enemy.y, player.x - enemy.x) * (180 / PI) + 90
     *
     * @return Rotation angle in degrees
     */
    float calculateRotation();

    /**
     * Handles collision by pushing the enemy away from another entity.
     *
     * The method calculates the vector difference between the enemy and the other entity,
     * then normalizes it to a direction. The enemy is moved in that direction ny a small amount
     * based on the enemies size.
     *
     * Formula steps:
     * 1. diff = enemy.position - other.position
     * 2. lenDistance = sqrt(diff.x * diff.x + diff.y * diff.y)
     * 3. direction = diff /lenDistance has a fallback distance to prevent dividing by 0
     * 4. push = other.width / 6 - the reason behind dividing by 6, stoping it from looking like the
     * enemy is teleporting
     * 5. enemy.position += direction * push
     */
    void entityCollisionHandler(Entity *other);

    /**
     * se if enemy can attack the player
     *
     * Formula steps:
     * 1 get the texur size of enemy and the player
     * 2 save attackRange in a varibel than add the squr rout of the to texur for enmy and player
     * imageRange += sqrt((p.x / 2) * (p.x / 2) + (p.y / 2) * (p.y / 2)) +
                  sqrt((e.x / 2) * (e.x / 2) + (e.y / 2) * (e.y / 2));
     * se if the distent betwen origo is smaler than the disten the imagesa and attackrange. also se
     if the couter is on 0 or smaler
     * if true than enemy attack and reset the counter
     * @param leng distent betwen enemy and players origo
    */
    void tryAttack(float leng);
    sf::Vector2f oldPosition;
    int attackRange;
    int attackSpeed;
    int count{};
    int const XP_DROP;
    double damage;
    int score;
    Player *player;
    float rotation;
    std::string const &pngName;
};

/**
 * Footman is responsible for:
 * how footman enemy attack
 * how footman enemy move
 */
class Footman : public Enemy
{
  public:
    /**
      * Constructor for footman with needed informaiton

      * @param pngName save which picure shode be jus to repesent the enemy
      * @param currentHP Saves the health that a enemy have
      * @param movementSpeed Saves the speed that a enemy have
      * @param position Is used to store the enemy current position
      * @param attackRange save the bigest distant that the enyme can attack from
      * @param attackSpeed how often the enemy can attack the player
      * @param XP_DROP save the emut of XP the player get when the enemy dies
      * @param damage save how much damege the enemy can do to the player
      * @param score save the emut of point that highscore get when the enemy dies
      * @param player is a pointer to the player bul carahter and its difrent informaskion.
      */

    Footman(/*Character*/ std::string const &pngName,
            double currentHp,
            int movementSpeed,
            sf::Vector2f positon,
            /*Enemy*/ int attackRange,
            int attackSpeed,
            int const XP_DROP,
            double damage,
            int score,
            Player *player);
    /**
     * attack handel to give the player damege
     */
    void attack() override;
    /**
     * move the enemy base on where the player is
     *
     * before the calculations begin sets the direction x and y values to 0
     * oldPosition is saved to allow reseting movement with collision of obstacles
     *
     * Formula steps:
     * 1 cal on calculateDistance() to figurat how long the distant betwen enemy and palyer are
     * 2 if disten isent 0 than calulet the normalisering so that momet only be one and than later
     * can be updated direction.x = (directionResult.x / len); direction.y = (directionResult.y /
     * len); 3 huse the calculateRotation() to get the rotegen the sprite for the enemy ned to lock
     * att the player 4 set how fast the enemy move sf::Sprite::move(direction.x * movementSpeed,
     * direction.y * movementSpeed); 5 run tryAttack(len) to se if the enemy is close inof to the
     * player to attack
     */
    void move() override;
};
/**
 * Kaboom is responsible for:
 * how kaboom enemy attack
 * how kaboom enemy move
 * how kaboom explode
 */
class Kaboom : public Enemy
{
  public:
    /**
     * Constructor for kaboom with needed informaiton
     * @param pngName save which picure shode be jus to repesent the enemy
     * @param currentHP Saves the health that a enemy have
     * @param movementSpeed Saves the speed that a enemy have
     * @param position Is used to store the enemy current position
     * @param attackRange save the bigest distant that the enyme can attack from
     * @param attackSpeed how often the enemy can attack the player
     * @param XP_DROP save the emut of XP the player get when the enemy dies
     * @param damage save how much damege the enemy can do to the player
     * @param score save the emut of point that highscore get when the enemy dies
     * @param player is a pointer to the player bul carahter and its difrent informaskion.
     * @param explodeDamage save how much damge the plager get it is in rage of kabooms explosen
     * @param explodeRange the distanat from kaboom that get hit in the exploshen
     * @param explodeCountdown how much time it is betwen the coutdow begin for the exploshen till
     * it explode
     * @param agroRange distent from the player where it momet icres
     */
    Kaboom(/*Character*/ std::string const &pngName,
           double currentHp,
           int movementSpeed,
           sf::Vector2f positon,
           /*Enemy*/ int attackRange,
           int attackSpeed,
           int const XP_DROP,
           double damage,
           int score,
           Player *player,
           double exploadeDamage,
           double exploadeRange,
           int exploadeCountdown,
           float agroRange);
    /**
     * attack handel to give the player damege
     */
    void attack() override;
    /**
     * move the enemy base on where the player is
     *
     * before the calculations begin sets the direction x and y values to 0
     * oldPosition is saved to allow reseting movement with collision of obstacles
     *
     * Formula steps:
     * 1 cal on calculateDistance() to figurat how long the distant betwen enemy and palyer are
     * 2 if disten isent 0 than calulet the normalisering so that momet only be one and than later
     * can be updated direction.x = (directionResult.x / len); direction.y = (directionResult.y /
     * len); 3 if kaboom is klosenif for it agro than incres sped to 8.0. 8.0 becus thats rely fast
     * 4 huse the calculateRotation() to get the rotegen the sprite for the enemy ned to lock att
     * the player 5 set how fast the enemy move sf::Sprite::move(direction.x * movementSpeed,
     * direction.y * movementSpeed); 6 run tryAttack(len) to se if the enemy is close inof to the
     * player to attack 7 run isInRange() to se if the enemy is close inof to the player to begin
     * exploshen countdown
     */
    void move() override;

  private:
    /**
   * se if enemy is closs inof to the player to begin coutdown for exploshen
   *
   * Formula steps:
   * 1 get the texur size of enemy and the player
   * 2 save explodeRange in a varibel than add the squr rout of the to texur for enmy and player
   * imageRange += sqrt((p.x / 2) * (p.x / 2) + (p.y / 2) * (p.y / 2)) +
                sqrt((e.x / 2) * (e.x / 2) + (e.y / 2) * (e.y / 2));
   * 3 se if the distent betwen origo is smaler than the disten the imagesa and explodeRange.
   * if true set contuneBegin to true.
   * 4 if contuneBegin is true and explodeCountdown is not 0 or smaler dicris explodeCountdown by 1
   * 5 if contuneBegin is true rune explode(float len)
   * @param leng distent betwen enemy and players origo
   */
    void isInRange(float len);
    /**
     * exploen hadel what hapen when it explod and se if it shode explode
     *
     * if hasExplod is true that run die() and reture so that kabbom kant explod moltibule time
     * if explodeCountdown is smaler or egul to 0
     * set hasExplod to true
     * Formula steps:
     * 1 get the texur size of enemy and the player
     * 2 save explodeRange in a varibel than add the squr rout of the to texur for enmy and player
     * imageRange += sqrt((p.x / 2) * (p.x / 2) + (p.y / 2) * (p.y / 2)) +
                  sqrt((e.x / 2) * (e.x / 2) + (e.y / 2) * (e.y / 2));
     * 3 se if the distent betwen origo is smaler than the disten the imagesa and explodeRange.
     * if true makt the player get explodeDamage
     *
     * set the sprite to the exploshen.png.
     */
    void exploade(float len);

    double explosionDamage;
    double explosionRange;
    int explosionCountdown;
    float agroRange;
    bool contuneBegin{false};
    bool hasExploaded{false};
};

/**
 * Archer is responsible for:
 * how archer enemy attack
 * how archer enemy move
 */
class Archer : public Enemy
{
  public:
    /**
    * Constructor for archer with needed informaiton

    * @param pngName save which picure shode be jus to repesent the enemy
    * @param currentHP Saves the health that a enemy have
    * @param movementSpeed Saves the speed that a enemy have
    * @param position Is used to store the enemy current position
    * @param attackRange save the bigest distant that the enyme can attack from
    * @param attackSpeed how often the enemy can attack the player
    * @param XP_DROP save the emut of XP the player get when the enemy dies
    * @param damage save how much damege the enemy can do to the player
    * @param score save the emut of point that highscore get when the enemy dies
    * @param player is a pointer to the player bul carahter and its difrent informaskion.
    * @param velocity save how fast the projektal move
    */
    Archer(/*Character*/ std::string const &pngName,
           double currentHp,
           int movementSpeed,
           sf::Vector2f positon,
           /*Enemy*/ int attackRange,
           int attackSpeed,
           int const XP_DROP,
           double damage,
           int score,
           Player *player,
           double velocity);
    /*
     * attack handel how to attack the player
     * run shoot() fukion
     */
    void attack() override;
    /**
     * move the enemy base on where the player is
     *
     * before the calculations begin sets the direction x and y values to 0
     * oldPosition is saved to allow reseting movement with collision of obstacles
     *
     * Formula steps:
     * 1 cal on calculateDistance() to figurat how long the distant betwen enemy and palyer are
     * 2 if disten isent 0 than calulet the normalisering so that momet only be one and than later
     * can be updated direction.x = (directionResult.x / len); direction.y = (directionResult.y /
     * len); 3 if len is biger than attaRange than move the archer sf::Sprite::move(direction.x *
     * movementSpeed, direction.y * movementSpeed); 4 huse the calculateRotation() to get the
     * rotegen the sprite for the enemy ned to lock att the player 5 run tryAttack(len) to se if the
     * enemy is close inof to the player to attack
     */
    void move() override;

  private:
    /*
     * spawn enemy projektat
     */
    void shoot();
    double velocity;
};

#endif
