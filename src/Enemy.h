#ifndef Enemy_H
#define Enemy_H
#include <string>

#include "Character.h"
#include "GameState.h"
#include "Player.h"
#include "StateMachine.h"

class Enemy : public Character
{
  public:
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

    virtual void attack() = 0;
    std::string getTag();

    // void move() override;
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

class Footman : public Enemy
{
  public:
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
    void attack() override;
    void move() override;
};

class Kaboom : public Enemy
{
  public:
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
    void attack() override;
    void move() override;

  private:
    void isInRange(float len);
    void exploade(float len);
    double explosionDamage;
    double explosionRange;
    int explosionCountdown;
    float agroRange;
    bool contuneBegin{false};
    bool hasExploaded{false};
};

class Archer : public Enemy
{
  public:
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
    void attack() override;
    void move() override;

  private:
    void shoot();
    double velocity;
};

#endif
