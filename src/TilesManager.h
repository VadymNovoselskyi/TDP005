#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Obstacle.h"

class TilesManager
{
  public:
    static TilesManager *instance();
    static TilesManager *init(std::string const &tileMapPath);
    static void deleteInstance();

    bool outOfBorders(sf::Sprite const *sprite) const;
    bool inDangerZone(sf::Sprite const *sprite) const;

    void drawTiles(sf::RenderWindow *window) const;

    std::vector<Obstacle *> getObstacles() const;
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