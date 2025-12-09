#ifndef EXPERIENCE_MANAGER_H
#define EXPERIENCE_MANAGER_H

#include <vector>
#include <map>

#include "StateMachine.h"

enum LevelUpChoice
{
    HP,
    SPEED,
    DAMAGE,
    WEAPON
};

struct LevelUpInfo
{
    std::string name;
    std::string description;
    std::function<void()> onClick;
};

class ExperienceManager
{
  public:
    ExperienceManager();

    bool addXp(int xp);

  private:
    std::map<LevelUpChoice, LevelUpInfo> LEVEL_UPS;
    std::vector<int> LEVELS_PROGRESSION;

    int currentXp;
    int level;
};

#endif /*EXPERIENCE_MANAGER_H*/
