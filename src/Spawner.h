#include"Enemy.h"
#include"Map.h"
#include <vector>

class Spawner
{
    public:
        Spawner(double spawnRate);
        void spwanEnemies();
        sf::Vector2f choseSpawnPos();

    private:
        std::vector <Enemy*> enemies;
        double spwanRate;
        sf::Vector2f spwanPoint;
        

};


