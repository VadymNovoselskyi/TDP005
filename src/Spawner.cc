#include "Spawner.h"

#include <cstdlib>
#include "TileManager.h"

Spawner::Spawner(Player* player):spawnRate{200.0}, player{player}
{
    Spawner::spwanEnemies();
}

void Spawner::spwanEnemies()
{
    
    if(conter >= spawnRate)
    {
        Footman* enemyF = new Footman(currentHP, movementSpeed, position, attackRange, attackSpeed, XP_DROP, damage, score, player);

        Map::instance()->addEntity(enemyF);
        addKaboom();
    
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
        spawnRate *= 0.99;
        inKaboom = true; // tilfälig
    }
}


void Spawner::addKaboom()
{
    if(inKaboom)
    {
        double explodeRange {};
        double explodeDamage {};
        Kaboom* enemyK = new Kaboom( currentHP, movementSpeed, position, attackRange, attackSpeed, XP_DROP, damage, score, player, explodeRange, explodeDamage);
        Map::instance()->addEntity(enemyK);
    }
}
