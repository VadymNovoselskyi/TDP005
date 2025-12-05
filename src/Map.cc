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

Map *Map::init(Player *player)
{
    Map::instancePtr = new Map(player);
    return Map::instancePtr;
}

void Map::deleteInstance()
{
    // std::cout << "Deleting the instance" << std::endl;
    delete Map::instancePtr;
    Map::instancePtr = nullptr;
}

void Map::draw(sf::RenderWindow *window) const
{
    for_each(entities.begin(), entities.end(), [](Entity *e) { e->move(); });

    // de som är i loopen är tagen från tdp004
    // https://www.ida.liu.se/~TDP004/current/sal/slides/tdp004_9.pdf s.20 for (auto
    // it1{entities.begin()}; it1 != entities.end(); ++it1)
    // {
    //     for (auto it2{it1  + 1}; it2 != entities.end(); ++it2)
    //     {

    //     }
    // }

    // std::cout << "Rendering the player" << std::endl;
    view->setCenter(player->getPosition());
    window->setView(*view);
    player->draw(window);

    int const r{50};
    sf::CircleShape circle1{r};
    circle1.setOrigin(r, r);
    circle1.setFillColor(sf::Color::Red);
    sf::CircleShape circle2{r};
    circle2.setOrigin(r, r);
    circle2.setFillColor(sf::Color::Green);
    sf::CircleShape circle3{r};
    circle3.setOrigin(r, r);
    circle3.setFillColor(sf::Color::Blue);

    circle1.setPosition(500, 100);
    circle2.setPosition(1000, 100);
    circle3.setPosition(1500, 100);
    window->draw(circle1);
    window->draw(circle2);
    window->draw(circle3);
}

void Map::addEntity(Entity *e)
{
    entities.push_back(e);
}

void Map::removeEntity(Entity *e)
{
    entities.erase(std::remove_if(entities.begin(), entities.end(), [e](Entity *e1){
        return e == e1;
    }));
}

Map::Map(Player *player)
    : view{new sf::View{
          {static_cast<float>(Window::WINDOW_WIDTH) / 2,
           static_cast<float>(Window::WINDOW_HEIGHT) / 2},
          {static_cast<float>(Window::WINDOW_WIDTH), static_cast<float>(Window::WINDOW_HEIGHT)}}},
      player{player}, entities{}
{
}

Map::~Map()
{
    // std::cout << "Running the window destructor" << std::endl;
    delete player;
    player = nullptr;

    for (Entity* e : entities)
    {
        delete e;
    }
}
