#include "StateMachine.h"

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
    delete StateMachine::instancePtr;
    StateMachine::instancePtr = nullptr;
}

// Instance methods
StateMachine::StateMachine() : currentState{GameState::IN_START_MENU}
{
}

void StateMachine::addListener(std::function<void(GameState)> const &handler)
{
    listeners.push_back(handler);
}

GameState StateMachine::state() const
{
    return currentState;
}

void StateMachine::openStartMenu()
{
    if (currentState != GameState::GAME_PAUSED && currentState != GameState::GAME_OVER &&
        currentState != GameState::LEADERBOARD)
    {
        throw std::logic_error(
            "Can open the start menu only if the game is paused or over or in the leaderboard");
    }
    setState(GameState::IN_START_MENU);
}

void StateMachine::openLeaderboard()
{
    if (currentState != GameState::IN_START_MENU)
    {
        throw std::logic_error("Can open the leaderboard only if the start menu is open");
    }
    setState(GameState::LEADERBOARD);
}

void StateMachine::chooseUsername()
{
    if (currentState != GameState::IN_START_MENU)
    {
        throw std::logic_error("Can choose the name only from the start menu");
    }
    setState(GameState::CHOOSING_USERNAME);
}

void StateMachine::startGame()
{
    if (currentState != GameState::IN_START_MENU && currentState != GameState::GAME_OVER &&
        currentState != GameState::CHOOSING_USERNAME)
    {
        throw std::logic_error(
            "Can start the game only if in the main menu, choosing name or the game is over");
    }
    setState(GameState::STARTING_GAME);
}

void StateMachine::setInGame()
{
    if (currentState != GameState::STARTING_GAME && currentState != GameState::GAME_OVER &&
        currentState != GameState::GAME_PAUSED && currentState != GameState::LEVEL_UP_SCREEN)
    {
        throw std::logic_error("Can set to in game only if in was starting the game, game is over, "
                               "game is paused or level up screen");
    }
    setState(GameState::IN_GAME);
}

void StateMachine::startLevelUp()
{
    if (currentState != GameState::IN_GAME)
    {
        throw std::logic_error("Can go to the level up screen only when in game");
    }
    setState(GameState::LEVEL_UP_SCREEN);
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
    if (currentState != GameState::IN_GAME && currentState != GameState::GAME_PAUSED)
    {
        throw std::logic_error("Can finish the game only if the game is on or is paused");
    }
    setState(GameState::GAME_OVER);
}

void StateMachine::exitGame()
{
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
    for (auto &handler : listeners)
    {
        handler(currentState);
    }
}
