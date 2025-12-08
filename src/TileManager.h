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

    void drawTilesInView(sf::Window *window) const;
    [[nodiscard]] std::vector<Obstacle *> getObstacles() const;

  private:
    void generateTiles(std::string const &tileMapPath);

    TileManager(std::string const &tileMapPath);
    ~TileManager();
    static TileManager *instancePtr;

    sf::VertexArray tiles;
    std::vector<Obstacle *> obstacles;
};

#endif