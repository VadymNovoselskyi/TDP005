#ifndef Spawner_H
#define Spawner_H

#include <vector>

#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "TileManager.h"

class Spawner
{
  public:
    Spawner(Player *player);
    void resetState();

    void spawnEnemies();
    void choseSpawnPos();

  private:
    void incresSpawnRate();
    void newEnmey();
    void addFootman();
    void addKaboom();
    void addArcher();

    //std::vector<Enemy *> enemies;
    double spawnRate;
    double spawnRateIncrease;
    sf::Vector2f spawnPoint;
    double counter;
    Player *player;

    double timeCounter; // resepterat tid föt tillfälet

    bool canSpawnKaboom;
    bool canSpawnArcher;
};

#endif
