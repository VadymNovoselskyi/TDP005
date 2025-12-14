#include "TilesManager.h"

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

int const TilesManager::TILE_SIZE{32};
TilesManager *TilesManager::instancePtr{nullptr};

// Static methods:
TilesManager *TilesManager::instance()
{
    if (TilesManager::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init TilesManager before calling instance on it");
    }
    return TilesManager::instancePtr;
}

TilesManager *TilesManager::init(std::string const &tileMapPath)
{
    TilesManager::instancePtr = new TilesManager(tileMapPath);
    return TilesManager::instancePtr;
}

void TilesManager::deleteInstance()
{
    delete TilesManager::instancePtr;
    TilesManager::instancePtr = nullptr;
}

// Instance methods
TilesManager::TilesManager(std::string const &tileMapPath)
    : tiles{}, obstacles{}, columnCount{}, rowCount{}, wallCount{}, dangerZoneCount{}, mapRect{}
{
    generateTiles(tileMapPath);

    mapRect.setSize(sf::Vector2f{static_cast<float>((columnCount - (2 * wallCount)) * TILE_SIZE),
                                 static_cast<float>((rowCount - (2 * wallCount)) * TILE_SIZE)});
    mapRect.setPosition(
        {static_cast<float>(wallCount * TILE_SIZE), static_cast<float>(wallCount * TILE_SIZE)});

    safeZoneRect.setSize(sf::Vector2f{
        static_cast<float>((columnCount - (2 * (wallCount + dangerZoneCount))) * TILE_SIZE),
        static_cast<float>((rowCount - (2 * (wallCount + dangerZoneCount))) * TILE_SIZE)});
    safeZoneRect.setPosition({static_cast<float>((wallCount + dangerZoneCount) * TILE_SIZE),
                              static_cast<float>((wallCount + dangerZoneCount) * TILE_SIZE)});
}

std::vector<Obstacle *> TilesManager::getObstacles() const
{
    return obstacles;
}

bool TilesManager::outOfBorders(sf::Sprite const *sprite) const
{
    auto mapBorders{mapRect.getGlobalBounds()};
    auto spriteRect{sprite->getGlobalBounds()};

    return spriteRect.left < mapBorders.left || spriteRect.top < mapBorders.top ||
           spriteRect.left + spriteRect.width > mapBorders.left + mapBorders.width ||
           spriteRect.top + spriteRect.height > mapBorders.top + mapBorders.height;
}

bool TilesManager::inDangerZone(sf::Sprite const *sprite) const
{
    auto safeZoneBounds{safeZoneRect.getGlobalBounds()};
    auto spriteRect{sprite->getGlobalBounds()};

    return spriteRect.left < safeZoneBounds.left || spriteRect.top < safeZoneBounds.top ||
           spriteRect.left + spriteRect.width > safeZoneBounds.left + safeZoneBounds.width ||
           spriteRect.top + spriteRect.height > safeZoneBounds.top + safeZoneBounds.height;
}

sf::Vector2f TilesManager::getMapDimensions() const
{
    return mapRect.getSize();
}

void TilesManager::drawTiles(sf::RenderWindow *window) const
{
    auto viewCenter = window->getView().getCenter();
    auto viewSize = window->getView().getSize();
    auto viewRect = sf::FloatRect{static_cast<float>(viewCenter.x - viewSize.x / 2.0),
                                  static_cast<float>(viewCenter.y - viewSize.y / 2.0),
                                  viewSize.x,
                                  viewSize.y};

    for (int columnIdx{std::max(static_cast<int>(std::floor(viewRect.left / TILE_SIZE)), 0)};
         columnIdx <
         std::min(static_cast<int>(std::ceil((viewRect.left + viewRect.width) / TILE_SIZE)),
                  columnCount);
         columnIdx++)
    {
        for (int rowIdx{std::max(static_cast<int>(std::floor(viewRect.top / TILE_SIZE)), 0)};
             rowIdx <
             std::min(static_cast<int>(std::ceil((viewRect.top + viewRect.height) / TILE_SIZE)),
                      rowCount);
             rowIdx++)
        {
            window->draw(tiles.at(rowIdx * columnCount + columnIdx));
        }
    }
}

std::string repeat(std::string const &str, int count)
{
    std::string result{};
    for (int i{0}; i < count; ++i)
    {
        result += str;
    }
    return result;
}

void TilesManager::generateTiles(std::string const &tileMapPath)
{
    std::ifstream file{tileMapPath};

    if (!file.is_open())
    {
        throw std::logic_error("Couldn't open the tilemap");
    }

    std::string bordersDefinition{};
    std::getline(file, bordersDefinition);

    std::istringstream borderDefStream{bordersDefinition};
    borderDefStream >> columnCount >> rowCount >> wallCount >> dangerZoneCount;
    rowCount += 2 * (wallCount + dangerZoneCount);
    columnCount += 2 * (wallCount + dangerZoneCount);

    int rowIndex{0};
    insertWallRow(wallCount, columnCount, rowIndex);
    rowIndex += wallCount;

    insertDangerZoneRow(dangerZoneCount, wallCount, columnCount - (2 * wallCount), rowIndex);
    rowIndex += dangerZoneCount;

    // The loop is inspired from
    // https://stackoverflow.com/questions/12133379/c-using-ifstream-with-getline
    for (std::string line{}; std::getline(file, line);)
    {
        std::string lineWithBorders{repeat("wall ", wallCount) + repeat("gas ", dangerZoneCount) +
                                    line + " " + repeat("gas ", dangerZoneCount) +
                                    repeat("wall ", wallCount)};

        processLine(lineWithBorders, rowIndex);
        rowIndex++;
    }

    insertDangerZoneRow(dangerZoneCount, wallCount, columnCount - (2 * wallCount), rowIndex);
    rowIndex += dangerZoneCount;

    insertWallRow(wallCount, columnCount, rowIndex);
}

void TilesManager::insertWallRow(int linesCount, int wallsCount, int rowIndex)
{
    std::string wallsRow{repeat("wall ", wallsCount)};
    for (int i{0}; i < linesCount; ++i)
    {
        processLine(wallsRow, rowIndex);
        rowIndex++;
    }
}

void TilesManager::insertDangerZoneRow(int linesCount,
                                       int wallsCount,
                                       int dangerZoneCount,
                                       int rowIndex)
{
    std::string dangerZoneRow{repeat("wall ", wallsCount) + repeat("gas ", dangerZoneCount) +
                              repeat("wall ", wallsCount)};

    for (int i{0}; i < linesCount; ++i)
    {
        processLine(dangerZoneRow, rowIndex);
        rowIndex++;
    }
}

void TilesManager::processLine(std::string const &line, int rowIndex)
{
    std::istringstream lineStream{line};
    int wordCount{0};

    for (std::string word{}; lineStream >> word;)
    {
        sf::Texture *texture = TextureManager::instance()->getTexture(word + ".png");
        sf::Vector2f position = sf::Vector2f{static_cast<float>(wordCount * TILE_SIZE),
                                             static_cast<float>(rowIndex * TILE_SIZE)};

        sf::RectangleShape tile{};

        tile.setSize({TILE_SIZE, TILE_SIZE});
        tile.setPosition(position);
        tile.setTexture(texture);
        tiles.push_back(tile);

        if (word.find("obstacle-") != std::string::npos)
        {
            obstacles.push_back(new Obstacle{texture, position});
        }
        wordCount++;
    }
}
