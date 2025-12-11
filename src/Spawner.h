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
    void spwanEnemies();
    void choseSpawnPos();

    private:
        void incresSpawnRate();
        void nyEnmey();
        void addKaboom();
        void addArcher();
        std::vector <Enemy*> enemies;
        double spawnRate;
        double spawnRateIncres {0.99};
        sf::Vector2f spwanPoint;
        Player* player;
        double conter;

        double timeConter; // resepterat tid föt tillfälet 

        bool inKaboom{false};
        bool inArcher{false};

        //det som ska kicas till enemy
        double currentHP {100.0};
        int movementSpeed {4};
        sf::Vector2f position {};
        sf::Vector2f direction {0,0};
        int attackRange {10};
        int attackSpeed {10};
        int XP_DROP {5};
        double damage {15};
        int score {2};
        
        

};

#endif
