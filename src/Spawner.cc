#include "Spawner.h"

#include <cstdlib>
#include <iostream>

#include "TilesManager.h"
#include "Window.h"

Spawner::Spawner(Player *player)
    : spawnRate{200.0}, spawnRateIncrease{0.99}, spawnPoint{}, counter{0}, timeCounter{0},
      player{player}, hpIncrease{}, canSpawnKaboom{false}, canSpawnArcher{false}
{
    Spawner::spawnEnemies();
}

void Spawner::resetState()
{
    spawnRate = 200.0;
    counter = 0;
    timeCounter = 0;
    canSpawnKaboom = false;
    canSpawnArcher = false;
}

void Spawner::spawnEnemies()
{
    if (counter >= spawnRate)
    {
        newEnmey();
        addFootman();
        addKaboom();
        addArcher();

        counter = 0;
        timeCounter += 1;
        increaseSpawnRate();
        if (timeCounter >= 40)
        {
            addFootman();
            addKaboom();
            addArcher();
        }
    }
    else
    {
        counter += 1;
    }
}

void Spawner::newEnmey()
{
    if (timeCounter >= 10)
    {
        canSpawnKaboom = true;
    }
    if (timeCounter >= 20)
    {
        canSpawnArcher = true;
        hpIncrease += 5;
    }
}

void Spawner::chooseSpawnPos()
{
    sf::Vector2i mapSize{TilesManager::instance()->getMapDimensions()};
    sf::Vector2f playerPos{player->getPosition()};
    auto windowSize{Window::getWindowSize()};
    auto viewRect{sf::FloatRect(playerPos.x - windowSize.x / 2.0F,
                                playerPos.y - windowSize.y / 2.0F,
                                windowSize.x,
                                windowSize.y)};

    bool validSpawnPos = false;
    while (!validSpawnPos)
    {
        float randomX = std::rand() % mapSize.x;
        float randomY = std::rand() % mapSize.y;
        sf::Vector2f newSpawnPos{randomX, randomY};
        if (!(TilesManager::instance()->outOfBorders(newSpawnPos) ||
              viewRect.contains(newSpawnPos)))
        {
            validSpawnPos = true;
            spawnPoint = newSpawnPos;
        }
    }
}

void Spawner::increaseSpawnRate()
{
    if (spawnRate > 1)
    {
        spawnRate *= spawnRateIncrease;
    }
}

void Spawner::addFootman()
{
    chooseSpawnPos();
    std::string const pngName{"enemy.png"};
    double currentHP{100.0 + hpIncrease};
    int movementSpeed{4};
    sf::Vector2f direction{0, 0};
    int attackRange{20};
    int attackSpeed{10};
    int const XP_DROP{5};
    double damage{15};
    int score{2};

    // sf::Vector2f spawnPoint {160,160};
    // sf::Vector2f spawnPoint {2200,2200};
    Footman *enemyF = new Footman(pngName,
                                  currentHP,
                                  movementSpeed,
                                  spawnPoint,
                                  attackRange,
                                  attackSpeed,
                                  XP_DROP,
                                  damage,
                                  score,
                                  player);

    Map::instance()->addEntity(enemyF);
}

void Spawner::addKaboom()
{
    if (canSpawnKaboom)
    {
        chooseSpawnPos();
        std::string const pngName{"kaboom.png"};
        double currentHP{75.0 + hpIncrease};
        int movementSpeed{4};
        sf::Vector2f direction{0, 0};
        int attackRange{10};
        int attackSpeed{10};
        int const XP_DROP{10};
        double damage{5};
        int score{3};
        double exploadeRange{60};
        double exploadeDamage{30};
        int exploadeCountdown{20};
        float agroRange{300};
        Kaboom *enemyK = new Kaboom(pngName,
                                    currentHP,
                                    movementSpeed,
                                    spawnPoint,
                                    attackRange,
                                    attackSpeed,
                                    XP_DROP,
                                    damage,
                                    score,
                                    player,
                                    exploadeRange,
                                    exploadeDamage,
                                    exploadeCountdown,
                                    agroRange);
        Map::instance()->addEntity(enemyK);
    }
}

void Spawner::addArcher()
{
    if (canSpawnArcher)
    {
        chooseSpawnPos();
        std::string const pngName{"fighter.png"};
        double currentHP{100.0 + hpIncrease};
        int movementSpeed{2};
        sf::Vector2f direction{0, 0};
        int attackRange{40};
        int attackSpeed{10};
        int const XP_DROP{10};
        double damage{5};
        int score{2};
        double velocity{3};
        attackRange = 350;
        Archer *enemyA = new Archer(pngName,
                                    currentHP,
                                    movementSpeed,
                                    spawnPoint,
                                    attackRange,
                                    attackSpeed,
                                    XP_DROP,
                                    damage,
                                    score,
                                    player,
                                    velocity);
        Map::instance()->addEntity(enemyA);
    }
}
