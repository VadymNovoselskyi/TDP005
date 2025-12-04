#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "GameState.h"
#include "Window.h"

class GameStateMachine
{
  public:
    static GameStateMachine *instance();
    static GameStateMachine *init(Window *window);
    static void deleteInstance();

    GameState state() const;

    void openStartMenu();
    void startGame();
    void pauseGame();
    void finishGame();
    void exitGame();

    void run();

    void addListener(std::string id, std::function<void(GameState)> handler);
    void removeListener(std::string id);

    // TODO: Better ways to decouple gsm from window???
    void setWindow(Window *window);

  private:
    void setState(GameState gameState);

    static GameStateMachine *instancePtr;
    GameStateMachine(Window *window);
    ~GameStateMachine();
    GameState currentState;

    int static const FPS;
    sf::Time static const UPDATE_INTERVAL;

    Window *window;
    sf::Clock clock;

    std::map<std::string, std::function<void(GameState)>> listenersMap;
};

#endif