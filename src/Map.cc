#include "Map.h"

#include <algorithm>
#include <iostream>

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
    // std::cout << "Deleting the instance" << std::endl;
    delete Map::instancePtr;
    Map::instancePtr = nullptr;
}

void Map::handelUpdate(sf::RenderWindow *window)
{
    // std::cout << "Starting the handleUpdate func" << std::endl;
    // std::cout << "Entities before move: " << entities.size() << std::endl;
    // for (auto e : entities)
    // {
    //     std::cout << e << std::endl;
    // }

    // std::cout << "Starting the move loop" << std::endl;
    // std::cout << "Entities size: " << entities.size() << std::endl;
    for (Entity *e : entities)
    {
        // std::cout << "Moving in loop: " << count << std::endl;
        // std::cout << "Moving entity mem: " << e << std::endl;
        // std::cout << "Moving entity tag: " << e->getTag() << std::endl;
        e->move();
        // std::cout << "Moved entity mem: " << e << std::endl;
    }
    for (auto e : entitiesToAdd)
    {
        entities.push_back(e);
    }
    entitiesToAdd.clear();
    // std::cout << "Ended the move loop" << std::endl;

    player->updateRotation(window);
    if (TilesManager::instance()->inDangerZone(player))
    {
        player->takeDamage(0.2);
    }

    // std::cout << "Starting the handleUpdate loop" << std::endl;
    for (auto it1{entities.begin()}; it1 != entities.end(); ++it1) // de som är i loopen är
    // tagen från tdp004 https://www.ida.liu.se/~TDP004/current/sal/slides/tdp004_9.pdf s.20

    {
        if (TilesManager::instance()->outOfBorders(*it1))
        {
            (*it1)->onBorderCollision();
        }

        for (auto it2{it1 + 1}; it2 != entities.end(); ++it2)
        {
            // std::cout << "Check collision for: " << *it1 << " " << *it2 << std::endl;
            // std::cout << "Check nullptr for it1: " << (*it1 == nullptr) << std::endl;
            // std::cout << "Check nullptr for it2: " << (*it2 == nullptr) << std::endl;
            // std::cout << "Check for: " << *it1 << " " << *it2 << " is "
            //           << (*it1)->getGlobalBounds().intersects((*it2)->getGlobalBounds())
            //           << std::endl;

            if ((*it1)->getGlobalBounds().intersects((*it2)->getGlobalBounds()))
            {
                (*it1)->onCollision(*it2);
                (*it2)->onCollision(*it1);
            }
        }
    }
    // std::cout << "Done with handleUpdate loop" << std::endl;

    if (entitiesToDelete.size() > 0)
    {
        // std::cout << "Entities before delete: " << entities.size() << std::endl;
        // for (auto e : entities)
        // {
        //     std::cout << e << std::endl;
        // }
        // std::cout << "Entities to delete: " << entitiesToDelete.size() << std::endl;
        // for (auto e : entitiesToDelete)
        // {
        //     std::cout << "type: " << e->getTag() << std::endl;
        //     std::cout << "mem: " << e << std::endl;
        // }
        // std::cout << "Removing from entities " << entitiesToDelete.size() << std::endl;

        for (auto e : entitiesToDelete)
        {
            // std::cout << "Deleting entity: " << e->getTag() << std::endl;
            // std::cout << "Deleting entity mem: " << e << std::endl;
            auto entitieItToDelete = std::find_if(
                entities.begin(), entities.end(), [&e](Entity *e1) { return e == e1; });
            delete e;
            entities.erase(entitieItToDelete);
        }

        //     std::cout << "Done removing" << std::endl;
        entitiesToDelete.clear();

        //     std::cout << "Entities after delete: " << entities.size() << std::endl;
        //     for (auto e : entities)
        //     {
        //         std::cout << e << std::endl;
        //     }
    }
    // std::cout << "Done with handleUpdate func" << std::endl;
}

void Map::draw(sf::RenderWindow *window) const
{
    // std::cout << "Starting the draw func" << std::endl;

    view->setCenter(player->getPosition());
    window->setView(*view);

    // std::cout << "Starting to draw entities" << std::endl;
    for (Entity *e : entities)
    {
        // std::cout << "Drawing: " << e << std::endl;
        // std::cout << "Is nullptr? " << (e == nullptr) << std::endl;
        e->draw(window);
    }
    player->draw(window);
    // std::cout << "Finished drawing all entities" << std::endl;

    if (StateMachine::instance()->state() != GameState::LEADERBOARD)
    {
        player->drawInfo(window);
    }
    // std::cout << "Finished the draw func" << std::endl;
}

void Map::addEntity(Entity *e)
{
    // std::cout << "Adding entity: " << e << std::endl;
    entitiesToAdd.push_back(e);
    // std::cout << "New size: " << entities.size() << std::endl;
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

    auto entitieItToDelete =
        std::find_if(entities.begin(), entities.end(), [&e](Entity *e1) { return e == e1; });
    auto existingEntitieItToDelete = std::find_if(
        entitiesToDelete.begin(), entitiesToDelete.end(), [&e](Entity *e1) { return e == e1; });
    if (entitieItToDelete != entities.end() && existingEntitieItToDelete == entitiesToDelete.end())
    {
        // std::cout << "Scheduling to delete entity mem " << *entitieItToDelete << std::endl;
        entitiesToDelete.push_back(*entitieItToDelete);
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
