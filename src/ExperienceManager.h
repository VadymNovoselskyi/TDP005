#ifndef EXPERIENCE_MANAGER_H
#define EXPERIENCE_MANAGER_H

#include <vector>

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
    LevelUpChoice levelUpChoice;
    std::string description;
    std::function<void()> onClick;
};

class ExperienceManager
{
  public:
    ExperienceManager();
    void setCallbacks(std::map<LevelUpChoice, std::function<void()>> const &levelUpCallbacks);
    void resetState();

    bool gainXp(int gainedXp);
    std::vector<LevelUpInfo> chooseLevelUps() const;

  private:
    std::vector<int> static const LEVELS_PROGRESSION;
    std::vector<LevelUpInfo> levelUps;

    int currentXp;
    int level;
};

#endif /*EXPERIENCE_MANAGER_H*/
