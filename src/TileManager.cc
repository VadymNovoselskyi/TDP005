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
TileManager::TileManager(std::string const &tileMapPath)
    : tiles{}, obstacles{}, columnCount{}, rowCount{}
{
    generateTiles(tileMapPath);
}

TileManager::~TileManager() = default;

std::vector<Obstacle *> TileManager::getObstacles() const
{
    return obstacles;
}

sf::Vector2i TileManager::getMapDimensions() const
{
    return sf::Vector2i{columnCount * TILE_SIZE, rowCount * TILE_SIZE};
}

void TileManager::drawTiles(sf::RenderWindow *window) const
{
    auto viewPortCenter = window->getView().getCenter();
    auto viewPortSize = window->getView().getSize();
    auto viewPortRect = sf::FloatRect{static_cast<float>(viewPortCenter.x - viewPortSize.x / 2.0),
                                      static_cast<float>(viewPortCenter.y - viewPortSize.y / 2.0),
                                      viewPortSize.x,
                                      viewPortSize.y};

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
    // TODO: Optimize drawing with sf::VertexArray

    // The loop is taken from
    // https://stackoverflow.com/questions/12133379/c-using-ifstream-with-getline
    int lineCount{0};
    for (std::string line{}; std::getline(file, line, '\n');)
    {
        std::istringstream line_stream{line};
        int wordCount{0};
        for (std::string word{}; line_stream >> word;)
        {
            sf::Texture *texture = TextureManager::instance()->getTexture(word + ".png");
            sf::Vector2f position = sf::Vector2f{static_cast<float>(wordCount * TILE_SIZE),
                                                 static_cast<float>(lineCount * TILE_SIZE)};

            sf::RectangleShape tile{};

            tile.setSize({TILE_SIZE, TILE_SIZE});
            tile.setPosition(position);
            tile.setTexture(texture);

            if (auto idx{word.find("obstacle-")}; idx != std::string::npos)
            {
                std::string obstacleType = word.substr(9);
                Obstacle *obstacle{new Obstacle{
                    texture,
                    position,
                    (obstacleType == "wall" || obstacleType == "gas") ? obstacleType : "obstacle"}};
                obstacles.push_back(obstacle);
            }

            tiles.push_back(tile);

            wordCount++;
        }
        lineCount++;
        columnCount = std::max(columnCount, wordCount);
    }
    rowCount = lineCount;
}
