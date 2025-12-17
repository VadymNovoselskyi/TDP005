#ifndef WEAPONS_MANAGER_H
#define WEAPONS_MANAGER_H

#include <string>
#include <vector>

#include "Weapon.h"

/**
 * Manages the players equipped and unequipped weapons
 *
 * WeaponsManager is responsible for:
 * - Storing equipped weapons and available weapons
 * - Shooting with equipped weapons
 * - Updating position and rotation for equipped weapons
 * - Equipping a specific weapon or a random weapon
 */
class WeaponsManager
{
  public:
    /**
     * Create a WeaponsManager with all weapons available as unequipped
     */
    WeaponsManager();

    /**
     * Destroy the WeaponsManager and delete stored weapons
     */
    ~WeaponsManager();

    /**
     * Reset equipped weapons back to unequipped
     */
    void resetState();

    /**
     * Try to shoot with all equipped weapons
     */
    void shoot();

    /**
     * Set the position for all equipped weapons
     *
     * @param pos Position to set on all equipped weapons
     */
    void setWeaponsPos(sf::Vector2f const &pos);

    /**
     * Set rotation for all equipped weapons
     *
     * @param rotaiton Rotation to set on all equipped weapons
     */
    void setWeaponsRotation(double rotaiton);

    /**
     * Equip a weapon by name
     *
     * @param name Name of the weapon to equip
     */
    void receiveNewWeapon(std::string const &name);

    /**
     * Equip a random weapon if any are available
     */
    void receiveRandomWeapon();

    /**
     * Check if there are any unequipped weapons left to get
     *
     * @return true if there are unequipped weapons available
     */
    bool canGetNewWeapon() const;

  private:
    /**
     * Move a weapon from unequipped to equipped list
     *
     * @param weapon Weapon pointer to equip
     */
    void equipWeapon(Weapon *weapon);

    std::vector<Weapon *> equipedWeapons;
    std::vector<Weapon *> unequipedWeapons;
};

#endif