#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Window.h"

class GameState
{
  public:
    GameState(std::vector<Menu *> menus);
    ~GameState();
    void run();

  private:
    int static const FPS;
    sf::Time static const UPDATE_INTERVAL;

    Window *window;
    sf::Clock clock;
};

#endif