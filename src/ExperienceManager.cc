#include "ExperienceManager.h"

#include <algorithm>
#include <iostream>

std::vector<int> const ExperienceManager::LEVELS_PROGRESSION{
    0, 1000, 2500, 5000, 8000, 15000, 24000, 35000, 999999999};

ExperienceManager::ExperienceManager() : levelUps{}, currentXp{0}, level{0}
{
    levelUps = {{LevelUpChoice::HP, "Buff your HP stats", []() {}},
                {LevelUpChoice::SPEED, "Buff your SPEED stats", []() {}},
                {LevelUpChoice::DAMAGE, "Buff your DAMAGE stats", []() {}},
                {LevelUpChoice::WEAPON, "Choose a WEAPON", []() {}}};
}

void ExperienceManager::setCallbacks(
    std::map<LevelUpChoice, std::function<void()>> const &levelUpCallbacks)
{
    for (LevelUpInfo &levelUp : levelUps)
    {
        levelUp.onClick = levelUpCallbacks.at(levelUp.levelUpChoice);
    }
}

void ExperienceManager::resetState()
{
    currentXp = 0;
    level = 0;
}

bool ExperienceManager::gainXp(int gainedXP)
{
    currentXp += gainedXP;
    if (currentXp >= LEVELS_PROGRESSION.at(level))
    {
        level++;
        return true;
    }

    return false;
}

std::vector<LevelUpInfo> ExperienceManager::chooseLevelUps() const
{
    return levelUps;
}

int ExperienceManager::getXpFilled() const
{
    return static_cast<int>(currentXp / LEVELS_PROGRESSION.at(level));
}
