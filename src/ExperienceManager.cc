#include "ExperienceManager.h"

ExperienceManager::ExperienceManager(int xp, int maxXP) : xp{xp}, maxXP{maxXP}
{
}
void ExperienceManager::setXP(int gainedXP)
{
    xp += gainedXP;
 
}

bool ExperienceManager::hasLeveldUP()
{
    return xp >= maxXP;
}
void ExperienceManager::levelupOptions()
{
    StateMachine::instance()->startLevelUp();
}