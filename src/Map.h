#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Obstacle.h"
#include "Player.h"

/**
 * Declares the Map singleton which owns and updates/draws all in-world entities
 *
 * Map is responsible for:
 * - Keeping a list of active `Entity` objects (player, obstacles, enemies, projectiles, ...)
 * - Updating movement, border checks, and collision callbacks each tick
 * - Drawing the world using an `sf::View` centered on the player
 */
class Map
{
  public: // singelton taget from vadyms kod
    /**
     * Get the Map singleton instance
     * The instance must be created with init() before calling this function
     *
     * @return Pointer to the singleton Map instance
     * @throws std::logic_error if the Map has not been initialized
     */
    static Map *instance();

    /**
     * Create and initialize the Map singleton
     * Stores the provided player and obstacles as entities in the world
     *
     * @param player Pointer to the Player entity (must remain valid for the lifetime of the Map)
     * @param obstacles List of obstacle pointers to populate the map with
     * @return Pointer to the created singleton Map instance
     */
    static Map *init(Player *player, std::vector<Obstacle *> const &obstacles);

    /**
     * Destroy the Map singleton instance and reset the stored pointer
     */
    static void deleteInstance();

    /**
     * Reset the map state by deleting all entities except the player and static obstacles
     * This is used when restarting so entities (enemies, projectiles, etc) are removed
     */
    void resetState();

    /**
     * Update all entities for one tick: movement, collision checks and deletions
     *
     * @param window The render window used for mouse position/rotation update
     */
    void handelUpdate(sf::RenderWindow *window);

    /**
     * Draw the world (all entities) using a view centered on the player
     * Also draws player HUD when not in leaderboard state
     *
     * @param window The RenderWindow to draw into
     */
    void draw(sf::RenderWindow *window) const;

    /**
     * Schedule an entity to be added to the world
     * The entity is added after the move loop in handelUpdate
     *
     * @param e Pointer to the entity to add
     */
    void addEntity(Entity *e);

    /**
     * Schedule an entity to be removed from the world
     * The entity is deleted and removed after the collision loop in handelUpdate
     *
     * @param e Pointer to the entity to remove
     */
    void removeEntity(Entity *e);

  private:
    /**
     * Construct a Map and populate it with player and obstacles
     *
     * @param player Pointer to Player
     * @param obstacles List of obstacle pointers to add as entities
     */
    Map(Player *player, std::vector<Obstacle *> const &obstacles);

    /**
     * Destroy the Map and delete owned entities
     */
    ~Map();
    static Map *instancePtr;

    sf::View *view;
    Player *player;
    std::vector<Entity *> entities;
    std::vector<Entity *> entitiesToDelete;
    std::vector<Entity *> entitiesToAdd;
};

#endif