#include "StateMachine.h"

#include <iostream>
#include <stdexcept>

StateMachine *StateMachine::instancePtr{nullptr};

// Static methods:
StateMachine *StateMachine::instance()
{
    if (StateMachine::instancePtr == nullptr)
    {
        throw std::logic_error("Didn't init StateMachine before calling instance on it");
    }
    return StateMachine::instancePtr;
}

StateMachine *StateMachine::init()
{
    StateMachine::instancePtr = new StateMachine();
    return StateMachine::instancePtr;
}

void StateMachine::deleteInstance()
{
    // std::cout << "Deleting the instance" << std::endl;
    delete StateMachine::instancePtr;
    StateMachine::instancePtr = nullptr;
}

// Instance methods
StateMachine::StateMachine() : currentState{GameState::START_MENU}
{
    // std::cout << "Constructed the StartMenu" << std::endl;
}

void StateMachine::addListener(std::string const &id, std::function<void(GameState)> handler)
{
    listenersMap.insert_or_assign(id, handler);
}
void StateMachine::removeListener(std::string const &id)
{
    listenersMap.erase(listenersMap.find(id));
}

GameState StateMachine::state() const
{
    return currentState;
}

void StateMachine::openStartMenu()
{
    if (currentState != GameState::GAME_PAUSED && currentState != GameState::GAME_OVER)
    {
        throw std::logic_error("Can open the start menu only if the game is paused or over");
    }
    setState(GameState::START_MENU);
}
void StateMachine::startGame()
{
    if (currentState != GameState::START_MENU && currentState != GameState::GAME_OVER)
    {
        throw std::logic_error("Can start the game only if in the main menu or the game is over");
    }
    setState(GameState::IN_GAME);
}

void StateMachine::pauseGame()
{
    if (currentState != GameState::IN_GAME)
    {
        throw std::logic_error("Can pause the game only if the game is on");
    }
    setState(GameState::GAME_PAUSED);
}

void StateMachine::finishGame()
{
    if (currentState != GameState::IN_GAME)
    {
        throw std::logic_error("Can finish the game only if the game is on");
    }
    setState(GameState::GAME_OVER);
}

void StateMachine::exitGame()
{
    if (currentState != GameState::START_MENU && currentState != GameState::GAME_OVER &&
        currentState != GameState::GAME_PAUSED)
    {
        throw std::logic_error(
            "Can exit the game only if the main, paus or game over menus is open");
    }
    setState(GameState::EXIT);
}

void StateMachine::setState(GameState gameState)
{
    this->currentState = gameState;
    for (auto const &[id, handler] : listenersMap)
    {
        handler(currentState);
    }
}
