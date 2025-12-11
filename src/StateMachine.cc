#include "StateMachine.h"

#include <iostream>
#include <stdexcept>

#include "GameState.h"

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
StateMachine::StateMachine() : currentState{GameState::IN_START_MENU}
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
    // std::cout << "Opening the start menu from " << currentState << std::endl;
    if (currentState != GameState::GAME_PAUSED && currentState != GameState::GAME_OVER)
    {
        throw std::logic_error("Can open the start menu only if the game is paused or over");
    }
    setState(GameState::IN_START_MENU);
}

void StateMachine::chooseUsername()
{
    // std::cout << "Choosing the name from" << currentState << std::endl;
    if (currentState != GameState::IN_START_MENU)
    {
        throw std::logic_error("Can choose the name only from the start menu");
    }
    setState(GameState::CHOOSING_USERNAME);
}

void StateMachine::startGame()
{
    // std::cout << "Starting the game from " << currentState << std::endl;
    if (currentState != GameState::IN_START_MENU && currentState != GameState::GAME_OVER &&
        currentState != GameState::CHOOSING_USERNAME)
    {
        throw std::logic_error("Can start the game only if in the main menu, choosing name or the game is over");
    }
    setState(GameState::STARTING_GAME);
}

void StateMachine::continueGame()
{
    // std::cout << "Continuing the game from " << currentState << std::endl;
    if (currentState != GameState::GAME_PAUSED && currentState != GameState::LEVEL_UP_SCREEN)
    {
        throw std::logic_error("Can continue the game only if it was paused or on level up");
    }
    setState(GameState::CONTINUING_GAME);
}

void StateMachine::setInGame()
{
    // std::cout << "Setting to in game from " << currentState << std::endl;
    if (currentState != GameState::STARTING_GAME && currentState != GameState::CONTINUING_GAME)
    {
        throw std::logic_error("Can set to in game only if in was starting or continuing the game");
    }
    setState(GameState::IN_GAME);
}

void StateMachine::startLevelUp()
{
    // std::cout << "Starting the level up from " << currentState << std::endl;
    if (currentState != GameState::IN_GAME)
    {
        throw std::logic_error("Can go to the level up screen only when in game");
    }
    setState(GameState::LEVEL_UP_SCREEN);
}

void StateMachine::pauseGame()
{
    // std::cout << "Pausing the game from " << currentState << std::endl;
    if (currentState != GameState::IN_GAME)
    {
        throw std::logic_error("Can pause the game only if the game is on");
    }
    setState(GameState::GAME_PAUSED);
}

void StateMachine::finishGame()
{
    // std::cout << "Finishing the game from " << currentState << std::endl;
    if (currentState != GameState::IN_GAME && currentState != GameState::GAME_PAUSED)
    {
        throw std::logic_error("Can finish the game only if the game is on or is paused");
    }
    setState(GameState::GAME_OVER);
}

void StateMachine::exitGame()
{
    // std::cout << "Exiting the game from " << currentState << std::endl;
    if (currentState != GameState::IN_START_MENU && currentState != GameState::GAME_OVER &&
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
