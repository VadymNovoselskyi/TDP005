#ifndef Spawner_H
#define Spawner_H


#include"Enemy.h"
#include"Map.h"
#include <vector>
#include "Player.h"
#include "TileManager.h"

class Spawner
{
    public:
        Spawner(Player* player);
        void spwanEnemies();
        sf::Vector2f choseSpawnPos();

    private:
        void incresSpawnRate();
        void addKaboom();
        void addArcher();
        std::vector <Enemy*> enemies;
        double spawnRate;
        sf::Vector2f spwanPoint;
        Player* player;
        double conter;

        bool inKaboom{false};
        bool inArcher{false};

        //det som ska kicas till enemy
        double maxHP {100.0};
        double currentHP {100.0};
        int movementSpeed {4};
        sf::Vector2f position {choseSpawnPos()};
        sf::Vector2f direction {0,0};
        int attackRange {12};
        int attackSpeed {6};
        int XP_DROP {10};
        double damage {5};
        int score {2};
        
        

};

#endif
