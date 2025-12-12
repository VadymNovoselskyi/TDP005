#include "Map.h"

#include <algorithm>
#include <iostream>

#include "TileManager.h"
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
    auto obstaclesSize{TileManager::instance()->getObstacles().size()};
    for (auto it{entities.begin() + obstaclesSize + 1}; it != entities.end(); ++it)
    {
        delete *it;
    }

    entities.erase(entities.begin() + obstaclesSize + 1, entities.end());
}

void Map::deleteInstance()
{
    // std::cout << "Deleting the instance" << std::endl;
    delete Map::instancePtr;
    Map::instancePtr = nullptr;
}

void Map::handelUpdate(sf::RenderWindow *window)
{
    for (Entity *e : entities)
    {
        e->move();
    }
    player->updateRotation(window);

    // TODO: watching walls and gas is too expensive, come up with other ways to do it
    for (auto it1{entities.begin()}; it1 != entities.end(); ++it1) // de som är i loopen är
    // tagen från tdp004 https://www.ida.liu.se/~TDP004/current/sal/slides/tdp004_9.pdf s.20

    {
        if (TileManager::instance()->outOfBounds(*it1))
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

    if (entitiesToRemove.size())
    {
        // std::cout << "Removing from entities " << entitiesToRemove.size() << std::endl;
        for (auto it = entitiesToRemove.rbegin(); it != entitiesToRemove.rend(); ++it)
        {
            // std::cout << *it << std::endl;
            delete *(*it);
            entities.erase(*it);
        }
        entitiesToRemove.clear();
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
}

void Map::addEntity(Entity *e)
{
    entities.push_back(e);
}

void Map::removeEntity(Entity *e)
{
    // std::cout << "Request to delete: " << e->getTag() << std::endl;
    // std::cout << "Request to delete mem address: " << e << std::endl;
    // for (auto e : entities)
    // {
    //     std::cout << e << std::endl;
    // }
    // std::cout << "After delete" << std::endl;

    auto entitieToDelete =
        std::find_if(entities.begin(), entities.end(), [&e](Entity *e1) { return e == e1; });
    auto existingEntity = std::find_if(entitiesToRemove.begin(),
                                       entitiesToRemove.end(),
                                       [&entitieToDelete](std::vector<Entity *>::iterator e1)
                                       { return entitieToDelete == e1; });
    if (entitieToDelete != entities.end() && existingEntity == entitiesToRemove.end())
    {
        entitiesToRemove.push_back(entitieToDelete);
    }
    // std::remove_if(entities.begin(), entities.end(), [&e](Entity *e1) { return e == e1; });
    // for (auto e : entities)
    // {
    //     std::cout << e << std::endl;
    // }
}

Entity *Map::getClosestEnemy()
{
    Entity *enemy{nullptr};
    double minPos{999999.0};
    for (Entity *e : entities)
    {
        if (e->getTag() != "enemy")
        {
            continue;
        }

        // get abs x and y fore e
        double eX = abs(e->getPosition().x + player->getPosition().x);
        double eY = abs(e->getPosition().y + player->getPosition().y);

        double eXY = eX + eY;

        if (eXY <= minPos)
        {
            // set new enemy
            enemy = e;
            minPos = eXY;
        }
    }
    return enemy;
}

Map::Map(Player *player, std::vector<Obstacle *> const &obstacles)
    : view{new sf::View{{static_cast<float>(Window::getWindowWidth()) / 2.0F,
                         static_cast<float>(Window::getWindowHeight()) / 2.0F},
                        {static_cast<float>(Window::getWindowWidth()),
                         static_cast<float>(Window::getWindowHeight())}}},
      player{player}, entities{}, entitiesToRemove{}
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
