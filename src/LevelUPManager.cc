#include "LevelUPManager.h"
LevelUPManager::LevelUPManager(int xp, int maxXP) : xp{xp}, maxXP{maxXP}
{
}
void LevelUPManager::setXP(int gainedXP)
{
    xp += gainedXP;
 
}

bool LevelUPManager::hasLeveldUP()
{
    return xp >= maxXP;
}
void LevelUPManager::levelupOptions()
{
    StateMachine::instance()->startLevelUp();
}