#include "Spawner.h"
//#include <iostream>

#include <cstdlib>

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
    sf::Vector2f newSpawnPos{randomX, randomY};

    float pRight{playerWindow.x + (Window::getWindowWidth() / 2.0F)}; // 512
    float pLeft{-pRight};
    float pUpp{playerWindow.y + (Window::getWindowHeight() / 2.0F)}; // 384
    float pDown{-pUpp};

    bool insideX =
        (newSpawnPos.x > pLeft &&
         newSpawnPos.x < pRight); // tar insparaskion från w3schools
                                 // https://www.w3schools.com/cpp/cpp_operators_logical.asp
    bool insideY = (newSpawnPos.y > pDown && newSpawnPos.y < pUpp);
 
    bool xCrash = (randomX < 160 || randomX > 2200);
    bool yCrash = (randomY < 160 || randomY > 2200);
    //std::cout<<"inan"<<std::endl;
    if (insideX && insideY || xCrash || yCrash)
    {
        //std::cout<<"inne"<<std::endl;
        chooseSpawnPos();
    }
    else
    {
        spawnPoint = newSpawnPos;
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
    double currentHP{100.0};
    int movementSpeed{4};
    sf::Vector2f direction{0, 0};
    int attackRange{20};
    int attackSpeed{10};
    int const XP_DROP{5};
    double damage{15};
    int score{2};

    //sf::Vector2f spawnPoint {160,160};
    //sf::Vector2f spawnPoint {2200,2200};
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
        double currentHP{75.0};
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
        double currentHP{100.0};
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
