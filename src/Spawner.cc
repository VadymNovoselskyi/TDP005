#include "Spawner.h"

#include <cstdlib>
#include <iostream> // print test

#include "TilesManager.h"
#include "Window.h"

Spawner::Spawner(Player *player)
    : spawnRate{200.0}, spawnRateIncrease{0.99}, spawnPoint{}, counter{0}, timeCounter{0},
      player{player}, canSpawnKaboom{false}, canSpawnArcher{false}
{
    Spawner::spawnEnemies();
}

void Spawner::resetState()
{
    //enemies.clear();
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
    }
}
void Spawner::chooseSpawnPos()
{
    sf::Vector2i mapSize{TilesManager::instance()->getMapDimensions()};
    sf::Vector2f playerWindow{player->getPosition()};

    float randomX =
        std::rand() % mapSize.x; // tar inspraskion från  w3schools
                                 // //https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    float randomY = std::rand() % mapSize.y;
    sf::Vector2f nySpawnPos{randomX, randomY};

    float pPlusX{playerWindow.x + (Window::getWindowWidth() / 2.0F)}; // 512
    float pMinusX{playerWindow.x - (Window::getWindowWidth() / 2.0F)};
    float pPlusY{playerWindow.y + (Window::getWindowHeight() / 2.0F)}; // 384
    float pMinusY{playerWindow.y - (Window::getWindowHeight() / 2.0F)};

    bool insidaX =
        (nySpawnPos.x > pMinusX &&
         nySpawnPos.x < pPlusX); // tar insparaskion från w3schools
                                 // https://www.w3schools.com/cpp/cpp_operators_logical.asp
    bool insidaY = (nySpawnPos.y > pMinusY && nySpawnPos.y < pPlusY);

    if (insidaX and insidaY)
    {
        chooseSpawnPos();
    }
    else
    {
        spawnPoint = nySpawnPos;
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
    double currentHP{100.0};
    int movementSpeed{4};
    sf::Vector2f direction{0, 0};
    int attackRange{20};
    int attackSpeed{10};
    int const XP_DROP{5};
    double damage{15};
    int score{2};
    Footman *enemyF = new Footman(currentHP,
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
        double currentHP{75.0};
        int movementSpeed{4};
        sf::Vector2f direction{0, 0};
        int attackRange{10};
        int attackSpeed{10};
        int const XP_DROP{10};
        double damage{5};
        int score{3};
        double explodeRange{60};
        double explodeDamage{30};
        int explodeCountdown{20};
        float agroRange{300};
        Kaboom *enemyK = new Kaboom(currentHP,
                                    movementSpeed,
                                    spawnPoint,
                                    attackRange,
                                    attackSpeed,
                                    XP_DROP,
                                    damage,
                                    score,
                                    player,
                                    explodeRange,
                                    explodeDamage,
                                    explodeCountdown,
                                    agroRange);
        Map::instance()->addEntity(enemyK);
    }
}

void Spawner::addArcher()
{
    if (canSpawnArcher)
    {
        chooseSpawnPos();
        double currentHP{100.0};
        int movementSpeed{2};
        sf::Vector2f direction{0, 0};
        int attackRange{10};
        int attackSpeed{10};
        int const XP_DROP{10};
        double damage{5};
        int score{2};
        double velocity{3};
        attackRange = 350;
        Archer *enemyA = new Archer(currentHP,
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
