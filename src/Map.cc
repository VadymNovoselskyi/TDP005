#include "Map.h"

#include <algorithm>

#include "TilesManager.h"
#include "Window.h"

Map *Map::instancePtr{nullptr};

Map *Map::instance()
{
    if (Map::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init Map before calling instance on it");
    }
    return Map::instancePtr;
}

Map *Map::init(Player *player, std::vector<Obstacle *> const &obstacles)
{
    Map::instancePtr = new Map(player, obstacles);
    return Map::instancePtr;
}

void Map::resetState()
{
    auto obstaclesSize{TilesManager::instance()->getObstacles().size()};
    for (auto it{entities.begin() + obstaclesSize + 1}; it != entities.end(); ++it)
    {
        delete *it;
    }

    entities.erase(entities.begin() + obstaclesSize + 1, entities.end());
}

void Map::deleteInstance()
{
    delete Map::instancePtr;
    Map::instancePtr = nullptr;
}

void Map::handelUpdate(sf::RenderWindow *window)
{
    for (Entity *e : entities)
    {
        e->move();
    }

    // Separate loop to add entities to avoid modifying the vector while iterating over it
    for (auto e : entitiesToAdd)
    {
        entities.push_back(e);
    }
    entitiesToAdd.clear();

    player->updateRotation(window);
    if (TilesManager::instance()->inDangerZone(player))
    {
        player->takeDamage(0.2);
    }

    // Loopens definition ärtagen från tdp004
    // https://www.ida.liu.se/~TDP004/current/sal/slides/tdp004_9.pdf s.20

    // Loop through all entities and check for collisions with borders and other entities
    for (auto it1{entities.begin()}; it1 != entities.end(); ++it1)
    {
        if (TilesManager::instance()->outOfBorders((*it1)->getGlobalBounds()))
        {

            (*it1)->onBorderCollision();
        }

        for (auto it2{it1 + 1}; it2 != entities.end(); ++it2)
        {
            if ((*it1)->getGlobalBounds().intersects((*it2)->getGlobalBounds()))
            {
                (*it1)->onCollision(*it2);
                (*it2)->onCollision(*it1);
            }
        }
    }

    // Remove entities the collision loop to avoid modifying the vector while iterating over it
    if (entitiesToDelete.size() > 0)
    {
        for (auto e : entitiesToDelete)
        {
            auto entitieItToDelete = std::find_if(
                entities.begin(), entities.end(), [&e](Entity *e1) { return e == e1; });
            delete e;
            entities.erase(entitieItToDelete);
        }
        entitiesToDelete.clear();
    }
}

void Map::draw(sf::RenderWindow *window) const
{
    view->setCenter(player->getPosition());
    window->setView(*view);

    for (Entity *e : entities)
    {
        e->draw(window);
    }
    player->draw(window);

    if (StateMachine::instance()->state() != GameState::LEADERBOARD &&
        StateMachine::instance()->state() != GameState::IN_START_MENU)
    {
        player->drawInfo(window);
    }
}

void Map::addEntity(Entity *e)
{
    entitiesToAdd.push_back(e);
}

void Map::removeEntity(Entity *e)
{
    auto entitieItToDelete =
        std::find_if(entities.begin(), entities.end(), [&e](Entity *e1) { return e == e1; });
    auto existingEntitieItToDelete = std::find_if(
        entitiesToDelete.begin(), entitiesToDelete.end(), [&e](Entity *e1) { return e == e1; });

    // Add the entity to the deletion list if it exists in the entities vector and not yet in the
    // deletion list
    if (entitieItToDelete != entities.end() && existingEntitieItToDelete == entitiesToDelete.end())
    {
        entitiesToDelete.push_back(*entitieItToDelete);
    }
}

Map::Map(Player *player, std::vector<Obstacle *> const &obstacles)
    : view{new sf::View{{static_cast<float>(Window::getWindowWidth()) / 2.0F,
                         static_cast<float>(Window::getWindowHeight()) / 2.0F},
                        {static_cast<float>(Window::getWindowWidth()),
                         static_cast<float>(Window::getWindowHeight())}}},
      player{player}, entities{}, entitiesToDelete{}, entitiesToAdd{}
{
    entities.push_back(player);
    for (Obstacle *obstacle : obstacles)
    {
        entities.push_back(obstacle);
    }
}

Map::~Map()
{
    for (Entity *e : entities)
    {
        delete e;
    }
    player = nullptr;

    delete view;
    view = nullptr;
}
