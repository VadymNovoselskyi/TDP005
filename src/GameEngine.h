#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Player.h"
#include "Spawner.h"
#include "Window.h"

class GameEngine
{
  public:
    static GameEngine *instance();
    static GameEngine *init();
    static void deleteInstance();

    void run();

    int static const FPS;

  private:
    GameEngine();
    ~GameEngine();
    GameEngine static *instancePtr;

    Spawner *spawner;
    sf::Clock clock;

    sf::Time static const UPDATE_INTERVAL;
};

#endif