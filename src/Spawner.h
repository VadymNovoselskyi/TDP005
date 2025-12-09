#ifndef Spawner_H
#define Spawner_H


#include"Enemy.h"
#include"Map.h"
#include <vector>
#include "Player.h"

class Spawner
{
    public:
        Spawner(Player* player);
        void spwanEnemies();
        sf::Vector2f choseSpawnPos();

    private:
        double incresSpawnRate();
        std::vector <Enemy*> enemies;
        double spawnRate;
        sf::Vector2f spwanPoint;
        Player* player;
        double conter;
        
        

};

#endif
