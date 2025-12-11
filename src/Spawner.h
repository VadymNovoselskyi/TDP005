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
        void increaseSpawnRate();
        void addKaboom();
        void addArcher();

        std::vector <Enemy*> enemies;
        sf::Vector2f spwanPoint;

        double spawnRate;
        double counter;
        Player* player;

        bool inKaboom{false};
        bool inArcher{false};

        //det som ska kicas till enemy
        double maxHP {100.0};
        double currentHP {100.0};
        int movementSpeed {4};
        sf::Vector2f position {};
        sf::Vector2f direction {0,0};
        int attackRange {12};
        int attackSpeed {6};
        int XP_DROP {10};
        double damage {5};
        int score {2};
        
        

};

#endif
