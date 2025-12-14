#ifndef Spawner_H
#define Spawner_H

#include <vector>

#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "TilesManager.h"

class Spawner
{
  public:
    Spawner(Player *player);
    void resetState();

    void spawnEnemies();
    void chooseSpawnPos();

  private:
    void increaseSpawnRate();
    void newEnmey();
    void addFootman();
    void addKaboom();
    void addArcher();

    std::vector<Enemy *> enemies;
    double spawnRate;
    double spawnRateIncrease;
    sf::Vector2f spawnPoint;
    double counter;
    double timeCounter;

    Player *player;


    bool inKaboom;
    bool inArcher;
};

#endif
