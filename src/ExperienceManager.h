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

/**
 * Manages player XP and level progression
 *
 * ExperienceManager is responsible for:
 * - Tracking current XP and level
 * - Determining when level ups occur based on progression vector
 * - Providing level up choices to the player
 * - Calculating XP fill percentage (0-1) for display
 */
class ExperienceManager
{
  public:
    ExperienceManager();
    
    /**
     * Set callback functions for each level up choice type
     *
     * @param levelUpCallbacks Map of level up choices to their callback functions
     */
    void setCallbacks(std::map<LevelUpChoice, std::function<void()>> const &levelUpCallbacks);
    
    /**
     * Reset experience and level to initial state
     */
    void resetState();

    /**
     * Add XP and check if level up occurs
     *
     * @param gainedXp Amount of XP to add
     * @return true if level up occurred
     */
    bool gainXp(int gainedXp);
    
    /**
     * Get available level up choices based on weapon availability
     *
     * @param weaponsAvailable Whether weapon upgrades are available
     * @return Vector of LevelUpInfo options
     */
    std::vector<LevelUpInfo> chooseLevelUps(bool weaponsAvailable) const;

    /**
     * Calculate the current XP fill percentage for the current level
     *
     * @return Percentage (0.0 to 1.0) of XP filled for current level
     */
    double getXpFilled() const;

  private:
    std::vector<int> static const LEVELS_PROGRESSION;
    std::vector<LevelUpInfo> levelUps;
    int currentXp;
    int level;
};

#endif
