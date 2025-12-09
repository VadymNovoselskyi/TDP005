#ifndef Spawner_H
#define Spawner_H


#include"Enemy.h"
#include"Map.h"
#include <vector>
#include "Player.h"

class Spawner
{
    public:
        Spawner(double spawnRate, Player* player);
        void spwanEnemies();
        sf::Vector2f choseSpawnPos();

    private:
        std::vector <Enemy*> enemies;
        double spawnRate;
        sf::Vector2f spwanPoint;
        Player* player;
        
};

#endif
