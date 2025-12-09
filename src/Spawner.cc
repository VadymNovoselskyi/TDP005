#include "Spawner.h"

#include <cstdlib>
#include <iostream>

Spawner::Spawner(Player *player) : spawnRate{200.0}, player{player}, counter{0}
{
    Spawner::spwanEnemies();
}

void Spawner::spwanEnemies()
{
    Footman *enemy = new Footman(100.0, 4, {10, 10}, 12, 6, 10, 5, 2, player);

    Map::instance()->addEntity(enemy);
    // Spawner::incresSpawnRate();
    // std::cout<<"nolsets "<<conter<<std::endl;

    // std::cout<<"i spawner "<<conter<<std::endl;
}

sf::Vector2f Spawner::choseSpawnPos()
{
    int const random_x = std::rand();
    int const random_y = std::rand();
}

double Spawner::increaseSpawnRate()
{
    spawnRate *= 0.8;
}
