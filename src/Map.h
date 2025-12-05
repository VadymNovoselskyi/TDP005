#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Menu.h"

class Map
{
  public:
    Map();
    ~Map();
    void draw(sf::RenderWindow *window);
    void closeWindow();

    int static const MAP_WIDTH;
    int static const MAP_HEIGHT;

  private:
    sf::View *view;
    

};

#endif