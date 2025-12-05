#include"Enemy.h"

class Spawner
{
    public:
        void spwanEnemies();
        Point choseSpawnPos(Point);

    private:
        vector <Enemy*> enemies;
        double spwanRate;
        Point spwanPoint;
        

};









int main()
{
    return 0;
}