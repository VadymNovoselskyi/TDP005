#include "Spawner.h"
#include <iostream>
#include <cstdlib>

Spawner::Spawner(Player* player):spawnRate{200.0}, player{player}
{
    Spawner::spwanEnemies();
}

void Spawner::spwanEnemies()
{
    double maxHP {100.0};
    double currentHP {100.0};
    int movementSpeed {4};
    sf::Vector2f position {10,10};
    sf::Vector2f direction {0,0};
    int attackRange {12};
    int attackSpeed {6};
    int XP_DROP {10};
    double damage {5};
    int score {2};
    
    if(conter == spawnRate)
    {
        Footman* enemy = new Footman(maxHP, currentHP, movementSpeed, position, direction, attackRange, attackSpeed, XP_DROP, damage, score, player);

        Map::instance()->addEntity(enemy);

    
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
