#include "Spawner.h"

#include <cstdlib>
#include <iostream>


Spawner::Spawner(Player* player):spawnRate{200.0}, player{player}
{
    Spawner::spwanEnemies();
}

void Spawner::spwanEnemies()
{

    double currentHP {100.0};
    int movementSpeed {4};
    sf::Vector2f position {10,10};
    sf::Vector2f direction {0,0};
    int attackRange {12};
    int attackSpeed {6};
    int XP_DROP {10};
    double damage {5};
    int score {2};
    
    if(conter >= spawnRate)
    {
        Footman* enemy = new Footman(currentHP, movementSpeed, position, direction, attackRange, attackSpeed, XP_DROP, damage, score, player);

        Map::instance()->addEntity(enemy);
    
        conter = 0;
        Spawner::incresSpawnRate();
    }
    else
    {
        conter += 1;
    }
}

void Spawner::choseSpawnPos()
{
    sf::Vector2i mapSize { TileManager::instance() -> getMapDimensions()};
    //std::cout<<mapSize.x<<std::endl;
    float randomX = std::rand() % (mapSize.x - Window::WINDOW_WIDTH) + Window::WINDOW_WIDTH; // tar inspraskion från  w3schools //https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    float randomY = std::rand() % (mapSize.y - Window::WINDOW_HEIGHT) + Window::WINDOW_HEIGHT;//+ gör två saker. den matimatska att öka max higden men också läga till en minsta värde som random kan va.  
 
    sf::Vector2f nySpawnPos {randomX, randomY};
    position = nySpawnPos;

}

void Spawner::incresSpawnRate()
{
   
    spawnRate *= 0.8;
   
}
