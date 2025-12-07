#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class TileManager
{
  public:
    static TileManager *instance();
    static TileManager *init(std::vector<std::string> tilesIds, int columns);
    static void deleteInstance();

    void drawTilesInView(sf::Window *window) const;

  private:
    void generateTiles(std::vector<std::string> tilesIds, int columns);

    TileManager(std::vector<std::string> tilesIds, int columns);
    ~TileManager();
    static TileManager *instancePtr;

    sf::VertexArray tiles;
};

#endif