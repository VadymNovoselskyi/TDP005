#include "Spawner.h"
#include <iostream>
#include <cstdlib>




struct Point
{
    int x{};
    int y{};
};
Spawner::Spawner(double spawnRate, Player* player):spawnRate{spawnRate}, player{player}
{
    Spawner::spwanEnemies();
}

void Spawner::spwanEnemies()
{
    if(conter == spawnRate)
    {
        Footman* enemy = new Footman(100.0,
                                100.0,
                                4,
                                {10,10},
                                {0,0},
                                12,
                                6,
                                10,
                                5,
                                2,
                                player);

                    Map::instance()
                        ->addEntity(enemy);
        if(conter == spawnRate)
        {
            conter = 0;
            std::cout<<"nolsets "<<conter<<std::endl;
        }
        std::cout<<"i spawner "<<conter<<std::endl;
    }
    else
    {
        conter +=1;
    }
}

Point choseSpawnPos()
{
    int const random_x = std::rand();
    int const random_y = std::rand();
}