#include "Map.h"

#include <algorithm>
#include <iostream>

#include "StateMachine.h"
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
        for (auto it2{it1 + 1}; it2 != entities.end(); ++it2)
        {
            if ((*it1)->getGlobalBounds().intersects((*it2)->getGlobalBounds()))
            {
                (*it1)->onCollision(*it2);
                (*it2)->onCollision(*it1);
            }
        }
        toRemove.erase(toRemove.begin());
    }
}

void Map::draw(sf::RenderWindow *window) const
{
    // std::cout << "Rendering the player" << std::endl;
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
    std::remove_if(entities.begin(), entities.end(), [e](Entity *e1) { return e == e1; }),
        toRemove.end();
}

Entity *Map::getClosestEnemy()
{
    Entity *enemy{nullptr};
    double minPos {999999.0};
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
    : view{new sf::View{
          {static_cast<float>(Window::WINDOW_WIDTH) / 2,
           static_cast<float>(Window::WINDOW_HEIGHT) / 2},
          {static_cast<float>(Window::WINDOW_WIDTH), static_cast<float>(Window::WINDOW_HEIGHT)}}},
      player{player}, entities{}, toRemove{}
{
    for (Obstacle *obstacle : obstacles)
    {
        entities.push_back(obstacle);
    }
}

Map::~Map()
{
    // std::cout << "Running the window destructor" << std::endl;
    delete player;
    delete view;
    player = nullptr;
    view = nullptr;

    for (Entity *e : entities)
    {
        delete e;
    }
}
