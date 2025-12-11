#include "Spawner.h"

#include <cstdlib>
#include "TileManager.h"
#include "Window.h"

Spawner::Spawner(Player* player):spawnRate{200.0}, player{player}
{
    Spawner::spwanEnemies();
}

void Spawner::spwanEnemies()
{
    
    if(conter >= spawnRate)
    {
        nyEnmey();
        choseSpawnPos();
        Footman* enemyF = new Footman(currentHP, movementSpeed, position, attackRange, attackSpeed, XP_DROP, damage, score, player);

        Map::instance()->addEntity(enemyF);
        choseSpawnPos();
        addKaboom();
        choseSpawnPos();
        addArcher();

        conter = 0;
        timeConter +=1;
        Spawner::incresSpawnRate();
    }
    else
    {
        conter += 1;
    }

}

void Spawner::nyEnmey()
{
    if(timeConter >= 10)
    {
        inKaboom = true;
    }
    if(timeConter >= 20)
    {
        inArcher = true;
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
   
    if(spawnRate > 1)
    {
        spawnRate *= spawnRateIncres;

    }
}


void Spawner::addKaboom()
{
    if(inKaboom)
    {
        double explodeRange {150};
        double explodeDamage {10};
        float agroRange {300};
        Kaboom* enemyK = new Kaboom( currentHP, movementSpeed, position, attackRange, attackSpeed, XP_DROP, damage, score, player, explodeRange, explodeDamage, agroRange);
        Map::instance()->addEntity(enemyK);
    }
}

void Spawner::addArcher()
{
    if(inArcher)
    {
        float fireRange {350};
        Archer* enemyA = new Archer( currentHP, movementSpeed, position, attackRange, attackSpeed, XP_DROP, damage, score, player, fireRange);
        Map::instance()->addEntity(enemyA);
    }
}
