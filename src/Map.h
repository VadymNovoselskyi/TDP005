#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Player.h"

class Map
{
  public:
    static Map *instance();
    static Map *init(Player *player);
    static void deleteInstance();

    void handelUpdate();
    void draw(sf::RenderWindow *window) const;

    void addEntity(Entity *e);
    void removeEntity(Entity *e);

  private:
    Map(Player *player);
    ~Map();
    static Map *instancePtr;

    sf::View *view;
    Player *player;
    std::vector<Entity *> entities;
};

#endif