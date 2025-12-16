#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>

#include "GameState.h"

/**
 * Controls the current game state, validates state transitions and notifies listeners when state
 * changes happen
 *
 * StateMachine is responsible for:
 * - Tracking the current GameState
 * - Providing functions for moving between game states
 * - Notifying listeners when state changes happen
 */
class StateMachine
{
  public:
    /**
     * Get the StateMachine singleton instance
     * The instance must be created with init() before calling this function
     *
     * @return Pointer to the singleton StateMachine instance
     * @throws std::logic_error if the StateMachine has not been initialized
     */
    static StateMachine *instance();

    /**
     * Create and initialize the StateMachine singleton
     *
     * @return Pointer to the created singleton StateMachine instance
     */
    static StateMachine *init();

    /**
     * Destroy the StateMachine singleton instance
     */
    static void deleteInstance();

    /**
     * Get the current game state
     *
     * @return Current GameState
     */
    GameState state() const;

    /**
     * Set state to IN_START_MENU
     */
    void openStartMenu();

    /**
     * Set state to LEADERBOARD
     */
    void openLeaderboard();

    /**
     * Set state to CHOOSING_USERNAME
     */
    void chooseUsername();

    /**
     * Set state to STARTING_GAME
     */
    void startGame();

    /**
     * Set state to IN_GAME
     */
    void setInGame();

    /**
     * Set state to GAME_PAUSED
     */
    void pauseGame();

    /**
     * Set state to CONTINUING_GAME
     */
    void continueGame();

    /**
     * Set state to LEVEL_UP_SCREEN
     */
    void startLevelUp();

    /**
     * Set state to GAME_OVER
     */
    void finishGame();

    /**
     * Set state to EXIT
     */
    void exitGame();

    /**
     * Add a listener callback for state changes
     *
     * @param handler Function called when the state changes
     */
    void addListener(std::function<void(GameState)> const &handler);

  private:
    void setState(GameState gameState);

    static StateMachine *instancePtr;
    StateMachine();
    GameState currentState;

    std::vector<std::function<void(GameState)>> listeners;
};

#endif