#include "TileManager.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Window.h"

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
TileManager::TileManager(std::string const &tileMapPath) : tiles{}, obstacles{}
{
    generateTiles(tileMapPath);
}

TileManager::~TileManager() = default;

std::vector<Obstacle *> TileManager::getObstacles() const
{
    return obstacles;
}

void TileManager::drawTiles(sf::RenderWindow *window) const
{
    // auto viewPortCenter = window->getView().getCenter();
    // auto viewPortSize = window->getView().getSize();
    // auto viewPortRect = sf::FloatRect{static_cast<float>(viewPortCenter.x - viewPortSize.x
    // / 2.0),
    //                                   static_cast<float>(viewPortCenter.y - viewPortSize.y
    //                                   / 2.0), viewPortSize.x, viewPortSize.y};

    // int renderedCount{0};
    // for (auto tile : tiles)
    // {
    //     if (viewPortRect.intersects(tile.getGlobalBounds()))
    //     {
    //         window->draw(tile);
    //         renderedCount++;
    //     }
    // }

    auto viewPortCenter = window->getView().getCenter();
    auto viewPortSize = window->getView().getSize();
    auto viewPortRect = sf::FloatRect{static_cast<float>(viewPortCenter.x - viewPortSize.x / 2.0),
                                      static_cast<float>(viewPortCenter.y - viewPortSize.y / 2.0),
                                      viewPortSize.x,
                                      viewPortSize.y};

    // for (int column_idx{std::floor(viewPortRect.left / TILE_SIZE)};
    //      column_idx < std::ceil((viewPortRect.left + viewPortRect.width) / TILE_SIZE);
    //      column_idx++)
    // {
    //     if (column_idx < 0)
    //     {
    //         column_idx = 0;
    //     }

    //     for (int row_idx{std::floor(viewPortRect.top / TILE_SIZE)};
    //          row_idx < std::ceil((viewPortRect.top + viewPortRect.height) / TILE_SIZE);
    //          row_idx++)
    //     {
    //         if (row_idx < 0)
    //         {
    //             row_idx = 0;
    //         }

    //         window->draw(tiles.at(row_idx * columnCount + column_idx));
    //         renderedCount++;
    //     }
    // }

    for (int column_idx{std::max(static_cast<int>(std::floor(viewPortRect.left / TILE_SIZE)), 0)};
         column_idx <
         std::min(static_cast<int>(std::ceil((viewPortRect.left + viewPortRect.width) / TILE_SIZE)),
                  columnCount);
         column_idx++)
    {
        for (int row_idx{std::max(static_cast<int>(std::floor(viewPortRect.top / TILE_SIZE)), 0)};
             row_idx < std::min(static_cast<int>(std::ceil(
                                    (viewPortRect.top + viewPortRect.height) / TILE_SIZE)),
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

    // The loop is taken from
    // https://stackoverflow.com/questions/12133379/c-using-ifstream-with-getline
    int lineCount{0};
    for (std::string line{}; std::getline(file, line, '\n');)
    {
        std::istringstream line_stream{line};
        int wordCount{0};
        for (std::string word{}; line_stream >> word;)
        {
            sf::RectangleShape tile{};

            tile.setSize({TILE_SIZE, TILE_SIZE});
            tile.setPosition(wordCount * TILE_SIZE, lineCount * TILE_SIZE);
            tile.setTexture(TextureManager::instance()->getTexture(word + ".png"));

            tiles.push_back(tile);
            wordCount++;
        }
        lineCount++;
        columnCount = std::max(columnCount, wordCount);
    }
    rowCount = lineCount;
}
