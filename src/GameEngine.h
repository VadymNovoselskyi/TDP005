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
    
    int static const FPS;
  private:
    Spawner *spawner;
    sf::Clock clock;
    
    sf::Time static const UPDATE_INTERVAL;
};

#endif