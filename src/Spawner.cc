#include "Spawner.h"
#include <iostream> // print test
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
        addKaboom();
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
    sf::Vector2f playerWindow {player -> getPosition()};
    // std::cout <<"map x  "<<mapSize.x<<std::endl;
    // std::cout <<"map y  "<<mapSize.y<<std::endl;

    // std::cout <<"Window x  "<<Window::WINDOW_WIDTH<<std::endl;
    // std::cout <<"Window y  "<<Window::WINDOW_HEIGHT<<std::endl;
    
    float randomX = std::rand() % mapSize.x; // tar inspraskion från  w3schools //https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    float randomY = std::rand() % mapSize.y;  
    sf::Vector2f nySpawnPos {randomX, randomY};
 
    float pPlusX {playerWindow.x + (Window::WINDOW_WIDTH/2)};//512
    float pMinusX {playerWindow.x - (Window::WINDOW_WIDTH/2)};
    float pPlusY {playerWindow.y + (Window::WINDOW_HEIGHT/2)};//384
    float pMinusY {playerWindow.y - (Window::WINDOW_HEIGHT/2)};
    
    bool insidaX = (nySpawnPos.x > pMinusX && nySpawnPos.x < pPlusX); // tar insparaskion från w3schools https://www.w3schools.com/cpp/cpp_operators_logical.asp 
    bool insidaY = (nySpawnPos.y > pMinusY && nySpawnPos.y < pPlusY);

    // std::cout <<"player x "<<playerWindow.x<<std::endl;
    // std::cout <<"player y "<<playerWindow.y<<std::endl;
    // std::cout <<"window +x "<<pPlusX<<std::endl;
    // std::cout <<"window -x  "<<pMinusX<<std::endl;
    // std::cout <<"spaw pos x  "<<nySpawnPos.x<<std::endl;
    // std::cout <<"spaw pos y  "<<nySpawnPos.y<<std::endl;
    if(insidaX and insidaY)
    {
        choseSpawnPos();
    }
    else
    {
        position = nySpawnPos;
    }
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
        choseSpawnPos();
        currentHP = 75;
        damage = 5;
        XP_DROP = 10;
        double explodeRange {150};
        double explodeDamage {30};
        float agroRange {300};
        Kaboom* enemyK = new Kaboom( currentHP, movementSpeed, position, attackRange, attackSpeed, XP_DROP, damage, score, player, explodeRange, explodeDamage, agroRange);
        Map::instance()->addEntity(enemyK);
    }
}

void Spawner::addArcher()
{
    if(inArcher)
    {
        choseSpawnPos();
        movementSpeed = 2;
        damage = 5;
        XP_DROP = 10;
        attackSpeed = 10;
        float fireRange {350};
        attackRange = fireRange;
        Archer* enemyA = new Archer( currentHP, movementSpeed, position, attackRange, attackSpeed, XP_DROP, damage, score, player, fireRange);
        Map::instance()->addEntity(enemyA);
    }
}
