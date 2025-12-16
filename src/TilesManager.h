#ifndef TILES_MANAGER_H
#define TILES_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Obstacle.h"

/**
 * Manages tile map generation and map borders
 *
 * TilesManager is responsible for:
 * - Loading the tile map from file and generating tiles
 * - Creating obstacles from the tile map
 * - Keeping track and checking if a sprite is outside map borders and safe zone borders
 * - Drawing visible tiles in the current view
 */
class TilesManager
{
  public:
    /**
     * Get the TilesManager singleton instance
     * The instance must be created with init() before calling this function
     *
     * @return Pointer to the singleton TilesManager instance
     * @throws std::logic_error if the TilesManager has not been initialized
     */
    static TilesManager *instance();

    /**
     * Create and initialize the TilesManager singleton
     *
     * @param tileMapPath Path to the tile map file
     * @return Pointer to the created singleton TilesManager instance
     */
    static TilesManager *init(std::string const &tileMapPath);

    /**
     * Destroy the TilesManager singleton instance
     */
    static void deleteInstance();

    /**
     * Check if a sprite is outside the map borders
     *
     * @param sprite Sprite to check
     * @return true if the sprite is outside the map borders
     */
    bool outOfBorders(sf::Sprite const *sprite) const;

    /**
     * Check if a sprite is inside the danger zone
     *
     * @param sprite Sprite to check
     * @return true if the sprite is in the danger zone
     */
    bool inDangerZone(sf::Sprite const *sprite) const;

    /**
     * Draw tiles that are within the current view
     *
     * @param window The RenderWindow to draw into
     */
    void drawTiles(sf::RenderWindow *window) const;

    /**
     * Get all obstacles created from the tile map
     *
     * @return Vector of obstacle pointers
     */
    std::vector<Obstacle *> getObstacles() const;

    /**
     * Get the map dimensions
     *
     * @return Map width and height as Vector2f
     */
    sf::Vector2f getMapDimensions() const;

  private:
    TilesManager(std::string const &tileMapPath);
    static TilesManager *instancePtr;

    void generateTiles(std::string const &tileMapPath);
    void insertWallRow(int linesCount, int wallsCount, int rowIndex);
    void insertDangerZoneRow(int linesCount, int wallsCount, int dangerZoneCount, int rowIndex);
    void processLine(std::string const &line, int rowIndex);

    int static const TILE_SIZE;
    std::vector<sf::RectangleShape> tiles;
    std::vector<Obstacle *> obstacles;

    int columnCount;
    int rowCount;
    int wallCount;
    int dangerZoneCount;

    sf::RectangleShape mapRect;
    sf::RectangleShape safeZoneRect;
};

#endif