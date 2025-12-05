#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Player.h"

class Map
{
  public:
    Map(Player *player);
    ~Map();
    void draw(sf::RenderWindow *window) const;

  private:
    sf::View *view;
    Player *player;
};

#endif