#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics.hpp>

#include "Window.h"

class GameState
{
  public:
    GameState();
    ~GameState();
    void run();

  private:
    int static const FPS;
    sf::Time static const UPDATE_INTERVAL;

    Window *window;
    sf::Clock clock;
};

#endif