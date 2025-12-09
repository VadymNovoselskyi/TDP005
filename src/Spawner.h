#ifndef Spawner_H
#define Spawner_H

#include <vector>

#include "Enemy.h"
#include "Map.h"
#include "Player.h"

class Spawner
{
  public:
    Spawner(Player *player);
    void spwanEnemies();
    sf::Vector2f choseSpawnPos();

  private:
    double increaseSpawnRate();
    double spawnRate;
    int counter;
    sf::Vector2f spwanPoint;

    std::vector<Enemy *> enemies;
    Player *player;
};

#endif
