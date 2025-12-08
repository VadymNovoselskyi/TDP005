#ifndef LEVELUPMANAGER_H
#define LEVELUPMANAGER_H
#include "StateMachine.h"

enum Choises // levelup choise
{
    HP,
    SPEED,
    DAMAGE,
    WEAPON
};

class LevelUPManager
{
  public:
    LevelUPManager(int xp, int maxXP);
    void setXP(int xp);
    bool hasLeveldUP();
    void levelupOptions();

  private:
    int xp;
    int maxXP;
};

#endif /*LEVELUPMANAGER_H*/

// metod för att kolla om spelaren levlat up --
// metod för att byta game status till level up
// metod för att få mer xp