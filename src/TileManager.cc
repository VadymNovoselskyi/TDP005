#include "TileManager.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

int const TileManager::TILE_SIZE{32};
TileManager *TileManager::instancePtr{nullptr};

// Static methods:
TileManager *TileManager::instance()
{
    if (TileManager::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init TileManager before calling instance on it");
    }
    return TileManager::instancePtr;
}

TileManager *TileManager::init(std::string const &tileMapPath)
{
    TileManager::instancePtr = new TileManager(tileMapPath);
    return TileManager::instancePtr;
}

void TileManager::deleteInstance()
{
    delete TileManager::instancePtr;
    TileManager::instancePtr = nullptr;
}

// Instance methods
TileManager::TileManager(std::string const &tileMapPath)
    : tiles{}, obstacles{}, columnCount{}, rowCount{}, mapRect{}
{
    generateTiles(tileMapPath);

    mapRect.setSize(sf::Vector2f{static_cast<float>(columnCount * TILE_SIZE),
                                 static_cast<float>(rowCount * TILE_SIZE)});
}

TileManager::~TileManager() = default;

std::vector<Obstacle *> TileManager::getObstacles() const
{
    return obstacles;
}

bool TileManager::outOfBounds(sf::Sprite const *sprite) const
{
    auto mapBound{mapRect.getGlobalBounds()};
    auto spriteRect{sprite->getGlobalBounds()};

    return spriteRect.left < mapBound.left || spriteRect.top < mapBound.top ||
           spriteRect.left + spriteRect.width > mapBound.left + mapBound.width ||
           spriteRect.top + spriteRect.height > mapBound.top + mapBound.height;
}

sf::Vector2f TileManager::getMapDimensions() const
{
    return mapRect.getSize();
}

void TileManager::drawTiles(sf::RenderWindow *window) const
{
    auto viewCenter = window->getView().getCenter();
    auto viewSize = window->getView().getSize();
    auto viewRect = sf::FloatRect{static_cast<float>(viewCenter.x - viewSize.x / 2.0),
                                  static_cast<float>(viewCenter.y - viewSize.y / 2.0),
                                  viewSize.x,
                                  viewSize.y};

    for (int column_idx{std::max(static_cast<int>(std::floor(viewRect.left / TILE_SIZE)), 0)};
         column_idx <
         std::min(static_cast<int>(std::ceil((viewRect.left + viewRect.width) / TILE_SIZE)),
                  columnCount);
         column_idx++)
    {
        for (int row_idx{std::max(static_cast<int>(std::floor(viewRect.top / TILE_SIZE)), 0)};
             row_idx <
             std::min(static_cast<int>(std::ceil((viewRect.top + viewRect.height) / TILE_SIZE)),
                      rowCount);
             row_idx++)
        {
            window->draw(tiles.at(row_idx * columnCount + column_idx));
        }
    }
}

void TileManager::generateTiles(std::string const &tileMapPath)
{
    std::ifstream file{tileMapPath};

    if (!file.is_open())
    {
        throw std::logic_error("Couldn't open the tilemap");
    }
    // TODO: Optimize drawing with sf::VertexArray

    // The loop is inspired from
    // https://stackoverflow.com/questions/12133379/c-using-ifstream-with-getline
    int lineCount{0};
    for (std::string line{}; std::getline(file, line, '\n');)
    {
        std::istringstream lineStream{line};
        int wordCount{0};
        for (std::string word{}; lineStream >> word;)
        {
            sf::Texture *texture = TextureManager::instance()->getTexture(word + ".png");
            sf::Vector2f position = sf::Vector2f{static_cast<float>(wordCount * TILE_SIZE),
                                                 static_cast<float>(lineCount * TILE_SIZE)};

            sf::RectangleShape tile{};

            tile.setSize({TILE_SIZE, TILE_SIZE});
            tile.setPosition(position);
            tile.setTexture(texture);

            if (word.find("obstacle-") != std::string::npos)
            {
                std::string obstacleType = word.substr(9);
                if (obstacleType != "wall" && obstacleType != "gas")
                {
                    obstacles.push_back(new Obstacle{texture, position});
                }
            }

            tiles.push_back(tile);

            wordCount++;
        }
        lineCount++;
        columnCount = std::max(columnCount, wordCount);
    }
    rowCount = lineCount;
}
