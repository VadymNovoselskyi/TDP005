#include "GameStateMachine.h"

#include <iostream>
#include <stdexcept>

#include "Window.h"

GameStateMachine *GameStateMachine::instancePtr{nullptr};
int const GameStateMachine::FPS{60};
sf::Time const GameStateMachine::UPDATE_INTERVAL{sf::milliseconds(1000.0 / FPS)};

// Static methods:
GameStateMachine *GameStateMachine::instance()
{
    if (GameStateMachine::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init GameStateMachine before calling instance on it");
    }
    return GameStateMachine::instancePtr;
}

GameStateMachine *GameStateMachine::init(Window *window)
{
    GameStateMachine::instancePtr = new GameStateMachine(window);
    return GameStateMachine::instancePtr;
}

void GameStateMachine::deleteInstance()
{
    delete GameStateMachine::instancePtr;
    GameStateMachine::instancePtr = nullptr;
}

// Instance methods
GameStateMachine::GameStateMachine(Window *window)
    : currentState{GameState::START_MENU}, window{window}, clock{sf::Clock()}
{
    // std::cout << "Constructed the StartMenu" << std::endl;
}

GameStateMachine::~GameStateMachine()
{
    if (window != nullptr)
    {
        delete window;
        window = nullptr;
    }
}

void GameStateMachine::run()
{
    if (window == nullptr)
    {
        throw std::logic_error("Trying to run the GameStateMachine while window is nullptr");
    }

    // std::cout << "Running the GameOverState" << std::endl;
    while (!window->isClosed())
    {
        // std::cout << "Running the run loop" << std::endl;

        clock.restart();
        window->draw();

        sf::Time delta{UPDATE_INTERVAL - clock.getElapsedTime()};
        sf::sleep(delta);
    }
}

void GameStateMachine::addListener(std::string id, std::function<void(GameState)> handler)
{
    listenersMap.insert_or_assign(id, handler);
}
void GameStateMachine::removeListener(std::string id)
{
    listenersMap.erase(listenersMap.find(id));
}

GameState GameStateMachine::state() const
{
    return currentState;
}

void GameStateMachine::openStartMenu()
{
    if (currentState != GameState::GAME_PAUSED && currentState != GameState::GAME_OVER)
    {
        throw std::logic_error("Can open the start menu only if the game is paused or over");
    }
    setState(GameState::START_MENU);
}
void GameStateMachine::startGame()
{
    if (currentState != GameState::START_MENU && currentState != GameState::GAME_OVER)
    {
        throw std::logic_error("Can start the game only if in the main menu or the game is over");
    }
    setState(GameState::IN_GAME);
}

void GameStateMachine::pauseGame()
{
    if (currentState != GameState::IN_GAME)
    {
        throw std::logic_error("Can pause the game only if the game is on");
    }
    setState(GameState::GAME_PAUSED);
}

void GameStateMachine::finishGame()
{
    if (currentState != GameState::IN_GAME)
    {
        throw std::logic_error("Can finish the game only if the game is on");
    }
    setState(GameState::GAME_OVER);
}

void GameStateMachine::exitGame()
{
    if (currentState != GameState::START_MENU && currentState != GameState::GAME_OVER &&
        currentState != GameState::GAME_PAUSED)
    {
        throw std::logic_error("Can exit the game only if the main, paus or game over menus is open");
    }
    window->closeWindow();
    setState(GameState::EXIT);
}

void GameStateMachine::setState(GameState gameState)
{
    this->currentState = gameState;
    for (auto const &[id, handler] : listenersMap)
    {
        handler(currentState);
    }
}

void GameStateMachine::setWindow(Window *window)
{
    this->window = window;
}