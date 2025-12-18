#ifndef Spawner_H
#define Spawner_H

#include <vector>

#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "TilesManager.h"
/**
 * Spawner is responsible for:
 * creating enemy
 * plase enmy on the game map
 * how often to place enemy
 * placing difrent typ of enmy 
 */

class Spawner
{
  public:
   /**
     * Constructor for player with needed informaiton
     * @param player is a pointer to the player bul carahter and its difrent informaskion. 
     */
    Spawner(Player *player);
   /**
     * Resets the spawner variables with the start values
     */
    void resetState();
   /**
     * loking when to spawn enemy
     * Formula steps:
     * 1 se if couter is eguel or biger then spawn rate 
     * 1.1 run newEnime fukion and the difrent add fukion.
     * 1.2 reset the couter and incres time couter for a new enmy typ. 
     * 1.3 run increaseSpawnRate fukion
     * 2 if not incres couter by 1 
     */
    void spawnEnemies();
    /**
     * loking fore where to spawn enemy where it is not seen by the player.
     * Formula steps:
     * 1 get the map size
     * 2 get the size of the window where the player can see
     * 3 get a random x and y nuber betwen 0 and the map size
     * std::rand() % mapSize.x; std::rand() % mapSize.y;
     * sät x och y till en variabel för den nya posikionen
     * 4 finde the window where the player can see 
     * float pPlusX{playerWindow.x + (Window::getWindowWidth() / 2.0F)}; // 512
     * float pMinusX{playerWindow.x - (Window::getWindowWidth() / 2.0F)};
     * float pPlusY{playerWindow.y + (Window::getWindowHeight() / 2.0F)}; // 384
     * float pMinusY{playerWindow.y - (Window::getWindowHeight() / 2.0F)};
     * 5 se if the ny posigen is in the window where the player can see 
     * if init du the proses egan aurvise return the ny posigen 
     */
    void chooseSpawnPos();

  private:
    /**
    * incres the curen spawn rate so enemy swan more often 
    */
    void increaseSpawnRate();
    /**
    * se if it is time to allow a ny enemy typ enter
    */
    void newEnmey();
    /**
    * spawn the footman enemy typ
    */
    void addFootman();
    /**
    * spawn the kaboom enemy typ
    */
    void addKaboom();
    /**
    * spawn the archer enemy typ
    */
    void addArcher();

    // std::vector<Enemy *> enemies;
    double spawnRate;
    double spawnRateIncrease;
    sf::Vector2f spawnPoint;
    double counter;
    double timeCounter;

    Player *player;


    bool canSpawnKaboom; 
    bool canSpawnArcher; 
};

#endif
