#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Player.h"
#include "Spawner.h"
#include "Window.h"

/**
 * Main game engine singleton that manages the game loop and initializations
 *
 * GameEngine is responsible for:
 * - Initializing all game systems (StateMachine, TextureManager, Map, etc)
 * - Running the main game loop with fixed FPS
 * - Managing game states and events
 */
class GameEngine
{
  public:
    /**
     * Get the GameEngine singleton instance
     * The instance must be created with init() before calling this function
     *
     * @return Pointer to the singleton GameEngine instance
     * @throws std::logic_error if the GameEngine has not been initialized
     */
    static GameEngine *instance();

    /**
     * Create and initialize the GameEngine singleton
     * Initializes all game systems and sets up the game world
     *
     * @return Pointer to the created singleton GameEngine instance
     */
    static GameEngine *init();

    /**
     * Destroy the GameEngine singleton instance
     */
    static void deleteInstance();

    /**
     * Run the main game loop
     */
    void run();

    int static const FPS;

  private:
    /**
     * Create a GameEngine and initialize game systems
     */
    GameEngine();

    /**
     * Destroy the GameEngine and clean up owned systems
     */
    ~GameEngine();
    GameEngine static *instancePtr;

    Spawner *spawner;
    sf::Clock clock;

    sf::Time static const UPDATE_INTERVAL;
};

#endif