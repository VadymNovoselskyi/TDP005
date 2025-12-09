#include "Spawner.h"
#include <iostream>
#include <cstdlib>


Spawner::Spawner(Player* player):spawnRate{200.0}, player{player}
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

    
        conter = 0;
        //Spawner::incresSpawnRate();
        //std::cout<<"nolsets "<<conter<<std::endl;
 
        //std::cout<<"i spawner "<<conter<<std::endl;
    }
    else
    {
        conter +=1;
    }
}

sf::Vector2f Spawner::choseSpawnPos()
{
    int const random_x = std::rand();
    int const random_y = std::rand();
}
double Spawner::incresSpawnRate()
{
    spawnRate *= 0.8;
}
