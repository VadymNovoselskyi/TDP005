#include "Spawner.h"
#include <iostream>
#include <cstdlib>
#include "TileManager.h"

Spawner::Spawner(Player* player):spawnRate{200.0}, player{player}
{
    Spawner::spwanEnemies();
}

void Spawner::spwanEnemies()
{
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
    
    if(conter >= spawnRate)
    {
        Footman* enemy = new Footman(maxHP, currentHP, movementSpeed, position, direction, attackRange, attackSpeed, XP_DROP, damage, score, player);

        Map::instance()->addEntity(enemy);

    
        conter = 0;
        Spawner::incresSpawnRate();
 
        
    }
    else
    {
        conter +=1;
    }
    
}

sf::Vector2f Spawner::choseSpawnPos()
{
    sf::Vector2i mapSize { TileManager::instance() -> getMapDimensions()};
    //std::cout<<mapSize.x<<std::endl;
    float randomX = std::rand() % mapSize.x; // tar inspraskion från  w3schools //https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    float randomY = std::rand() % mapSize.y;
 
    sf::Vector2f nySpawnPos {randomX, randomY};
    return nySpawnPos;

}
void Spawner::incresSpawnRate()
{
    if(spawnRate > 1)
    {
        spawnRate *= 0.8;
    }
}
