#include "ExperienceManager.h"

#include <iostream>

std::vector<int> const ExperienceManager::LEVELS_PROGRESSION{
    0, 1000, 2500, 5000, 8000, 15000, 24000, 35000, 999999999};
std::vector<LevelUpInfo> const ExperienceManager::LEVEL_UPS{
    {LevelUpChoice::HP,
     "Buff your HP stats",
     []() { std::cout << "HP buff selected" << std::endl; }},
    {LevelUpChoice::SPEED,
     "Buff your SPEED stats",
     []() { std::cout << "SPEED buff selected" << std::endl; }},
    {LevelUpChoice::DAMAGE,
     "Buff your DAMAGE stats",
     []() { std::cout << "DAMAGE buff selected" << std::endl; }},
    {LevelUpChoice::WEAPON,
     "Choose a WEAPON",
     []() { std::cout << "WEAPON buff selected" << std::endl; }}};

ExperienceManager::ExperienceManager() : currentXp{}, level{}
{
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
    return LEVEL_UPS;
}