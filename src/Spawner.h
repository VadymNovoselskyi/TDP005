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

        std::vector <Enemy*> enemies;
        double spawnRate;
        double spawnRateIncrease {0.99};
        sf::Vector2f spwanPoint;
        double counter;
        Player* player;

        double timeCounter; // resepterat tid föt tillfälet 

        bool inKaboom{false};
        bool inArcher{false};
        
        sf::Vector2f position {};
};

#endif
