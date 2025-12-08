

#include "TileManager.h"

#include <iostream>
#include <stdexcept>

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
TileManager::TileManager(std::string const &tileMapPath) : tiles{}, obstacles{}
{
    generateTiles(tileMapPath);
}

TileManager::~TileManager() = default;

std::vector<Obstacle *> TileManager::getObstacles() const
{
    return obstacles;
}

void TileManager::generateTiles(std::string const &tileMapPath)
{
    // Parse the file and generate the VertexArray and the obstacles
}
