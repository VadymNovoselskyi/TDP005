#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Obstacle.h"

class TileManager
{
  public:
    static TileManager *instance();
    static TileManager *init(std::string const &tileMapPath);
    static void deleteInstance();

    void drawTiles(sf::RenderWindow *window) const;
    [[nodiscard]] std::vector<Obstacle *> getObstacles() const;

  private:
    void generateTiles(std::string const &tileMapPath);

    TileManager(std::string const &tileMapPath);
    ~TileManager();
    static TileManager *instancePtr;

    int static const TILE_SIZE;
    std::vector<sf::RectangleShape> tiles;
    std::vector<Obstacle *> obstacles;
    int columnCount;
    int rowCount;
};

#endif