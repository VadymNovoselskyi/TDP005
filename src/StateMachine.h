#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "GameState.h"

class StateMachine
{
  public:
    static StateMachine *instance();
    static StateMachine *init();
    static void deleteInstance();

    // .clang-tidy that recommended it
    GameState state() const;

    void openStartMenu();
    void chooseUsername();
    void startGame();
    void setInGame();
    void pauseGame();
    void continueGame();
    void startLevelUp();
    void finishGame();
    void exitGame();

    void addListener(std::string const &id, std::function<void(GameState)> handler);
    void removeListener(std::string const &id);

  private:
    void setState(GameState gameState);

    static StateMachine *instancePtr;
    StateMachine();
    GameState currentState;

    std::map<std::string, std::function<void(GameState)>> listenersMap;
};

#endif