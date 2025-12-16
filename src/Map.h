#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Obstacle.h"
#include "Player.h"

class Map
{
  public: // singelton taget från vadyms kod
    static Map *instance();
    static Map *init(Player *player, std::vector<Obstacle *> const &obstacles);
    static void deleteInstance();
    void resetState();

    void handelUpdate(sf::RenderWindow *window);
    void draw(sf::RenderWindow *window) const;

    void addEntity(Entity *e);
    void removeEntity(Entity *e);

    Entity *getClosestEnemy();

  private:
    Map(Player *player, std::vector<Obstacle *> const &obstacles);
    ~Map();
    static Map *instancePtr;

    sf::View *view;
    Player *player;
    std::vector<Entity *> entities;
    std::vector<Entity *> entitiesToDelete;
    std::vector<Entity *> entitiesToAdd;
};

#endif