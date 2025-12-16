#include "ExperienceManager.h"

#include <iostream>

std::vector<int> const ExperienceManager::LEVELS_PROGRESSION{
    25, 75, 200, 400, 700, 1300, 2400, 3500, 999999999};

ExperienceManager::ExperienceManager() : levelUps{}, currentXp{0}, level{0}
{
    levelUps = {{LevelUpChoice::HP, "Buff your HP stats", []() {}},
                {LevelUpChoice::SPEED, "Buff your SPEED stats", []() {}},
                {LevelUpChoice::DAMAGE, "Buff your DAMAGE stats", []() {}},
                {LevelUpChoice::WEAPON, "Choose a random WEAPON", []() {}}};
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

std::vector<LevelUpInfo> ExperienceManager::chooseLevelUps(bool weaponsAvailable) const
{
    // This asumes the weapon level up always lies last (not best, but kinda ok)
    return weaponsAvailable ? levelUps
                            : std::vector<LevelUpInfo>{levelUps.begin(), levelUps.end() - 1};
}

double ExperienceManager::getXpFilled() const
{
    return currentXp == 0
               ? 0
               : static_cast<double>(currentXp) / static_cast<double>(LEVELS_PROGRESSION.at(level));
}
