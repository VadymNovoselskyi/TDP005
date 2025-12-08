#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Player.h"
#include "Window.h"
#include "Spawner.h"

class GameEngine
{
  public:
    GameEngine();
    ~GameEngine();
    void run();

  private:
    Window *window;

    int static const FPS;
    sf::Time static const UPDATE_INTERVAL;
    sf::Clock clock;
};

#endif